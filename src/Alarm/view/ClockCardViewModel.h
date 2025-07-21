#ifndef CLOCK_CARD_VIEW_MODEL_H
#define CLOCK_CARD_VIEW_MODEL_H

#include <api/Mediator.h>
#include <QObject>

#include "TimeChangedEvent.h"

/**
 * View model for the clock card.
 */
class ClockCardViewModel : public QObject {
    Q_OBJECT

    Q_PROPERTY(uint64_t timestamp READ getTimestamp NOTIFY timestampChanged)

public:

    /**
     * Constructor for ClockCardViewModel.
     * @param mediator The mediator to communicate with other components.
     */
    ClockCardViewModel(Mediator& mediator);

    /**
     * Returns the date.
     * @return The current date and time.
     */
    uint64_t getTimestamp() const {
        return m_timestamp;
    }

signals:
    void timestampChanged();

private:

    void onTimeChanged(TimeChangedEvent const& event);

    uint64_t m_timestamp;
};

#endif