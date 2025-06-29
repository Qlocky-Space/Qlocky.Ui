#include "WidgetListViewModel.h"

WidgetListViewModel::WidgetListViewModel() :
    QAbstractListModel {nullptr}, m_widgets {} {
}

int WidgetListViewModel::rowCount(QModelIndex const& parent) const {
    if (parent.isValid()) {
        return 0;
    }
    return m_widgets.count();
}

QVariant WidgetListViewModel::data(QModelIndex const& index, int role) const {
    if (!index.isValid() || index.row() < 0 || index.row() >= m_widgets.size()) {
        return {};
    }

    std::shared_ptr<WidgetModel> widget = m_widgets.at(index.row());

    switch (role) {
        case SourceRole:
            return widget->source();
        case RowRole:
            return widget->row();
        case RowSpanRole:
            return widget->rowSpan();
        case ColumnRole:
            return widget->column();
        case ColumnSpanRole:
            return widget->columnSpan();
        default:
            return {};
    }
}

QHash<int, QByteArray> WidgetListViewModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[SourceRole] = "source";
    roles[RowRole] = "row";
    roles[RowSpanRole] = "rowSpan";
    roles[ColumnRole] = "column";
    roles[ColumnSpanRole] = "columnSpan";
    return roles;
}

void WidgetListViewModel::addWidget(WidgetMetadata const& widget) {
    std::shared_ptr<WidgetModel> model {std::make_shared<WidgetModel>(
        QString::fromStdString(widget.getSource()),
        widget.getRow(),
        widget.getRowSpan(),
        widget.getColumn(),
        widget.getColumnSpan())};

    beginInsertRows(QModelIndex(), m_widgets.size(), m_widgets.size());
    m_widgets.append(model);
    endInsertRows();
}

void WidgetListViewModel::clear() {
    if (!m_widgets.isEmpty()) {
        beginResetModel();
        m_widgets.clear();
        endResetModel();
    }
}