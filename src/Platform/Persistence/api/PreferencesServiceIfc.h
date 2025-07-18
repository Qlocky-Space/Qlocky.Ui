#ifndef PERSISTENCE_IFC_H
#define PERSISTENCE_IFC_H

#include <string>

#include "PreferencesContextIfc.h"

/**
 * PreferencesService manages multiple preferences contexts,
 * provides accessors and listeners for preference changes.
 */
class PreferencesServiceIfc {
public:

    /**
     * Initialize preferences service
     */
    virtual void initialize() = 0;

    /**
     * Get or create a PreferencesContextIfc by namespace.
     * @param ns The namespace string.
     * @return Reference to the PreferencesContextIfc.
     */
    virtual PreferencesContextIfc& getContext(std::string const& ns) = 0;

    virtual ~PreferencesServiceIfc() = default;
};

#endif