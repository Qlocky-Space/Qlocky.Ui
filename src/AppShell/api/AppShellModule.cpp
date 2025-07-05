#include "AppShellModule.h"

#include "api/Mediator.h"
#include "QmlRegistryUtil.h"
#include "view/MainPageViewModel.h"
#include "view/MainWindowViewModel.h"

void AppShellModule::registerExports(Injector& container) {
    container.install(boost::di::bind<Mediator>());
}

void AppShellModule::registerQmlTypes() {
    QmlRegistryUtil::qmlRegisterViewModel<MainPageViewModel>(*this, "MainPageViewModel");
    QmlRegistryUtil::qmlRegisterViewModel<MainWindowViewModel>(*this, "MainWindowViewModel");
}