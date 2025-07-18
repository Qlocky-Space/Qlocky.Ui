#ifndef QLOCKY_PERSISTENCE_SERVICE_H
#define QLOCKY_PERSISTENCE_SERVICE_H

#include <map>
#include <memory>
#include <mutex>
#include <rocksdb/db.h>

#include "KeyValueDatabaseIfc.h"
#include "PersistenceServiceIfc.h"

/**
 * @see PersistenceServiceIfc
 */
class PersistenceService final : public PersistenceServiceIfc {
public:

    /**
     * Constructor
     */
    PersistenceService();

    /**
     * @see PersistenceServiceIfc::initialize
     */
    void initialize() final;

    /**
     * @see PersistenceServiceIfc::getContext
     */
    KeyValueDatabaseIfc& getContext(std::string const& ns) final;

private:

    std::mutex m_mutex;

    std::map<std::string, std::shared_ptr<KeyValueDatabaseIfc>> m_contexts;
    std::shared_ptr<rocksdb::DB> m_db;
};

#endif