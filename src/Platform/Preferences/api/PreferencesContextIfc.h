#ifndef PREFERENCES_CONTEXT_IFC_H
#define PREFERENCES_CONTEXT_IFC_H

#include <string>

/**
 * A preference context which can be used to set/get preferences from a group.
 * A setting is defined as key/value pair
 */
class PreferencesContextIfc {
public:

    /**
     * Reads the string with key
     * @param key the key
     * @param defaultValue the default value if key does not exists
     * @return the value
     */
    virtual std::string getString(std::string const& key, std::string const& defaultValue) = 0;

    virtual ~PreferencesContextIfc() = default;
};

#endif