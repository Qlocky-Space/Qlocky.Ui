declare_module(Radio)

set(MODULE_SRC
    ${CMAKE_CURRENT_LIST_DIR}/api/RadioModule.cpp
    ${CMAKE_CURRENT_LIST_DIR}/api/RadioModule.h
    ${CMAKE_CURRENT_LIST_DIR}/api/StationEntity.h
    ${CMAKE_CURRENT_LIST_DIR}/api/StationFilter.h
    ${CMAKE_CURRENT_LIST_DIR}/api/StationProfile.h
    ${CMAKE_CURRENT_LIST_DIR}/api/StationProviderIfc.h
    ${CMAKE_CURRENT_LIST_DIR}/api/StationRepositoryIfc.h
    ${CMAKE_CURRENT_LIST_DIR}/api/StationServiceIfc.h
    ${CMAKE_CURRENT_LIST_DIR}/api/events/StationAddedEvent.h
    ${CMAKE_CURRENT_LIST_DIR}/api/events/StationRemovedEvent.h
    ${CMAKE_CURRENT_LIST_DIR}/api/events/StationServiceStateChangedEvent.h
    ${CMAKE_CURRENT_LIST_DIR}/api/events/StationUpdatedEvent.h

    ${CMAKE_CURRENT_LIST_DIR}/internal/RadioBrowserStationProvider.cpp
    ${CMAKE_CURRENT_LIST_DIR}/internal/RadioBrowserStationProvider.h
    ${CMAKE_CURRENT_LIST_DIR}/internal/RadioBrowserAPIv1.h
    ${CMAKE_CURRENT_LIST_DIR}/internal/StationRepository.cpp
    ${CMAKE_CURRENT_LIST_DIR}/internal/StationRepository.h
    ${CMAKE_CURRENT_LIST_DIR}/internal/StationMapper.h
    ${CMAKE_CURRENT_LIST_DIR}/internal/StationService.cpp
    ${CMAKE_CURRENT_LIST_DIR}/internal/StationService.h

    ${CMAKE_CURRENT_LIST_DIR}/view/RadioSettingsPageViewModel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/view/RadioSettingsPageViewModel.h
    ${CMAKE_CURRENT_LIST_DIR}/view/StationListModel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/view/StationListModel.h
    ${CMAKE_CURRENT_LIST_DIR}/view/StationViewModel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/view/StationViewModel.h
)

set(MODULE_QML_SRC
    qml/RadioCard.qml
    qml/RadioSettings.qml
)

set(MODULE_QML_RESOURCES
    resources/play.png
    resources/skip.png
    resources/previous.png
)

set(MODULE_LINK
    qlocky::RestAPI
    qlocky::Ui
    qlocky::Widget
    qlocky::Persistence
    qlocky::Configuration
)

setup_module()
