#include "KeyValueDatabase.h"

#include <iostream>

KeyValueDatabase::KeyValueDatabase(std::shared_ptr<rocksdb::DB> db, std::string const& ns) :
    m_db {db},
    m_ns {ns} {
}

Result<std::string> KeyValueDatabase::getString(PersistenceKey const& key) {
    std::string value {};
    rocksdb::Status const status {readString(key, value)};

    return toResult(value, status);
}

ResultVoid KeyValueDatabase::setString(PersistenceKey const& key, std::string const& value) {
    rocksdb::Status const status {writeString(key, value)};

    return toResult(status);
}

Result<bool> KeyValueDatabase::getBool(PersistenceKey const& key) {
    std::string value {};
    rocksdb::Status const status {readString(key, value)};

    return toResult(value == "true", status);
}

ResultVoid KeyValueDatabase::setBool(PersistenceKey const& key, bool const value) {
    rocksdb::Status const status {writeString(key, value ? "true" : "false")};

    return toResult(status);
}

Result<int32_t> KeyValueDatabase::getInt(PersistenceKey const& key) {
    std::string value {};
    rocksdb::Status const status {readString(key, value)};

    try {
        return toResult(std::stoi(value), status);
    }
    catch (std::invalid_argument const&) {
        return toResult(0, rocksdb::Status::Corruption("Invalid integer format"));
    }
}

ResultVoid KeyValueDatabase::setInt(PersistenceKey const& key, int32_t const value) {
    rocksdb::Status const status {writeString(key, std::to_string(value))};

    return toResult(status);
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
    internalKey.append(key);

    return internalKey;
}
