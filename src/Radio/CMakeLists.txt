declare_module(Radio)

set(MODULE_SRC
    ${CMAKE_CURRENT_LIST_DIR}/api/RadioModule.cpp
    ${CMAKE_CURRENT_LIST_DIR}/api/RadioModule.h
    ${CMAKE_CURRENT_LIST_DIR}/api/StationProfile.h
    ${CMAKE_CURRENT_LIST_DIR}/api/events/StationAddedEvent.h
    ${CMAKE_CURRENT_LIST_DIR}/api/events/StationRemovedEvent.h

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
    qlocky::Ui
    qlocky::Widget
    qlocky::Persistence
    qlocky::Configuration
)

setup_module()
