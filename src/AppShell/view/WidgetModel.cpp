#include "WidgetModel.h"

WidgetModel::WidgetModel(QString const& source,
    uint32_t row, uint32_t rowSpan,
    uint32_t column, uint32_t columnSpan,
    QObject* parent) :
    QObject {parent},
    m_source {source},
    m_row {row},
    m_rowSpan {rowSpan},
    m_column {column},
    m_columnSpan {columnSpan} {
}

QString WidgetModel::source() const {
    return m_source;
}

uint32_t WidgetModel::row() const {
    return m_row;
}

uint32_t WidgetModel::rowSpan() const {
    return m_rowSpan;
}

uint32_t WidgetModel::column() const {
    return m_column;
}

uint32_t WidgetModel::columnSpan() const {
    return m_columnSpan;
}