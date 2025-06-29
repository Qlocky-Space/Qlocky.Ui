#ifndef WIDGET_MODEL_H
#define WIDGET_MODEL_H

#include <cstdint>
#include <QObject>
#include <QString>

/**
 * Model representing a single widget's metadata for use in QML views.
 * Exposes properties for QML Repeaters and ListViews.
 */
class WidgetModel : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString source READ source CONSTANT)
    Q_PROPERTY(uint32_t row READ row CONSTANT)
    Q_PROPERTY(uint32_t rowSpan READ rowSpan CONSTANT)
    Q_PROPERTY(uint32_t column READ column CONSTANT)
    Q_PROPERTY(uint32_t columnSpan READ columnSpan CONSTANT)

public:

    WidgetModel() = default;
    ~WidgetModel() final = default;

    /**
     * Constructs a WidgetModel with the given properties.
     * @param source The QML source path for the widget.
     * @param row The row position in the layout.
     * @param rowSpan The row span in the layout.
     * @param column The column position in the layout.
     * @param columnSpan The column span in the layout.
     * @param parent The QObject parent.
     */
    explicit WidgetModel(QString const& source,
        uint32_t row,
        uint32_t rowSpan,
        uint32_t column,
        uint32_t columnSpan,
        QObject* parent = nullptr);

    /**
     * Returns the QML source path for the widget.
     */
    QString source() const;

    /**
     * Returns the row position in the layout.
     */
    uint32_t row() const;

    /**
     * Returns the row span in the layout.
     */
    uint32_t rowSpan() const;

    /**
     * Returns the column position in the layout.
     */
    uint32_t column() const;

    /**
     * Returns the column span in the layout.
     */
    uint32_t columnSpan() const;

private:

    QString m_source;
    uint32_t m_row;
    uint32_t m_rowSpan;
    uint32_t m_column;
    uint32_t m_columnSpan;
};

#endif