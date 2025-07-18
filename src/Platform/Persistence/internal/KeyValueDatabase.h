#ifndef PERSISTENCE_CONTEXT_H
#define PERSISTENCE_CONTEXT_H

#include <memory>
#include <rocksdb/db.h>
#include <string>

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
    Result<std::string> getString(PersistenceKey const& item) final;

    /**
     * @see KeyValueDatabaseIfc::setString
     */
    ResultVoid setString(PersistenceKey const& item, std::string const& value) final;

    /**
     * @see KeyValueDatabaseIfc::getBool
     */
    Result<bool> getBool(PersistenceKey const& item) final;

    /**
     * @see KeyValueDatabaseIfc::setBool
     */
    ResultVoid setBool(PersistenceKey const& item, bool const value) final;

    /**
     * @see KeyValueDatabaseIfc::getInt
     */
    Result<int32_t> getInt(PersistenceKey const& item) final;

    /**
     * @see KeyValueDatabaseIfc::setInt
     */
    ResultVoid setInt(PersistenceKey const& item, int32_t const value) final;

    /**
     * @see KeyValueDatabaseIfc::remove
     */
    ResultVoid remove(PersistenceKey const& item) final;

    /**
     * @see KeyValueDatabaseIfc::getList
     */
    Result<KeyValueList> getList(PersistenceKey const& item) final;

    /**
     * @see KeyValueDatabaseIfc::setListItem
     */
    ResultVoid setListItem(PersistenceKey const& item, uint32_t const id, std::string const& value) final;

    /**
     * @see KeyValueDatabaseIfc::removeListItem
     */
    ResultVoid removeListItem(PersistenceKey const& item, uint32_t const id) final;

private:

    rocksdb::Status writeString(PersistenceKey const& key, std::string const& value);
    rocksdb::Status readString(PersistenceKey const& key, std::string& value);

    std::string getInternalKey(PersistenceKey const& key);

    template<typename T>
    Result<T> toResult(T const& value, rocksdb::Status const& status) const {
        if (!status.ok()) {
            return Result<T>::error(status.ToString());
        }

        return Result<T>::success(value);
    }

    ResultVoid toResult(rocksdb::Status const& status) const {
        if (!status.ok()) {
            return ResultVoid::error(status.ToString());
        }

        return ResultVoid::success(true);
    }

    std::shared_ptr<rocksdb::DB> m_db;
    std::string const m_ns;
};

#endif