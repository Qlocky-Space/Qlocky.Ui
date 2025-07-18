#ifndef PERSISTENCE_CONTEXT_IFC_H
#define PERSISTENCE_CONTEXT_IFC_H

#include <cinttypes>
#include <string>
#include <types/Result.h>

#include "PersistenceKey.h"

/**
 * Represents a list of key-value pairs.
 * Each pair consists of a key and a value, both represented as strings.
 */
using KeyValueList = std::vector<std::pair<std::string, std::string>>;

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
    virtual Result<std::string> getString(PersistenceKey const& item) = 0;

    /**
     * Sets a string value for a given key.
     * @param key The key to set.
     * @param value The value to associate with the key.
     */
    virtual ResultVoid setString(PersistenceKey const& item, std::string const& value) = 0;

    /**
     * Reads the boolean value for a given key.
     * @param key The key to look up.
     * @param defaultValue The value to return if the key does not exist.
     * @return The value associated with the key, or the default value.
     */
    virtual Result<bool> getBool(PersistenceKey const& item) = 0;

    /**
     * Sets a boolean value for a given key.
     * @param key The key to set.
     * @param value The boolean value to associate with the key.
     */
    virtual ResultVoid setBool(PersistenceKey const& item, bool const value) = 0;

    /**
     * Reads the integer value for a given key.
     * @param key The key to look up.
     * @param defaultValue The value to return if the key does not exist.
     * @return The value associated with the key, or the default value.
     */
    virtual Result<int32_t> getInt(PersistenceKey const& item) = 0;

    /**
     * Sets an integer value for a given key.
     * @param key The key to set.
     * @param value The integer value to associate with the key.
     */
    virtual ResultVoid setInt(PersistenceKey const& item, int32_t const value) = 0;

    /**
     * Removes a key-value pair from the database.
     * @param item The key to remove.
     * @return Result indicating success or failure.
     */
    virtual ResultVoid remove(PersistenceKey const& item) = 0;

    /**
     * Reads a list of key-value pairs for a given key.
     * @param item The key to look up.
     * @return A list of key-value pairs associated with the key.
     */
    virtual Result<KeyValueList> getList(PersistenceKey const& item) = 0;

    /**
     * Sets a string value in the list for a given key.
     * @param item The key to set.
     * @param id The identifier for the item in the list.
     * @param value The value to associate with the key.
     * @return Result indicating success or failure.
     */
    virtual ResultVoid setListItem(PersistenceKey const& item, uint32_t const id, std::string const& value) = 0;

    /**
     * Removes a key-value pair from the list.
     * @param item The key to remove.
     * @param id The identifier for the item in the list.
     * @return Result indicating success or failure.
     */
    virtual ResultVoid removeListItem(PersistenceKey const& item, uint32_t const id) = 0;

    virtual ~KeyValueDatabaseIfc() = default;
};

#endif