#ifndef QLOCKY_MAIN_WINDOW_IFC_H
#define QLOCKY_MAIN_WINDOW_IFC_H

class QWindow;

/**
 * Interface to MainWindow. In the appliction it could only exists
 * one main window
 */
class MainWindowIfc {
public:

    virtual ~MainWindowIfc() = default;
};

#endif