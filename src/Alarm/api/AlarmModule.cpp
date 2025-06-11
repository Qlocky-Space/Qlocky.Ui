#include "AlarmModule.h"

#include "internal/PingCommand.h"
#include "QmlRegistryUtil.h"
#include "view/ClockCardViewModel.h"

void AlarmModule::registerExports(Injector& container) {
    container.install(boost::di::bind<PingCommand>());
}

void AlarmModule::registerQmlTypes() {
    QmlRegistryUtil::qmlRegisterViewModel<ClockCardViewModel>(*this, "ClockCardViewModel");
}
