#ifndef QLOCKY_SETTING_PAGE_VIEWMODEL_H
#define QLOCKY_SETTING_PAGE_VIEWMODEL_H

#include <QObject>
#include <QString>
#include <QtQml/qqmlregistration.h>
#include <QWindow>

#include "Navigation/InteractiveNavigatorIfc.h"
#include "NetworkRepositoryIfc.h"
#include "NetworkServiceIfc.h"

class SettingPageViewModel : public QObject {
    Q_OBJECT

public:

    explicit SettingPageViewModel(NetworkServiceIfc& networkService, NetworkRepositoryIfc& networkRepository);

    // TODO remove demo methods
    Q_INVOKABLE void networkDisconnect();
    Q_INVOKABLE void networkConnect();

private:

    NetworkServiceIfc& m_networkService;
    NetworkRepositoryIfc& m_networkRepository;
};

#endif