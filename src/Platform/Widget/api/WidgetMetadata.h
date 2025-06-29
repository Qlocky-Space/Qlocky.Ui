#ifndef WIDGET_DESCRIPTION_IFC_H
#define WIDGET_DESCRIPTION_IFC_H

#include <cstdint>
#include <string>

/**
 * This interface defines the structure for describing widgets within the system.
 * It provides a way to encapsulate the layout and metadata of a widget, allowing
 * for consistent management and instantiation of widgets across the application.
 */
struct WidgetLayout final {
public:

    WidgetLayout() = default;

    WidgetLayout(std::string const& source, uint32_t row, uint32_t rowSpan, uint32_t column, uint32_t columnSpan) :
        Source(source),
        Row(row),
        RowSpan(rowSpan),
        Column(column),
        ColumnSpan(columnSpan) {
    }

    std::string Source;
    uint32_t Row;
    uint32_t RowSpan;
    uint32_t Column;
    uint32_t ColumnSpan;
};

/**
 * This class encapsulates the metadata for a widget, including its name and layout.
 */
struct WidgetMetadata final {
public:

    WidgetMetadata() = default;

    WidgetMetadata(std::string const& name, WidgetLayout const& layout) :
        m_name(name),
        m_layout(layout) {
    }

    std::string const& getName() const {
        return m_name;
    }
    std::string const& getSource() const {
        return m_layout.Source;
    }
    uint32_t getRow() const {
        return m_layout.Row;
    }
    uint32_t getRowSpan() const {
        return m_layout.RowSpan;
    }
    uint32_t getColumn() const {
        return m_layout.Column;
    }
    uint32_t getColumnSpan() const {
        return m_layout.ColumnSpan;
    }

private:

    std::string m_name;
    WidgetLayout m_layout;
};

#endif