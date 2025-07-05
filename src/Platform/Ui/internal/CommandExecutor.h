#ifndef COMMAND_EXECUTOR_H
#define COMMAND_EXECUTOR_H

#include <QObject>
#include <QString>
#include <QVariantMap>

#include "Command/CommandDispatcherIfc.h"

/**
 * This class acts as a bridge allowing QML code to dispatch commands
 * through the provided CommandDispatcher interface.
 */
class CommandExecutor : public QObject {
    Q_OBJECT

public:

    CommandExecutor(CommandDispatcherIfc& dispatcher);

    /**
     * Dispatches a command by its identifier with optional data arguments.
     *
     * This method can be called from QML to trigger commands.
     *
     * @param id The identifier of the command to dispatch.
     * @param data Optional command arguments passed as a QVariantMap.
     */
    Q_INVOKABLE void dispatch(QString const& id, QVariantMap const& data = {});

private:

    CommandDispatcherIfc& m_dispatcher;
};

#endif