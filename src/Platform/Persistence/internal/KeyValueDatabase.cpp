#include "KeyValueDatabase.h"

#include <iostream>

namespace {

rocksdb::Status dbUnavailableStatus() {
    return rocksdb::Status::IOError("Database is not initialized");
}

} // namespace

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

ResultVoid KeyValueDatabase::remove(PersistenceKey const& key) {
    if (!m_db) {
        return toResult(dbUnavailableStatus());
    }

    rocksdb::Status const status {m_db->Delete(rocksdb::WriteOptions(), getInternalKey(key))};
    return toResult(status);
}

Result<KeyValueList> KeyValueDatabase::getList(PersistenceKey const& item) {
    if (!m_db) {
        return toResult(KeyValueList {}, dbUnavailableStatus());
    }

    std::vector<std::pair<std::string, std::string>> items;

    std::unique_ptr<rocksdb::Iterator> it(m_db->NewIterator(rocksdb::ReadOptions()));
    std::string prefix = getInternalKey(item) + ":";
    for (it->Seek(prefix); it->Valid() && it->key().starts_with(prefix); it->Next()) {
        std::string key = it->key().ToString();
        std::string value = it->value().ToString();
        items.emplace_back(key.substr(prefix.size()), value);
    }

    return toResult(items, it->status());
}

ResultVoid KeyValueDatabase::setListItem(PersistenceKey const& item, uint32_t const id, std::string const& value) {
    rocksdb::Status const status {writeString(item + ":" + std::to_string(id), value)};
    return toResult(status);
}

ResultVoid KeyValueDatabase::removeListItem(PersistenceKey const& item, uint32_t const id) {
    return remove(item + ":" + std::to_string(id));
}

rocksdb::Status KeyValueDatabase::writeString(PersistenceKey const& key, std::string const& value) {
    if (!m_db) {
        return dbUnavailableStatus();
    }

    return m_db->Put(rocksdb::WriteOptions(), getInternalKey(key), value);
}

rocksdb::Status KeyValueDatabase::readString(PersistenceKey const& key, std::string& value) {
    if (!m_db) {
        return dbUnavailableStatus();
    }

    return m_db->Get(rocksdb::ReadOptions(), getInternalKey(key), &value);
}

std::string KeyValueDatabase::getInternalKey(PersistenceKey const& key) {
    std::string internalKey {};
    internalKey.append(m_ns);
    internalKey.append(":");
    internalKey.append(key);

    return internalKey;
}
