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
    Result<std::string> getString(PersistenceItem<RawString> const& item) final;

    /**
     * @see KeyValueDatabaseIfc::setString
     */
    ResultVoid setString(PersistenceItem<RawString> const& item, std::string const& value) final;

    /**
     * @see KeyValueDatabaseIfc::getBool
     */
    Result<bool> getBool(PersistenceItem<bool> const& item) final;

    /**
     * @see KeyValueDatabaseIfc::setBool
     */
    ResultVoid setBool(PersistenceItem<bool> const& item, bool const value) final;

    /**
     * @see KeyValueDatabaseIfc::getInt
     */
    Result<int32_t> getInt(PersistenceItem<int32_t> const& item) final;

    /**
     * @see KeyValueDatabaseIfc::setInt
     */
    ResultVoid setInt(PersistenceItem<int32_t> const& item, int32_t const value) final;

private:

    rocksdb::Status writeString(PersistenceKey const& key, std::string const& value);
    rocksdb::Status readString(PersistenceKey const& key, std::string& value);

    std::string getInternalKey(PersistenceKey const& key);

    template<typename T, typename E>
    Result<T> toResult(T const& value, PersistenceItem<E> const& item, rocksdb::Status const& status) const {
        if (status.IsNotFound()) {
            if constexpr (std::is_same_v<E, RawString>) {
                return std::string {item.defaultValue()};
            }
            else {
                return item.defaultValue();
            }
        }
        else if (!status.ok()) {
            return Result<T>::error(status.ToString());
        }

        return value;
    }

    template<typename T>
    ResultVoid toResult(PersistenceItem<T> const& item, rocksdb::Status const& status) const {
        if (status.ok()) {
            return ResultVoid::success(true);
        }
        else {
            return ResultVoid::error(status.ToString());
        }
    }

    std::shared_ptr<rocksdb::DB> m_db;
    std::string const m_ns;
};

#endif