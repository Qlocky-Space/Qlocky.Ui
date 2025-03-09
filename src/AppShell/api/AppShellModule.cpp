#include "AppShellModule.h"

#include "internal/MainWindow.h"
#include "internal/UiEngine.h"
#include "view/MainWindowViewModel.h"

void AppShellModule::registerExports(Injector& container) {
    container.install(boost::di::bind<MainWindowIfc>().to<MainWindow>());
    container.install(boost::di::bind<UiEngineIfc>().to<UiEngine>());
}
