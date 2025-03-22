#ifndef QLOCKY_CARD_INFO_H
#define QLOCKY_CARD_INFO_H

#include <cstdint>
#include <string>

/**
 * Immitable CardInfo contains information about a card layout.
 */
struct CardInfo final {

    /**
     * Constructor
     *
     * @param source Source of the card
     * @param row Row of the card
     * @param rowSpan Row span of the card
     * @param column Column of the card
     * @param columnSpan Column span of the card
     */
    CardInfo(std::string const& source, uint32_t row, uint32_t rowSpan, uint32_t column, uint32_t columnSpan) :
        m_source {source},
        m_row {row},
        m_rowSpan {rowSpan},
        m_column {column},
        m_columnSpan {columnSpan} {
    }

    /**
     * Get the source of the card
     *
     * @return Source of the card
     */
    std::string const& getSource() const {
        return m_source;
    }

    /**
     * Get the row of the card
     *
     * @return Row of the card
     */
    uint32_t getRow() const {
        return m_row;
    }

    /**
     * Get the row span of the card
     *
     * @return Row span of the card
     */
    uint32_t getRowSpan() const {
        return m_rowSpan;
    }

    /**
     * Get the column of the card
     *
     * @return Column of the card
     */
    uint32_t getColumn() const {
        return m_column;
    }

    /**
     * Get the column span of the card
     *
     * @return Column span of the card
     */
    uint32_t getColumnSpan() const {
        return m_columnSpan;
    }

private:

    std::string const m_source;
    uint32_t const m_row;
    uint32_t const m_rowSpan;
    uint32_t const m_column;
    uint32_t const m_columnSpan;
};

#endif