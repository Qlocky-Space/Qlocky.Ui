#include "RadioSourceSelectDialogViewModel.h"

#include "RadioServiceIfc.h"

RadioSourceSelectDialogViewModel::RadioSourceSelectDialogViewModel(Mediator& mediator, RadioServiceIfc& radioService) :
    RadioSourceViewModelBase(mediator, radioService) {
}

void RadioSourceSelectDialogViewModel::chooseSelectedStation() {
    auto const radio = findRadioById(selectedSource());
    if (!radio.has_value()) {
        return;
    }

    m_radioService.selectRadio(*radio);
}
