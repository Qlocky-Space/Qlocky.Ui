#ifndef PREFERENCES_CONTEXT_H
#define PREFERENCES_CONTEXT_H

#include <memory>
#include <rocksdb/db.h>
#include <string>

#include "PreferencesContextIfc.h"

/**
 * @see PreferencesContextIfc
 */
class PreferencesContext : public PreferencesContextIfc {
public:

    PreferencesContext(std::shared_ptr<rocksdb::DB> db, std::string const& ns);

    /**
     * @see PreferencesContextIfc::getString
     */
    std::string getString(std::string const& key, std::string const& defaultValue) final;

private:

    std::string getInternalKey(std::string const& key);

    std::shared_ptr<rocksdb::DB> m_db;
    std::string const m_ns;
};

#endif