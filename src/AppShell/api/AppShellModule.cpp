#include "AppShellModule.h"

#include "api/Mediator.h"
#include "QmlRegistryUtil.h"
#include "view/MainWindowViewModel.h"
#include "view/WidgetListViewModel.h"

void AppShellModule::registerExports(Injector& container) {
    container.install(boost::di::bind<Mediator>());
}

void AppShellModule::registerQmlTypes() {
    QmlRegistryUtil::qmlRegisterViewModel<MainWindowViewModel>(*this, "MainWindowViewModel");
    QmlRegistryUtil::qmlRegisterViewModel<WidgetListViewModel>(*this, "WidgetListViewModel");
}