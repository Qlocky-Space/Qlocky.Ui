#include "KeyValueDatabase.h"

#include <iostream>

KeyValueDatabase::KeyValueDatabase(std::shared_ptr<rocksdb::DB> db, std::string const& ns) :
    m_db {db},
    m_ns {ns} {
}

std::string KeyValueDatabase::getString(PersistenceItem<RawString> const& item) {
    std::string value {};
    rocksdb::Status const status {readString(item.key(), value)};

    if (onError(status)) {
        // TODO error handling
        return item.defaultValue();
    }

    return value;
}

void KeyValueDatabase::setString(PersistenceItem<RawString> const& item, std::string const& value) {
    rocksdb::Status const status {writeString(item.key(), value)};

    if (onError(status)) {
        std::cerr << "Error setting string for key '" << item.key().name() << "': " << status.ToString() << std::endl;
    }
}

bool KeyValueDatabase::getBool(PersistenceItem<bool> const& item) {
    std::string value {};
    rocksdb::Status const status {writeString(item.key(), value)};

    if (onError(status)) {
        return item.defaultValue();
    }

    return value == "true";
}

void KeyValueDatabase::setBool(PersistenceItem<bool> const& item, bool const value) {
    rocksdb::Status const status {writeString(item.key(), value ? "true" : "false")};

    if (onError(status)) {
        std::cerr << "Error setting bool for key '" << item.key().name() << "': " << status.ToString() << std::endl;
    }
}

int KeyValueDatabase::getInt(PersistenceItem<int32_t> const& item) {
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

void KeyValueDatabase::setInt(PersistenceItem<int32_t> const& item, int32_t const value) {
    rocksdb::Status const status {writeString(item.key(), std::to_string(value))};

    if (onError(status)) {
        std::cerr << "Error setting int for key '" << item.key().name() << "': " << status.ToString() << std::endl;
    }
}

rocksdb::Status KeyValueDatabase::writeString(PersistenceKey const& key, std::string const& value) {
    return m_db->Put(rocksdb::WriteOptions(), getInternalKey(key), value);
}

rocksdb::Status KeyValueDatabase::readString(PersistenceKey const& key, std::string& value) {
    return m_db->Get(rocksdb::ReadOptions(), getInternalKey(key), &value);
}

std::string KeyValueDatabase::getInternalKey(PersistenceKey const& key) {
    std::string internalKey {};
    internalKey.append(m_ns);
    internalKey.append(":");
    internalKey.append(key.name());

    return internalKey;
}

bool KeyValueDatabase::onError(rocksdb::Status const& status) const {
    if (status.IsNotFound()) {
        return true;
    }
    else if (!status.ok()) {
        return true;
    }

    return false;
}
