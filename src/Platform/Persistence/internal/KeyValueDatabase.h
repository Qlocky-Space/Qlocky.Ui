#ifndef PERSISTENCE_CONTEXT_H
#define PERSISTENCE_CONTEXT_H

#include <memory>
#include <rocksdb/db.h>
#include <string>
#include <types/RawString.h>

#include "KeyValueDatabaseIfc.h"

/**
 * @see KeyValueDatabaseIfc
 *
 * A RocksDb based implementation of the KeyValueDatabaseIfc. This class provides methods to get
 * and set data as key-value pairs. Key-value pairs are stored in a namespace, allowing for
 * separation of different data groups. The keys are prefixed with the namespace to avoid
 * collisions with other data contexts.
 *
 * @note The values are stored as strings, and conversion to/from other types (like int or bool) is handled internally.
 */
class KeyValueDatabase : public KeyValueDatabaseIfc {
public:

    KeyValueDatabase(std::shared_ptr<rocksdb::DB> db, std::string const& ns);

    /**
     * @see KeyValueDatabaseIfc::getString
     */
    std::string getString(PersistenceItem<RawString> const& item) final;

    /**
     * @see KeyValueDatabaseIfc::setString
     */
    void setString(PersistenceItem<RawString> const& item, std::string const& value) final;

    /**
     * @see KeyValueDatabaseIfc::getBool
     */
    bool getBool(PersistenceItem<bool> const& item) final;

    /**
     * @see KeyValueDatabaseIfc::setBool
     */
    void setBool(PersistenceItem<bool> const& item, bool const value) final;

    /**
     * @see KeyValueDatabaseIfc::getInt
     */
    int32_t getInt(PersistenceItem<int32_t> const& item) final;

    /**
     * @see KeyValueDatabaseIfc::setInt
     */
    void setInt(PersistenceItem<int32_t> const& item, int32_t const value) final;

private:

    rocksdb::Status writeString(PersistenceKey const& key, std::string const& value);
    rocksdb::Status readString(PersistenceKey const& key, std::string& value);

    std::string getInternalKey(PersistenceKey const& key);
    bool onError(rocksdb::Status const& status) const;

    std::shared_ptr<rocksdb::DB> m_db;
    std::string const m_ns;
};

#endif