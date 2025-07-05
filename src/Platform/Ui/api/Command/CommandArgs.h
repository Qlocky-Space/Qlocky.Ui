#ifndef COMMAND_DATA_H
#define COMMAND_DATA_H

#include <QMap>
#include <QObject>
#include <QVariant>

/**
 * CommandArgs is a class that holds command arguments in a key-value format.
 * It allows setting and getting arguments using QString keys and QVariant values.
 */
class CommandArgs : public QObject {
    Q_OBJECT

public:

    CommandArgs() = default;

    /**
     * Sets a command argument with the specified key and value.
     * @param key The key for the argument.
     * @param value The value for the argument.
     */
    Q_INVOKABLE void set(QString const& key, QVariant const& value) {
        m_data[key] = value;
    }

    /**
     * Gets a command argument value by its key.
     * @param key The key for the argument.
     * @return The value associated with the key, or a default-constructed QVariant if the key does not exist.
     */
    template<typename T>
    T get(QString const& key, T defaultValue = T {}) const {
        if (!m_data.contains(key)) {
            return defaultValue;
        }

        return m_data.value(key).value<T>();
    }

private:

    QMap<QString, QVariant> m_data {};
};

Q_DECLARE_METATYPE(CommandArgs)

#endif