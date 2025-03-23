#ifndef QLOCKY_MAIN_WINDOW_IFC_H
#define QLOCKY_MAIN_WINDOW_IFC_H

#include "api/CardInfo.h"

/**
 * Interface to MainWindow. In the appliction it could only exists
 * one main window
 */
class MainWindowIfc {
public:

    /**
     * Register a card to the main window
     *
     * @param card Card to register
     */
    virtual void registerCard(CardInfo const& card) = 0;

    virtual ~MainWindowIfc() = default;
};

#endif