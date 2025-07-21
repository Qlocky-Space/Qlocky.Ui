#include "InteractiveProvider.h"

InteractiveProvider::InteractiveProvider(Mediator& mediator) {
    mediator.subscribe<NavigateToEvent>(this, &InteractiveProvider::navigateToQlocky);
}

void InteractiveProvider::navigateToQlocky(NavigateToEvent const& event) {
    InteractiveMeta::Type const type {event.getMeta().type};

    switch (type) {
        case InteractiveMeta::Type::Dialog:
            openDialog(event);
            break;
        case InteractiveMeta::Type::Page:
            openPage(event);
            break;

        default:
            // not supported
            break;
    }
}

void InteractiveProvider::openPage(NavigateToEvent const& event) {
    InteractiveQmlData* data = new InteractiveQmlData();
    fillData(*data, event);

    emit fireOpenPage(data);
}

void InteractiveProvider::openDialog(NavigateToEvent const& event) {
    InteractiveQmlData* data = new InteractiveQmlData();
    fillData(*data, event);

    emit fireOpenDialog(data);
}

void InteractiveProvider::cleanup(InteractiveQmlData* data) {
    // because emit fireOpenPage or fireOpenDialog is not guaranteed to by
    // blocked, a callback is used to ensure the data is cleaned up
    delete data;
}

void InteractiveProvider::fillData(InteractiveQmlData& data, NavigateToEvent const& event) {
    data.setValue("path", QString::fromStdString(std::string {event.getMeta().qmlPath}));

    QVariantMap params {};
    UriQuery::Params const& uriParams {event.getUri().params()};
    for (auto& it : uriParams) {
        params[QString::fromStdString(it.first)] = QVariant {QString::fromStdString(it.second)};
    }
    data.setValue("params", params);
}
