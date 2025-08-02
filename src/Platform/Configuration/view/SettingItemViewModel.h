#ifndef SETTING_ITEM_VIEW_MODEL_H
#define SETTING_ITEM_VIEW_MODEL_H

#include <QObject>
#include <QString>

/**
 * ViewModel for a setting item in the configuration settings.
 * This class provides properties and methods to manage the title of the setting item.
 */
class SettingItemViewModel : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
    Q_PROPERTY(QString category READ category WRITE setCategory NOTIFY categoryChanged)

public:

    SettingItemViewModel() = default;
    ~SettingItemViewModel() = default;

    /**
     * Gets the title of the setting item.
     * @return The title of the setting item.
     */
    QString title() const {
        return m_title;
    }

    /**
     * Sets the title of the setting item.
     * @param title The title to set.
     */
    void setTitle(QString const& title);

    /**
     * Gets the category of the setting item.
     * @return The category of the setting item.
     */
    QString category() const {
        return m_category;
    }

    /**
     * Sets the category of the setting item.
     * @param category The category to set.
     */
    void setCategory(QString const& category);

    /**
     * Gets the path of the setting item.
     * @return The path of the setting item.
     */
    QString path() const {
        return m_path;
    }

    /**
     * Sets the path of the setting item.
     * @param path The path to set.
     */
    void setPath(QString const& path);

signals:
    void titleChanged();
    void categoryChanged();

private:

    QString m_title;
    QString m_category;
    QString m_path;
};

#endif