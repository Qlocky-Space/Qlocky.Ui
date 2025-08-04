#ifndef SHOW_QR_CODE_COMMAND_H
#define SHOW_QR_CODE_COMMAND_H

#include <Command/QmlCommandBase.h>
#include <Navigation/InteractiveNavigatorIfc.h>

/**
 * Command to show a QR code dialog.
 * This command is used to display a QR code dialog in the application.
 * It utilizes the InteractiveNavigatorIfc to navigate to the QR code dialog.
 */
class ShowQrCodeCommand : public QmlCommandBase {
public:

    explicit ShowQrCodeCommand(InteractiveNavigatorIfc& navigator);

protected:

    /**
     * @see CommandIfc::doExecute
     */
    void doExecute(CommandArgs const& data) final;

private:

    InteractiveNavigatorIfc& m_navigator;
};

#endif