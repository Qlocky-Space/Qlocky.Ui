#ifndef PERSISTENCE_IFC_H
#define PERSISTENCE_IFC_H

#include <string>

#include "KeyValueDatabaseIfc.h"

/**
 * Interface for a persistence service managing multiple persistence contexts.
 *
 * The PersistenceServiceIfc class provides an interface for initializing a persistence service,
 * accessing key-value database contexts by namespace, and listening for persistence changes.
 * It is designed to be implemented by classes that manage persistent storage of application data.
 */
class PersistenceServiceIfc {
public:

    /**
     * Initialize preferences service
     */
    virtual void initialize() = 0;

    /**
     * Get or create a KeyValueDatabaseIfc by namespace.
     * @param ns The namespace string.
     * @return Reference to the KeyValueDatabaseIfc.
     */
    virtual KeyValueDatabaseIfc& getContext(std::string const& ns) = 0;

    virtual ~PersistenceServiceIfc() = default;
};

#endif