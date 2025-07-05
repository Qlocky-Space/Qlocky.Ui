#ifndef QLOCKY_UI_QML_COMMAND_BASE_H
#define QLOCKY_UI_QML_COMMAND_BASE_H

#include <QObject>

#include "CommandIfc.h"

/**
 * CommandIfc is an interface for commands in the UI framework.
 */
class QmlCommandBase : public QObject, public CommandIfc {
    Q_OBJECT
    Q_PROPERTY(bool canExecute READ canExecute NOTIFY canExecuteChanged)

public:

    /**
     * Constructor for QmlCommandBase.
     */
    using QObject::QObject;

    /**
     * Destructor for QmlCommandBase.
     */
    ~QmlCommandBase() override = default;

    /**
     * A simple way to call command from QML.
     *
     * command.execute({
     *     "action": "login",
     *     "username": "sandro",
     *     "password": "secret"
     * })
     */
    Q_INVOKABLE void execute(QVariantMap const& data = {}) {
        CommandArgs const args {CommandArgs::fromQVariantMap(data)};
        execute(&args);
    }

    /**
     * @see CommandIfc::execute
     */
    void execute(CommandArgs const* data) final;

    /**
     * @see CommandIfc::canExecute
     */
    bool canExecute() const final;

signals:
    /**
     * Signal emitted when the command's executable state changes.
     * This should be connected to UI elements to enable or disable them based on the command's state.
     */
    void canExecuteChanged();

protected:

    /**
     * Method 'execute' can be called from QML and delegates to this method.
     */
    virtual void doExecute(CommandArgs const& data) = 0;

    /**
     * Can be called to change wether the command can be executed or not.
     * @param canExecute true if the command can be executed, false otherwise.
     */
    void setCanExecute(bool const canExecute);

private:

    bool m_canExecute {true};
};

#endif