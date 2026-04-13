#include "AudioMixerStub.h"

bool AudioMixerStub::setOutputVolume(uint8_t volumePercent) {
    uint8_t const clamped = static_cast<uint8_t>(std::min<uint32_t>(volumePercent, 100U));
    if (m_volumePercent == clamped) {
        return true;
    }

    m_volumePercent = clamped;
    notify(&AudioMixerListenerIfc::onVolumeChanged, static_cast<uint8_t>(m_volumePercent));
    return true;
}

uint8_t AudioMixerStub::outputVolume() const {
    return m_volumePercent;
}
