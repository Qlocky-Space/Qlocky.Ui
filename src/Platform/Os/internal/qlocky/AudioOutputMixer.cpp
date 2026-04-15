#include "AudioOutputMixer.h"

#include <algorithm>
#include <alsa/asoundlib.h>
#include <chrono>
#include <ng-log/logging.h>
#include <poll.h>
#include <thread>
#include <vector>

namespace {

constexpr char const* CARD_NAME {"default"};
constexpr char const* MIXER_SELEM_NAME {"Master"};
constexpr uint8_t MIN_OUTPUT_PERCENT {40};
constexpr uint8_t MAX_OUTPUT_PERCENT {65};

uint8_t mapRequestedToOutputPercent(uint8_t requestedPercent) {
    long const clampedRequested = std::clamp(static_cast<long>(requestedPercent), 0L, 100L);
    long const outputRange = static_cast<long>(MAX_OUTPUT_PERCENT) - static_cast<long>(MIN_OUTPUT_PERCENT);
    long const mappedPercent = static_cast<long>(MIN_OUTPUT_PERCENT) + ((outputRange * clampedRequested + 50) / 100);

    return static_cast<uint8_t>(std::clamp(mappedPercent,
        static_cast<long>(MIN_OUTPUT_PERCENT),
        static_cast<long>(MAX_OUTPUT_PERCENT)));
}

uint8_t normalizePercent(long value, long min, long max) {
    if (max <= min) {
        return 0;
    }

    long const clamped = std::clamp(value, min, max);
    long const normalized = ((clamped - min) * 100 + ((max - min) / 2)) / (max - min);
    return static_cast<uint8_t>(std::clamp(normalized, 0L, 100L));
}

long percentToRaw(uint8_t percent, long min, long max) {
    if (max <= min) {
        return min;
    }

    long const clampedPercent = std::clamp(static_cast<long>(percent), 0L, 100L);
    long const range = max - min;
    return min + ((range * clampedPercent + 50) / 100);
}

} // namespace

AudioOutputMixer::AudioOutputMixer() {
    snd_mixer_t* rawHandle {nullptr};
    if (snd_mixer_open(&rawHandle, 0) < 0) {
        LOG(WARNING) << "Failed to open ALSA mixer";
        return;
    }

    m_mixerHandle.reset(rawHandle);

    if (snd_mixer_attach(m_mixerHandle.get(), CARD_NAME) < 0) {
        LOG(WARNING) << "Failed to attach ALSA mixer card: " << CARD_NAME;
        m_mixerHandle.reset();
        return;
    }

    if (snd_mixer_selem_register(m_mixerHandle.get(), nullptr, nullptr) < 0) {
        LOG(WARNING) << "Failed to register ALSA simple elements";
        m_mixerHandle.reset();
        return;
    }

    if (snd_mixer_load(m_mixerHandle.get()) < 0) {
        LOG(WARNING) << "Failed to load ALSA mixer";
        m_mixerHandle.reset();
        return;
    }

    snd_mixer_selem_id_t* rawSetting {nullptr};
    if (snd_mixer_selem_id_malloc(&rawSetting) < 0 || rawSetting == nullptr) {
        LOG(WARNING) << "Failed to allocate ALSA mixer setting id";
        m_mixerHandle.reset();
        return;
    }

    m_mixerSetting.reset(rawSetting);

    if (findMixerElementLocked() == nullptr) {
        LOG(WARNING) << "Failed to resolve ALSA mixer element: " << MIXER_SELEM_NAME;
        m_mixerSetting.reset();
        m_mixerHandle.reset();
        return;
    }

    uint8_t initialVolume {m_cachedVolume.load()};
    if (readVolumeLocked(initialVolume)) {
        m_cachedVolume.store(initialVolume);
    }

    m_volumeWatcher = std::thread([this]() {
        volumeWatchLoop();
    });
}

AudioOutputMixer::~AudioOutputMixer() {
    m_stopWatcher.store(true);
    if (m_volumeWatcher.joinable()) {
        m_volumeWatcher.join();
    }
}

void AudioOutputMixer::MixerHandleDeleter::operator()(snd_mixer_t* handle) const {
    if (handle != nullptr) {
        snd_mixer_close(handle);
    }
}

void AudioOutputMixer::MixerSettingDeleter::operator()(snd_mixer_selem_id_t* setting) const {
    if (setting != nullptr) {
        snd_mixer_selem_id_free(setting);
    }
}

bool AudioOutputMixer::isInitializedLocked() const {
    return m_mixerHandle && m_mixerSetting;
}

snd_mixer_elem_t* AudioOutputMixer::findMixerElementLocked() const {
    if (!isInitializedLocked()) {
        return nullptr;
    }

    snd_mixer_selem_id_set_index(m_mixerSetting.get(), 0);
    snd_mixer_selem_id_set_name(m_mixerSetting.get(), MIXER_SELEM_NAME);
    return snd_mixer_find_selem(m_mixerHandle.get(), m_mixerSetting.get());
}

void AudioOutputMixer::volumeWatchLoop() {
    while (!m_stopWatcher.load()) {
        std::vector<pollfd> descriptors {};

        {
            std::lock_guard<std::mutex> lock {m_mutex};
            if (!isInitializedLocked()) {
                break;
            }

            int const descriptorCount = snd_mixer_poll_descriptors_count(m_mixerHandle.get());
            if (descriptorCount <= 0) {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                continue;
            }

            descriptors.resize(static_cast<size_t>(descriptorCount));
            if (snd_mixer_poll_descriptors(m_mixerHandle.get(), descriptors.data(), descriptors.size()) < 0) {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                continue;
            }
        }

        int const pollResult = poll(descriptors.data(), descriptors.size(), 300);
        if (pollResult <= 0) {
            continue;
        }

        bool shouldNotify {false};
        uint8_t changedVolume {0};
        {
            std::lock_guard<std::mutex> lock {m_mutex};
            if (!isInitializedLocked()) {
                break;
            }

            unsigned short revents {0};
            if (snd_mixer_poll_descriptors_revents(m_mixerHandle.get(), descriptors.data(), descriptors.size(), &revents) < 0 || revents == 0) {
                continue;
            }

            if (snd_mixer_handle_events(m_mixerHandle.get()) < 0) {
                continue;
            }

            uint8_t currentVolume {m_cachedVolume.load()};
            if (!readVolumeLocked(currentVolume)) {
                continue;
            }

            if (currentVolume != m_cachedVolume.load()) {
                m_cachedVolume.store(currentVolume);
                changedVolume = currentVolume;
                shouldNotify = true;
            }
        }

        if (shouldNotify) {
            notify(&AudioMixerListenerIfc::onVolumeChanged, static_cast<uint8_t>(changedVolume));
        }
    }
}

bool AudioOutputMixer::setOutputVolume(uint8_t volumePercent) {
    uint8_t actualPercent {0};
    {
        std::lock_guard<std::mutex> lock {m_mutex};

        bool const success = writeVolumeLocked(volumePercent, actualPercent);
        if (!success) {
            return false;
        }

        m_cachedVolume.store(actualPercent);
    }

    notify(&AudioMixerListenerIfc::onVolumeChanged, static_cast<uint8_t>(actualPercent));
    return true;
}

uint8_t AudioOutputMixer::outputVolume() const {
    std::lock_guard<std::mutex> lock {m_mutex};

    uint8_t actualPercent {m_cachedVolume.load()};
    if (readVolumeLocked(actualPercent)) {
        m_cachedVolume.store(actualPercent);
    }

    return m_cachedVolume.load();
}

bool AudioOutputMixer::readVolumeLocked(uint8_t& volumePercent) const {
    snd_mixer_elem_t* element {findMixerElementLocked()};
    if (element == nullptr) {
        LOG(WARNING) << "Failed to resolve ALSA mixer element for volume read";
        return false;
    }

    long minVolume {0};
    long maxVolume {0};
    snd_mixer_selem_get_playback_volume_range(element, &minVolume, &maxVolume);

    long rawVolume {0};
    int const readResult = snd_mixer_selem_get_playback_volume(element, SND_MIXER_SCHN_FRONT_LEFT, &rawVolume);

    if (readResult < 0) {
        LOG(WARNING) << "Failed to read ALSA playback volume";
        return false;
    }

    volumePercent = normalizePercent(rawVolume, minVolume, maxVolume);
    return true;
}

bool AudioOutputMixer::writeVolumeLocked(uint8_t requestedPercent, uint8_t& actualPercent) {
    snd_mixer_elem_t* element {findMixerElementLocked()};
    if (element == nullptr) {
        LOG(WARNING) << "Failed to resolve ALSA mixer element for volume write";
        return false;
    }

    long minVolume {0};
    long maxVolume {0};
    snd_mixer_selem_get_playback_volume_range(element, &minVolume, &maxVolume);

    uint8_t const mappedOutputPercent = mapRequestedToOutputPercent(requestedPercent);
    long const rawRequested = percentToRaw(mappedOutputPercent, minVolume, maxVolume);
    int const writeResult = snd_mixer_selem_set_playback_volume_all(element, rawRequested);
    if (writeResult < 0) {
        LOG(WARNING) << "Failed to set ALSA playback volume";
        return false;
    }

    long rawActual {0};
    int const readResult = snd_mixer_selem_get_playback_volume(element, SND_MIXER_SCHN_FRONT_LEFT, &rawActual);

    if (readResult < 0) {
        LOG(WARNING) << "Failed to read ALSA playback volume after write";
        return false;
    }

    actualPercent = normalizePercent(rawActual, minVolume, maxVolume);
    return true;
}
