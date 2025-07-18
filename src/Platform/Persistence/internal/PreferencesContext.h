#ifndef PERSISTENCE_CONTEXT_H
#define PERSISTENCE_CONTEXT_H

#include <memory>
#include <rocksdb/db.h>
#include <string>

#include "PreferencesContextIfc.h"

/**
 * @see PreferencesContextIfc
 *
 * A RocksDb based implementation of the PreferencesContextIfc. This class provides methods to get
 * and set preferences as key/value pairs. Preferences are stored in a namespace, allowing for
 * separation of different preference groups. The keys are prefixed with the namespace to avoid
 * collisions with other preference contexts.
 *
 * @note The values are stored as strings, and conversion to/from other types (like int or bool) is handled internally.
 */
class PreferencesContext : public PreferencesContextIfc {
public:

    PreferencesContext(std::shared_ptr<rocksdb::DB> db, std::string const& ns);

    /**
     * @see PreferencesContextIfc::getString
     */
    std::string getString(PreferencesItem<RawString> const& item) final;

    /**
     * @see PreferencesContextIfc::setString
     */
    void setString(PreferencesItem<RawString> const& item, std::string const& value) final;

    /**
     * @see PreferencesContextIfc::getBool
     */
    bool getBool(PreferencesItem<bool> const& item) final;

    /**
     * @see PreferencesContextIfc::setBool
     */
    void setBool(PreferencesItem<bool> const& item, bool const value) final;

    /**
     * @see PreferencesContextIfc::getInt
     */
    int getInt(PreferencesItem<int32_t> const& item) final;

    /**
     * @see PreferencesContextIfc::setInt
     */
    void setInt(PreferencesItem<int32_t> const& item, int32_t const value) final;

private:

    rocksdb::Status writeString(PreferencesKey const& key, std::string const& value);
    rocksdb::Status readString(PreferencesKey const& key, std::string& value);

    std::string getInternalKey(PreferencesKey const& key);
    bool onError(rocksdb::Status const& status) const;

    std::shared_ptr<rocksdb::DB> m_db;
    std::string const m_ns;
};

#endif