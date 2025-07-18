#include "PreferencesContext.h"

#include <iostream>

PreferencesContext::PreferencesContext(std::shared_ptr<rocksdb::DB> db, std::string const& ns) :
    m_db {db},
    m_ns {ns} {
}

std::string PreferencesContext::getString(PreferencesItem<RawString> const& item) {
    std::string value {};
    rocksdb::Status const status {readString(item.key(), value)};

    if (onError(status)) {
        // TODO error handling
        return item.defaultValue();
    }

    return value;
}

void PreferencesContext::setString(PreferencesItem<RawString> const& item, std::string const& value) {
    rocksdb::Status const status {writeString(item.key(), value)};

    if (onError(status)) {
        std::cerr << "Error setting string for key '" << item.key().name() << "': " << status.ToString() << std::endl;
    }
}

bool PreferencesContext::getBool(PreferencesItem<bool> const& item) {
    std::string value {};
    rocksdb::Status const status {writeString(item.key(), value)};

    if (onError(status)) {
        return item.defaultValue();
    }

    return value == "true";
}

void PreferencesContext::setBool(PreferencesItem<bool> const& item, bool const value) {
    rocksdb::Status const status {writeString(item.key(), value ? "true" : "false")};

    if (onError(status)) {
        std::cerr << "Error setting bool for key '" << item.key().name() << "': " << status.ToString() << std::endl;
    }
}

int PreferencesContext::getInt(PreferencesItem<int32_t> const& item) {
    std::string value {};
    rocksdb::Status const status {readString(item.key(), value)};

    if (onError(status)) {
        return item.defaultValue();
    }

    try {
        return std::stoi(value);
    }
    catch (std::invalid_argument const&) {
        std::cerr << "Error setting int for key '" << item.key().name() << "': invalid value (" << value << ")" << std::endl;
        return item.defaultValue();
    }
}

void PreferencesContext::setInt(PreferencesItem<int32_t> const& item, int32_t const value) {
    rocksdb::Status const status {writeString(item.key(), std::to_string(value))};

    if (onError(status)) {
        std::cerr << "Error setting int for key '" << item.key().name() << "': " << status.ToString() << std::endl;
    }
}

rocksdb::Status PreferencesContext::writeString(PreferencesKey const& key, std::string const& value) {
    return m_db->Put(rocksdb::WriteOptions(), getInternalKey(key), value);
}

rocksdb::Status PreferencesContext::readString(PreferencesKey const& key, std::string& value) {
    return m_db->Get(rocksdb::ReadOptions(), getInternalKey(key), &value);
}

std::string PreferencesContext::getInternalKey(PreferencesKey const& key) {
    std::string internalKey {};
    internalKey.append(m_ns);
    internalKey.append(":");
    internalKey.append(key.name());

    return internalKey;
}

bool PreferencesContext::onError(rocksdb::Status const& status) const {
    if (status.IsNotFound()) {
        return true;
    }
    else if (!status.ok()) {
        return true;
    }

    return false;
}
