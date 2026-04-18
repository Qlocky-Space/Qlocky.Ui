declare_module(Radio)

set(MODULE_SRC
    ${CMAKE_CURRENT_LIST_DIR}/api/RadioModule.cpp
    ${CMAKE_CURRENT_LIST_DIR}/api/RadioModule.h
    ${CMAKE_CURRENT_LIST_DIR}/api/RadioPlayerIfc.h
    ${CMAKE_CURRENT_LIST_DIR}/api/RadioEntity.h
    ${CMAKE_CURRENT_LIST_DIR}/api/RadioSearchFilter.h
    ${CMAKE_CURRENT_LIST_DIR}/api/RadioRepositoryIfc.h
    ${CMAKE_CURRENT_LIST_DIR}/api/RadioSearchResult.h
    ${CMAKE_CURRENT_LIST_DIR}/api/RadioServiceIfc.h
    ${CMAKE_CURRENT_LIST_DIR}/api/RadioSourceProviderIfc.h
    ${CMAKE_CURRENT_LIST_DIR}/api/events/RadioFavoriteAddedEvent.h
    ${CMAKE_CURRENT_LIST_DIR}/api/events/RadioFavoriteRemovedEvent.h
    ${CMAKE_CURRENT_LIST_DIR}/api/events/RadioFavoriteUpdatedEvent.h
    ${CMAKE_CURRENT_LIST_DIR}/api/events/RadioPlaybackStateChangedEvent.h
    ${CMAKE_CURRENT_LIST_DIR}/api/events/RadioSelectionChangedEvent.h

    ${CMAKE_CURRENT_LIST_DIR}/internal/RadioPlayer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/internal/RadioPlayer.h
    ${CMAKE_CURRENT_LIST_DIR}/internal/RadioRepository.cpp
    ${CMAKE_CURRENT_LIST_DIR}/internal/RadioRepository.h
    ${CMAKE_CURRENT_LIST_DIR}/internal/RadioService.cpp
    ${CMAKE_CURRENT_LIST_DIR}/internal/RadioService.h
    ${CMAKE_CURRENT_LIST_DIR}/internal/RadioBrowserProvider.cpp
    ${CMAKE_CURRENT_LIST_DIR}/internal/RadioBrowserProvider.h
    ${CMAKE_CURRENT_LIST_DIR}/internal/RadioBrowserAPIv1.h

    ${CMAKE_CURRENT_LIST_DIR}/view/RadioCardViewModel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/view/RadioCardViewModel.h
    ${CMAKE_CURRENT_LIST_DIR}/view/RadioSettingsPageViewModel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/view/RadioSettingsPageViewModel.h
    ${CMAKE_CURRENT_LIST_DIR}/api/RadioSourceViewModelBase.h
    ${CMAKE_CURRENT_LIST_DIR}/api/RadioSourceViewModelBase.cpp
    ${CMAKE_CURRENT_LIST_DIR}/view/RadioSourceSelectDialogViewModel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/view/RadioSourceSelectDialogViewModel.h
)

set(MODULE_QML_SRC
    qml/RadioCard.qml
    qml/RadioSourceSelectDialog.qml
    qml/RadioSettings.qml
    qml/internal/RadioSourceFavorites.qml
    qml/internal/RadioSourceLibrary.qml
    qml/internal/RadioSourceItem.qml
    qml/internal/RadioSourceSearch.qml
)

set(MODULE_LINK
    qlocky::Os
    qlocky::Device
    qlocky::RestAPI
    qlocky::Ui
    qlocky::Persistence
    qlocky::Configuration
)

setup_module()
