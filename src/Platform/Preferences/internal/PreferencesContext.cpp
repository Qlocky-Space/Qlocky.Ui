#include "PreferencesContext.h"

PreferencesContext::PreferencesContext(std::shared_ptr<rocksdb::DB> db, std::string const& ns) :
    m_db {db},
    m_ns {ns} {
}

std::string PreferencesContext::getString(std::string const& key, std::string const& defaultValue) {
    std::string value {};
    rocksdb::Status const status {m_db->Get(rocksdb::ReadOptions(), getInternalKey(key), &value)};

    if (status.IsNotFound()) {
        return defaultValue;
    }
    else if (!status.ok()) {
        // TODO error handling
        // maybe return a std::result?
        return defaultValue;
    }

    return value;
}

std::string PreferencesContext::getInternalKey(std::string const& key) {
    std::string internalKey {};
    internalKey.append(m_ns);
    internalKey.append(":");
    internalKey.append(key);

    return internalKey;
}
