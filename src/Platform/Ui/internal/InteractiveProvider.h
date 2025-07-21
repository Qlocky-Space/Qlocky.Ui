#ifndef UI_INTERACTIVE_PROVIDER_H
#define UI_INTERACTIVE_PROVIDER_H

#include <Mediator.h>
#include <QObject>
#include <QVariantMap>

#include "Navigation/InteractiveNavigatorIfc.h"
#include "Navigation/InteractiveUriRegistryIfc.h"
#include "Navigation/NavigateToEvent.h"

class InteractiveQmlData : public QObject {
    Q_OBJECT

public:

    using QObject::QObject;

    Q_INVOKABLE QVariant value(QString const& key) const {
        return m_data.value(key);
    }

    Q_INVOKABLE void setValue(QString const& key, QVariant const& val) {
        m_data[key] = val;
    }

    Q_INVOKABLE QVariant data() const {
        return m_data;
    }

private:

    QVariantMap m_data;
};

/**
 * Manages all qlocky scheme uri
 */
class InteractiveProvider : public QObject {
    Q_OBJECT

public:

    InteractiveProvider(Mediator& mediator);

    /**
     * Called when the QML dialog is completed.
     */
    Q_INVOKABLE void cleanup(InteractiveQmlData* data);

signals:
    void fireOpenPage(InteractiveQmlData* data);
    void fireOpenDialog(InteractiveQmlData* data);

private:

    void navigateToQlocky(NavigateToEvent const& event);
    void openPage(NavigateToEvent const& event);
    void openDialog(NavigateToEvent const& event);

    void fillData(InteractiveQmlData& data, NavigateToEvent const& event);
};

#endif