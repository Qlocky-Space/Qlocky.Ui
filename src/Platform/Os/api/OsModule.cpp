#include "OsModule.h"

#include "AudioMixerIfc.h"
#include "AudioOutputIfc.h"
#include "internal/AsyncTaskExecutor.h"
#include "internal/TimeProvider.h"
#include "NetworkDriverIfc.h"
#include "TaskExecutorIfc.h"

// include platform specific drivers
#ifdef OS_IS_QLOCKY
#include "internal/qlocky/AudioOutputMixer.h"
#include "internal/qlocky/AudioOutputProcessDriver.h"
#include "internal/qlocky/WpaSupplicantDBusDriver.h"
#else
#include "internal/mock/AudioMixerStub.h"
#include "internal/mock/AudioOutputStub.h"
#include "internal/mock/NetworkDriverStub.h"
#endif

void OsModule::registerExports(Injector& container) {
    container.install(boost::di::bind<TimeProviderIfc>().to<TimeProvider>());
    container.install(boost::di::bind<TaskExecutorIfc>().to<AsyncTaskExecutor>().in(boost::di::singleton));

#ifdef OS_IS_QLOCKY
    container.install(boost::di::bind<AudioMixerIfc>().to<AudioOutputMixer>().in(boost::di::singleton));
    container.install(boost::di::bind<AudioOutputIfc>().to<AudioOutputProcessDriver>());
    container.install(boost::di::bind<NetworkDriverIfc>().to<WpaSupplicantDBusDriver>());
#else
    container.install(boost::di::bind<AudioMixerIfc>().to<AudioMixerStub>().in(boost::di::singleton));
    container.install(boost::di::bind<AudioOutputIfc>().to<AudioOutputStub>());
    container.install(boost::di::bind<NetworkDriverIfc>().to<NetworkDriverStub>());
#endif
}
