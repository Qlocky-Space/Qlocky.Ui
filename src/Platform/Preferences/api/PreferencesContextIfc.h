#ifndef PREFERENCES_CONTEXT_IFC_H
#define PREFERENCES_CONTEXT_IFC_H

#include <cinttypes>
#include <string>

#include "PreferencesItem.h"
#include "PreferencesKey.h"

/**
 * A preference context which can be used to set/get preferences from a group.
 * A setting is defined as key/value pair.
 */
class PreferencesContextIfc {
public:

    /**
     * Reads the string value for a given key.
     * @param key The key to look up.
     * @param defaultValue The value to return if the key does not exist.
     * @return The value associated with the key, or the default value.
     */
    virtual std::string getString(PreferencesItem<RawString> const& item) = 0;

    /**
     * Sets a string value for a given key.
     * @param key The key to set.
     * @param value The value to associate with the key.
     */
    virtual void setString(PreferencesItem<RawString> const& item, std::string const& value) = 0;

    /**
     * Reads the integer value for a given key.
     * @param key The key to look up.
     * @param defaultValue The value to return if the key does not exist.
     * @return The value associated with the key, or the default value.
     */
    virtual bool getBool(PreferencesItem<bool> const& item) = 0;

    /**
     * Sets a boolean value for a given key.
     * @param key The key to set.
     * @param value The boolean value to associate with the key.
     */
    virtual void setBool(PreferencesItem<bool> const& item, bool const value) = 0;

    /**
     * Reads the integer value for a given key.
     * @param key The key to look up.
     * @param defaultValue The value to return if the key does not exist.
     * @return The value associated with the key, or the default value.
     */
    virtual int getInt(PreferencesItem<int32_t> const& item) = 0;

    /**
     * Sets an integer value for a given key.
     * @param key The key to set.
     * @param value The integer value to associate with the key.
     */
    virtual void setInt(PreferencesItem<int32_t> const& item, int32_t const value) = 0;

    virtual ~PreferencesContextIfc() = default;
};

#endif