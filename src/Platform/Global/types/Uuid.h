#ifndef SRC_PLATFORM_GLOBAL_TYPES_UUID_H
#define SRC_PLATFORM_GLOBAL_TYPES_UUID_H

#include <QString>
#include <QUuid>
#include <string>

/**
 * Represents a UUID/GUID value.
 *
 * The class accepts canonical UUID strings such as
 * "550e8400-e29b-41d4-a716-446655440000", with optional braces or the
 * "urn:uuid:" prefix, and normalizes valid values to lowercase canonical form.
 */
class Uuid {
public:

    /**
     * Type alias for the UUID variant.
     */
    using Variant = QUuid::Variant;

    /**
     * Type alias for the UUID version.
     */
    using Version = QUuid::Version;

    /**
     * Default constructor. Creates an invalid UUID.
     */
    Uuid() = default;

    /**
     * Construct a UUID from a string.
     * @param str UUID string.
     */
    explicit Uuid(std::string const& str);

    /**
     * Construct a UUID from a string literal.
     * @param str UUID string.
     */
    explicit Uuid(char const* str);

    /**
     * Construct a UUID from a Qt string.
     * @param str UUID string.
     */
    explicit Uuid(QString const& str);

    /**
     * Create a random version 4 UUID.
     * @return Random UUID.
     */
    static Uuid createRandom();

    /**
     * Check whether this instance contains a syntactically valid UUID.
     * @return True if the UUID was parsed successfully.
     */
    bool isValid() const;

    /**
     * Check whether this UUID is the nil UUID.
     * @return True if the UUID is valid and all bits are zero.
     */
    bool isNil() const;

    /**
     * Get the UUID variant.
     * @return UUID variant or QUuid::VarUnknown when invalid.
     */
    Variant variant() const;

    /**
     * Get the UUID version.
     * @return UUID version or QUuid::VerUnknown when invalid.
     */
    Version version() const;

    /**
     * Get the UUID in canonical lowercase string form.
     * @return Canonical UUID string without braces, or an empty string when invalid.
     */
    std::string toString() const;

    /**
     * Get the UUID in canonical lowercase Qt string form.
     * @return Canonical UUID string without braces, or an empty string when invalid.
     */
    QString toQString() const;

    /**
     * Get the underlying Qt UUID value.
     * @return Qt UUID value.
     */
    QUuid toQt() const;

    inline bool operator==(Uuid const& uuid) const {
        return m_isValid == uuid.m_isValid && m_uuid == uuid.m_uuid;
    }

    inline bool operator!=(Uuid const& uuid) const {
        return !(*this == uuid);
    }

private:

    explicit Uuid(QUuid const& uuid);

    QUuid m_uuid;
    bool m_isValid {false};
};

template<>
struct std::hash<Uuid> {
    std::size_t operator()(Uuid const& uuid) const noexcept {
        return std::hash<std::string> {}(uuid.toString());
    }
};

#endif // SRC_PLATFORM_GLOBAL_TYPES_UUID_H