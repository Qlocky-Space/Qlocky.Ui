#ifndef QLOCKY_PERSISTENCE_SERVICE_H
#define QLOCKY_PERSISTENCE_SERVICE_H

#include <map>
#include <memory>
#include <mutex>
#include <rocksdb/db.h>

#include "PreferencesContextIfc.h"
#include "PreferencesServiceIfc.h"

/**
 * @see PreferencesServiceIfc
 */
class PreferencesService final : public PreferencesServiceIfc {
public:

    /**
     * Constructor
     */
    PreferencesService();

    /**
     * @see PreferencesServiceIfc::initialize
     */
    void initialize() final;

    /**
     * @see PreferencesServiceIfc::getContext
     */
    PreferencesContextIfc& getContext(std::string const& ns) final;

private:

    std::mutex m_mutex;

    std::map<std::string, std::shared_ptr<PreferencesContextIfc>> m_contexts;
    std::shared_ptr<rocksdb::DB> m_db;
};

#endif