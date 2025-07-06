#include "InteractiveProvider.h"

InteractiveProvider::InteractiveProvider(Mediator& mediator) {
    mediator.subscribe<NavigateToEvent>(this, &InteractiveProvider::navigateToQlocky);
}

void InteractiveProvider::navigateToQlocky(NavigateToEvent const& event) {
    InteractiveMeta::Type const type {event.getMeta().type};

    switch (type) {
        case InteractiveMeta::Type::Dialog:
            openDialog(event.getMeta());
            break;
        case InteractiveMeta::Type::Page:
            openPage(event.getMeta());
            break;

        default:
            // not supported
            break;
    }
}

void InteractiveProvider::openPage(InteractiveMeta const& meta) {
    InteractiveQmlData data {};
    fillData(data, meta);

    emit fireOpenPage(&data);
}

void InteractiveProvider::openDialog(InteractiveMeta const& meta) {
    InteractiveQmlData data {};
    fillData(data, meta);

    emit fireOpenDialog(&data);
}

void InteractiveProvider::fillData(InteractiveQmlData& data, InteractiveMeta const& meta) {
    data.setValue("path", QString::fromStdString(std::string {meta.qmlPath}));
}
