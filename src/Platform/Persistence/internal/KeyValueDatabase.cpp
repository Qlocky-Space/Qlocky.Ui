#include "KeyValueDatabase.h"

#include <iostream>

KeyValueDatabase::KeyValueDatabase(std::shared_ptr<rocksdb::DB> db, std::string const& ns) :
    m_db {db},
    m_ns {ns} {
}

Result<std::string> KeyValueDatabase::getString(PersistenceItem<RawString> const& item) {
    std::string value {};
    rocksdb::Status const status {readString(item.key(), value)};

    return toResult(value, item, status);
}

ResultVoid KeyValueDatabase::setString(PersistenceItem<RawString> const& item, std::string const& value) {
    rocksdb::Status const status {writeString(item.key(), value)};

    return toResult(item, status);
}

Result<bool> KeyValueDatabase::getBool(PersistenceItem<bool> const& item) {
    std::string value {};
    rocksdb::Status const status {readString(item.key(), value)};

    return toResult(value == "true", item, status);
}

ResultVoid KeyValueDatabase::setBool(PersistenceItem<bool> const& item, bool const value) {
    rocksdb::Status const status {writeString(item.key(), value ? "true" : "false")};

    return toResult(item, status);
}

Result<int32_t> KeyValueDatabase::getInt(PersistenceItem<int32_t> const& item) {
    std::string value {};
    rocksdb::Status const status {readString(item.key(), value)};

    try {
        return toResult(std::stoi(value), item, status);
    }
    catch (std::invalid_argument const&) {
        return toResult(item.defaultValue(), item, rocksdb::Status::InvalidArgument("Invalid integer format"));
    }
}

ResultVoid KeyValueDatabase::setInt(PersistenceItem<int32_t> const& item, int32_t const value) {
    rocksdb::Status const status {writeString(item.key(), std::to_string(value))};

    return toResult(item, status);
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
