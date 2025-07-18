#ifndef PERSISTENCE_CONTEXT_IFC_H
#define PERSISTENCE_CONTEXT_IFC_H

#include <cinttypes>
#include <string>
#include <types/RawString.h>

#include "PersistenceItem.h"
#include "PersistenceKey.h"

/**
 * Interface for a key-value database that provides methods to get and set preferences.
 */
class KeyValueDatabaseIfc {
public:

    /**
     * Reads the string value for a given key.
     * @param key The key to look up.
     * @param defaultValue The value to return if the key does not exist.
     * @return The value associated with the key, or the default value.
     */
    virtual std::string getString(PersistenceItem<RawString> const& item) = 0;

    /**
     * Sets a string value for a given key.
     * @param key The key to set.
     * @param value The value to associate with the key.
     */
    virtual void setString(PersistenceItem<RawString> const& item, std::string const& value) = 0;

    /**
     * Reads the boolean value for a given key.
     * @param key The key to look up.
     * @param defaultValue The value to return if the key does not exist.
     * @return The value associated with the key, or the default value.
     */
    virtual bool getBool(PersistenceItem<bool> const& item) = 0;

    /**
     * Sets a boolean value for a given key.
     * @param key The key to set.
     * @param value The boolean value to associate with the key.
     */
    virtual void setBool(PersistenceItem<bool> const& item, bool const value) = 0;

    /**
     * Reads the integer value for a given key.
     * @param key The key to look up.
     * @param defaultValue The value to return if the key does not exist.
     * @return The value associated with the key, or the default value.
     */
    virtual int32_t getInt(PersistenceItem<int32_t> const& item) = 0;

    /**
     * Sets an integer value for a given key.
     * @param key The key to set.
     * @param value The integer value to associate with the key.
     */
    virtual void setInt(PersistenceItem<int32_t> const& item, int32_t const value) = 0;

    virtual ~KeyValueDatabaseIfc() = default;
};

#endif