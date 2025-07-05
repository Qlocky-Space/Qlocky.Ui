#ifndef QLOCKY_SETTING_PAGE_VIEWMODEL_H
#define QLOCKY_SETTING_PAGE_VIEWMODEL_H

#include <QObject>
#include <QString>
#include <QtQml/qqmlregistration.h>
#include <QWindow>

#include "Navigation/NavigateBackCommand.h"
#include "Navigation/NavigatorIfc.h"

class SettingPageViewModel : public QObject {
    Q_OBJECT
    Q_PROPERTY(QmlCommandBase* navigateBack READ getNavigateBackCommand CONSTANT)

public:

    explicit SettingPageViewModel(NavigateBackCommand& navigateBackCommand);

    QmlCommandBase* getNavigateBackCommand() const {
        return &m_navigateBackCommand;
    }

private:

    NavigateBackCommand& m_navigateBackCommand;
};

#endif