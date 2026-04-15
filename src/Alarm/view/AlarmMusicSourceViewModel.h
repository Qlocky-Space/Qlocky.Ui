#ifndef ALARM_MUSIC_SOURCE_VIEW_MODEL_H
#define ALARM_MUSIC_SOURCE_VIEW_MODEL_H

#include <RadioSourceViewModelBase.h>

/**
 * ViewModel for the alarm music source selector.
 *
 * Provides radio source search, favourites and selection tracking without
 * applying a global radio selection side effect. The confirmed selection is
 * returned to the caller via QML bindings rather than written to the radio
 * service.
 *
 * @see RadioSourceViewModelBase
 */
class AlarmMusicSourceViewModel : public RadioSourceViewModelBase {
    Q_OBJECT

public:

    AlarmMusicSourceViewModel(Mediator& mediator, RadioServiceIfc& radioService);
    ~AlarmMusicSourceViewModel() final = default;
};

#endif
