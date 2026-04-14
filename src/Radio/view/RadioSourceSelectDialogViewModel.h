#ifndef RADIO_SOURCE_SELECT_DIALOG_VIEW_MODEL_H
#define RADIO_SOURCE_SELECT_DIALOG_VIEW_MODEL_H

#include "RadioSourceViewModelBase.h"

/**
 * ViewModel for the radio source selection dialog.
 *
 * Extends RadioSourceViewModelBase with the ability to apply the selected
 * station as the globally active radio source.
 *
 * @see RadioSourceViewModelBase
 */
class RadioSourceSelectDialogViewModel : public RadioSourceViewModelBase {
    Q_OBJECT

public:

    RadioSourceSelectDialogViewModel(Mediator& mediator, RadioServiceIfc& radioService);
    ~RadioSourceSelectDialogViewModel() final = default;

    /**
     * Applies the currently highlighted station as the globally active radio source.
     */
    Q_INVOKABLE void chooseSelectedStation();
};

#endif
