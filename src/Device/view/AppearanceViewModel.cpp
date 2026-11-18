#include "AppearanceViewModel.h"

#include <algorithm>
#include <QStringList>
#include <QVariantMap>

#include "internal/TimeZoneProvider.h"

AppearanceViewModel::AppearanceViewModel(Mediator& mediator, SystemPreferencesRepositoryIfc& repository, TimeZoneProviderIfc& timeZoneProvider) :
    m_repository {repository},
    m_timeZoneProvider {timeZoneProvider} {
}

void AppearanceViewModel::changeTimeFormat(bool is24HoursFormat) {
    m_repository.setTimeFormat(is24HoursFormat);
    emit timeFormatChanged();
}

bool AppearanceViewModel::getTimeFormatBoolean() const {
    return m_repository.isTimeFormat24Hour();
}

void AppearanceViewModel::resetTimeZoneSelection() {
    m_timeZoneGroups.clear();
    for (TimeZoneGroup const& group : m_timeZoneProvider.getTimeZoneGroups()) {
        QStringList cities {};
        cities.reserve(static_cast<qsizetype>(group.cities.size()));
        for (std::string const& city : group.cities) {
            cities.append(QString::fromStdString(city));
        }

        QString const offset {QString::fromStdString(group.offsetLabel)};
        QString const joinedCities {cities.join(QStringLiteral(", "))};

        QVariantMap entry {};
        entry[QStringLiteral("id")] = QString::fromStdString(group.id);
        entry[QStringLiteral("offset")] = offset;
        entry[QStringLiteral("cities")] = joinedCities;
        entry[QStringLiteral("observesDst")] = group.observesDst;
        // Lower case text used by the QML filter (matches city or offset)
        entry[QStringLiteral("searchText")] = (offset + QStringLiteral(" ") + joinedCities).toLower();
        m_timeZoneGroups.append(entry);
    }
    emit timeZoneGroupsChanged();

    auto const current {m_timeZoneProvider.findGroupByZoneId(m_repository.getTimeZone())};
    setSelectedTimeZoneGroup(current.has_value() ? QString::fromStdString(current->id) : QString {});
}

void AppearanceViewModel::applySelectedTimeZone() {
    if (m_selectedTimeZoneGroup.isEmpty()) {
        return;
    }

    std::string const selected {m_selectedTimeZoneGroup.toStdString()};
    auto const group {m_timeZoneProvider.findGroupByZoneId(selected)};
    if (!group.has_value()) {
        return;
    }

    // Keep the city chosen before if it behaves identically
    std::string const current {m_repository.getTimeZone()};
    if (std::ranges::binary_search(group->zoneIds, current)) {
        return;
    }

    m_repository.setTimeZone(group->id);
    emit timeZoneChanged();
}

QString AppearanceViewModel::getTimeZoneId() const {
    return QString::fromStdString(m_repository.getTimeZone());
}

QString AppearanceViewModel::getTimeZoneLabel() const {
    std::string const zoneId {m_repository.getTimeZone()};
    auto const group {m_timeZoneProvider.findGroupByZoneId(zoneId)};
    if (!group.has_value()) {
        return QString::fromStdString(zoneId);
    }
    return QString::fromStdString(group->offsetLabel + " " + TimeZoneProvider::toCityName(zoneId));
}

QString AppearanceViewModel::getSelectedTimeZoneGroup() const {
    return m_selectedTimeZoneGroup;
}

void AppearanceViewModel::setSelectedTimeZoneGroup(QString const& groupId) {
    if (m_selectedTimeZoneGroup == groupId) {
        return;
    }
    m_selectedTimeZoneGroup = groupId;
    emit selectedTimeZoneGroupChanged();
}

QVariantList AppearanceViewModel::getTimeZoneGroups() const {
    return m_timeZoneGroups;
}
