#ifndef APPEARANCE_VIEW_MODEL_H
#define APPEARANCE_VIEW_MODEL_H

#include <QObject>

#include "Mediator.h"

class AppearanceViewModel : public QObject {
    Q_OBJECT

public:

    explicit AppearanceViewModel(Mediator& mediator);
    ~AppearanceViewModel() final = default;

private:
};

#endif // APPEARANCE_VIEW_MODEL_H