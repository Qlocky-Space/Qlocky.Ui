#ifndef QLOCKY_SETTING_PAGE_VIEWMODEL_H
#define QLOCKY_SETTING_PAGE_VIEWMODEL_H

#include <QObject>
#include <QString>
#include <QtQml/qqmlregistration.h>
#include <QWindow>
#include <string>

#include "ConfigurationRegistryIfc.h"
#include "Navigation/InteractiveNavigatorIfc.h"
#include "SettingListProxyModel.h"

/**
 * ViewModel for the settings page.
 *
 * It manages the selected index of the settings list and loads the corresponding content.
 */
class SettingPageViewModel : public QObject {
    Q_OBJECT

    Q_PROPERTY(QAbstractItemModel* items READ settingsModel CONSTANT)
    Q_PROPERTY(uint32_t selectedIndex READ getSelectedIndex WRITE setSelectedIndex NOTIFY selectedIndexChanged)
    Q_PROPERTY(QString currentPageTitle READ getCurrentPageTitle NOTIFY currentPageTitleChanged)
    Q_PROPERTY(QString currentPageComponent READ getCurrentPageComponent NOTIFY currentPageComponentChanged)

public:

    explicit SettingPageViewModel(ConfigurationRegistryIfc& registry, SettingListProxyModel& model);
    ~SettingPageViewModel() final = default;

    /**
     * Returns the settings model.
     * @return The settings model.
     */
    QAbstractItemModel* settingsModel() const {
        return m_settingsModel;
    }

    /**
     * Gets the selected index.
     * @return The selected index.
     */
    uint32_t getSelectedIndex() const {
        return m_selectedIndex;
    }

    /**
     * Sets the selected index and loads the corresponding content.
     * @param index The index to set.
     */
    void setSelectedIndex(uint32_t index);

    /**
     * Gets the current page title.
     * @return The current page title.
     */
    QString getCurrentPageTitle() const {
        return m_currentPageTitle;
    }

    /**
     * Gets the current page component.
     * @return The current page component.
     */
    QString getCurrentPageComponent() const {
        return m_currentPageComponent;
    }

signals:
    void selectedIndexChanged();
    void currentPageComponentChanged();
    void currentPageTitleChanged();

private:

    void loadContent(uint32_t const index);
    std::string getMetaPath(uint32_t const index) const;

    ConfigurationRegistryIfc& m_registry;
    SettingListProxyModel* m_settingsModel;

    uint32_t m_selectedIndex;
    QString m_currentPageTitle;
    QString m_currentPageComponent;
};

#endif