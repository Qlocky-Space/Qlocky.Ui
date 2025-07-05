#ifndef WIDGET_LIST_MODEL_H
#define WIDGET_LIST_MODEL_H

#include <memory>
#include <QAbstractListModel>
#include <QString>
#include <QVector>
#include <WidgetMetadata.h>

#include "WidgetModel.h"

/**
 * List model representing widgets for use in QML views.
 * Provides data roles for QML Repeaters and ListViews.
 */
class WidgetListModel : public QAbstractListModel {
    Q_OBJECT

public:

    enum WidgetRoles {
        SourceRole = Qt::UserRole + 1,
        RowRole,
        RowSpanRole,
        ColumnRole,
        ColumnSpanRole
    };

    WidgetListModel();

    /**
     * Returns the number of widgets in the model.
     */
    int rowCount(QModelIndex const& parent = QModelIndex()) const override;

    /**
     * Returns the data for a given index and role.
     */
    QVariant data(QModelIndex const& index, int role = Qt::DisplayRole) const override;

    /**
     * Returns the role names for QML access.
     */
    QHash<int, QByteArray> roleNames() const override;

    /**
     * Adds a widget to the model.
     * @param widget The widget to add.
     */
    Q_INVOKABLE void addWidget(WidgetMetadata const& widget);

    /**
     * Clears all widgets from the model.
     */
    Q_INVOKABLE void clear();

private:

    QVector<std::shared_ptr<WidgetModel>> m_widgets;
};

#endif