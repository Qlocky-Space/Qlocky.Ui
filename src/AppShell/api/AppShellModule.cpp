#include "AppShellModule.h"

#include "internal/MainWindow.h"
#include "view/MainWindowViewModel.h"

void AppShellModule::registerExports(Injector& container) {
    container.install(boost::di::bind<MainWindowIfc>().to<MainWindow>());
}
