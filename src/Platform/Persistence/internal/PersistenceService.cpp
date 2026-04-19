#include "PersistenceService.h"

#include <filesystem>
#include <iostream>
#include <ng-log/logging.h>
#include <vector>

#include "KeyValueDatabase.h"

PersistenceService::PersistenceService() :
    m_mutex {},
    m_contexts {},
    m_db {} {
}

void PersistenceService::initialize() {
    std::string const dbPath {"/opt/data/qlocky_db"};

    rocksdb::Options options {};
    options.create_if_missing = true;

    std::error_code ec;
    std::filesystem::create_directories(std::filesystem::path {dbPath}.parent_path(), ec);

    rocksdb::DB* pDb {nullptr};
    rocksdb::Status const status {rocksdb::DB::Open(options, dbPath, &pDb)};
    if (!status.ok()) {
        LOG(ERROR) << "Failed to open database at " << dbPath << ": " << status.ToString();
        return;
    }

    m_db = std::shared_ptr<rocksdb::DB>(pDb);

    LOG(INFO) << "Persistence database opened at: " << dbPath;
}

KeyValueDatabaseIfc& PersistenceService::getContext(std::string const& ns) {
    std::lock_guard<std::mutex> lock(m_mutex);

    if (m_contexts.count(ns) != 0) {
        return *m_contexts[ns];
    }

    std::shared_ptr<KeyValueDatabase> ctx {std::make_shared<KeyValueDatabase>(m_db, ns)};
    return *m_contexts.emplace(ns, ctx).first->second;
}
