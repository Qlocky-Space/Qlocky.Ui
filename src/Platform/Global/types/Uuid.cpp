#include "Uuid.h"

#include <QRegularExpression>

namespace {

QString normalizeUuid(QString str) {
    static QRegularExpression const uuidExpression {
        R"(^(?:urn:uuid:)?\{?([0-9a-fA-F]{8}-[0-9a-fA-F]{4}-[0-9a-fA-F]{4}-[0-9a-fA-F]{4}-[0-9a-fA-F]{12})\}?$)",
        QRegularExpression::CaseInsensitiveOption};

    str = str.trimmed();

    auto const match = uuidExpression.match(str);
    if (!match.hasMatch()) {
        return {};
    }

    return match.captured(1).toLower();
}

} // namespace

Uuid::Uuid(std::string const& str) :
    Uuid {QString::fromStdString(str)} {
}

Uuid::Uuid(char const* str) :
    Uuid {QString::fromUtf8(str != nullptr ? str : "")} {
}

Uuid::Uuid(QString const& str) :
    m_uuid {},
    m_isValid {false} {
    auto const normalizedUuid {normalizeUuid(str)};
    if (normalizedUuid.isEmpty()) {
        return;
    }

    m_uuid = QUuid::fromString("{" + normalizedUuid + "}");
    m_isValid = !m_uuid.isNull() || normalizedUuid == QStringLiteral("00000000-0000-0000-0000-000000000000");
}

Uuid::Uuid(QUuid const& uuid) :
    m_uuid {uuid},
    m_isValid {true} {
}

Uuid Uuid::createRandom() {
    return Uuid {QUuid::createUuid()};
}

bool Uuid::isValid() const {
    return m_isValid;
}

bool Uuid::isNil() const {
    return m_isValid && m_uuid.isNull();
}

Uuid::Variant Uuid::variant() const {
    return m_isValid ? m_uuid.variant() : QUuid::VarUnknown;
}

Uuid::Version Uuid::version() const {
    return m_isValid ? m_uuid.version() : QUuid::VerUnknown;
}

std::string Uuid::toString() const {
    return toQString().toStdString();
}

QString Uuid::toQString() const {
    if (!m_isValid) {
        return {};
    }

    return m_uuid.toString(QUuid::WithoutBraces).toLower();
}

QUuid Uuid::toQt() const {
    return m_uuid;
}