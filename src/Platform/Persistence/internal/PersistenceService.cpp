#include "PersistenceService.h"

#include <filesystem>
#include <iostream>
#include <ng-log/logging.h>

#include "KeyValueDatabase.h"

PersistenceService::PersistenceService() :
    m_mutex {},
    m_contexts {},
    m_db {} {
}

void PersistenceService::initialize() {
    std::string const dbName {"/tmp/qlocky/db"};

    // ensure directory exists
    std::error_code ec;
    std::filesystem::create_directories(std::filesystem::path {dbName}.parent_path(), ec);

    rocksdb::DB* pDb {nullptr};
    rocksdb::Options options {};
    options.create_if_missing = true;

    rocksdb::Status const status {rocksdb::DB::Open(options, dbName, &pDb)};
    if (!status.ok()) {
        LOG(ERROR) << "Failed to open database: " << status.ToString();
        return;
    }

    m_db = std::shared_ptr<rocksdb::DB>(pDb, [&](auto p) {
        delete p;
    });
}

KeyValueDatabaseIfc& PersistenceService::getContext(std::string const& ns) {
    std::lock_guard<std::mutex> lock(m_mutex);

    if (m_contexts.count(ns) != 0) {
        return *m_contexts[ns];
    }

    std::shared_ptr<KeyValueDatabase> ctx {std::make_shared<KeyValueDatabase>(m_db, ns)};
    return *m_contexts.emplace(ns, ctx).first->second;
}
