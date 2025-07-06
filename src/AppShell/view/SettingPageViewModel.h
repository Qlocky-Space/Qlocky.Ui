#ifndef QLOCKY_SETTING_PAGE_VIEWMODEL_H
#define QLOCKY_SETTING_PAGE_VIEWMODEL_H

#include <QObject>
#include <QString>
#include <QtQml/qqmlregistration.h>
#include <QWindow>

#include "Navigation/InteractiveNavigatorIfc.h"

class SettingPageViewModel : public QObject {
    Q_OBJECT

public:

    explicit SettingPageViewModel();

private:
};

#endif