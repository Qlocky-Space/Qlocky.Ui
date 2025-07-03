#include "PreferencesService.h"

#include <filesystem>
#include <iostream>

#include "PreferencesContext.h"

PreferencesService::PreferencesService() :
    m_mutex {},
    m_contexts {},
    m_db {} {
}

void PreferencesService::initialize() {
    std::string const dbName {"/tmp/qlocky/db.data"};

    // ensure directory exists
    std::error_code ec;
    std::filesystem::create_directories(std::filesystem::path {dbName}.parent_path(), ec);

    rocksdb::DB* pDb {nullptr};
    rocksdb::Options options {};
    options.create_if_missing = true;

    rocksdb::Status const status {rocksdb::DB::Open(options, dbName, &pDb)};
    if (!status.ok()) {
        // TODO Error Handling
        std::cerr << "Error opening DB: " << status.ToString() << std::endl;
        return;
    }

    m_db = std::shared_ptr<rocksdb::DB>(pDb, [&](auto p) {
        delete p;
    });
}

PreferencesContextIfc& PreferencesService::getContext(std::string const& ns) {
    std::lock_guard<std::mutex> lock(m_mutex);

    if (m_contexts.count(ns) != 0) {
        return *m_contexts[ns];
    }

    std::shared_ptr<PreferencesContext> ctx {std::make_shared<PreferencesContext>(m_db, ns)};
    return *m_contexts.emplace(ns, ctx).first->second;
}
