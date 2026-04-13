#ifndef SRC_RADIO_INTERNAL_RADIO_BROWSER_API_V1_H
#define SRC_RADIO_INTERNAL_RADIO_BROWSER_API_V1_H

#include <cstdint>
#include <ng-log/logging.h>
#include <nlohmann/json.hpp>
#include <optional>
#include <string>
#include <vector>

struct RadioBrowserApiStationRecord {
    std::string stationuuid;
    std::string name;
    std::string url;
    std::string url_resolved;
    std::string favicon;
    std::string tags;
    std::string language;
    std::string countrycode;
    uint32_t votes {0};
};

struct RadioBrowserAPIv1 {
    std::vector<RadioBrowserApiStationRecord> stations {};
};

namespace radio_browser_api_v1 {

inline std::string readString(nlohmann::json const& json, char const* key) {
    auto const it = json.find(key);
    if (it == json.end() || it->is_null()) {
        return {};
    }

    if (it->is_string()) {
        return it->get<std::string>();
    }

    if (it->is_number_integer()) {
        return std::to_string(it->get<std::int64_t>());
    }

    if (it->is_number_unsigned()) {
        return std::to_string(it->get<std::uint64_t>());
    }

    if (it->is_number_float()) {
        return std::to_string(it->get<double>());
    }

    if (it->is_boolean()) {
        return it->get<bool>() ? "true" : "false";
    }

    return {};
}

inline uint32_t readUInt32(nlohmann::json const& json, char const* key) {
    auto const it = json.find(key);
    if (it == json.end() || it->is_null()) {
        return 0;
    }

    if (it->is_number_unsigned()) {
        return it->get<uint32_t>();
    }

    if (it->is_number_integer()) {
        auto const value = it->get<std::int64_t>();
        return value > 0 ? static_cast<uint32_t>(value) : 0;
    }

    if (it->is_string()) {
        try {
            return static_cast<uint32_t>(std::stoul(it->get<std::string>()));
        }
        catch (...) {
            return 0;
        }
    }

    return 0;
}

inline std::optional<RadioBrowserApiStationRecord> parseRecord(nlohmann::json const& json) {
    if (!json.is_object()) {
        return std::nullopt;
    }

    RadioBrowserApiStationRecord record {};
    record.stationuuid = readString(json, "stationuuid");
    record.name = readString(json, "name");
    record.url = readString(json, "url");
    record.url_resolved = readString(json, "url_resolved");
    record.favicon = readString(json, "favicon");
    record.tags = readString(json, "tags");
    record.language = readString(json, "language");
    record.countrycode = readString(json, "countrycode");
    record.votes = readUInt32(json, "votes");

    if (record.stationuuid.empty()) {
        return std::nullopt;
    }

    return record;
}

inline void collectStationsFromJson(
    nlohmann::json const& value,
    std::vector<RadioBrowserApiStationRecord>& stations,
    std::size_t& malformedRecords,
    std::size_t& acceptedRecords,
    std::size_t& visitedRecords) {
    if (value.is_array()) {
        for (nlohmann::json const& item : value) {
            collectStationsFromJson(item, stations, malformedRecords, acceptedRecords, visitedRecords);
        }
        return;
    }

    ++visitedRecords;

    try {
        std::optional<RadioBrowserApiStationRecord> const record {parseRecord(value)};
        if (!record.has_value()) {
            ++malformedRecords;
            return;
        }

        stations.push_back(record.value());
        ++acceptedRecords;
    }
    catch (std::exception const& ex) {
        LOG(WARNING) << "Failed to parse radio-browser station record at index " << (visitedRecords - 1) << ": " << ex.what();
        ++malformedRecords;
    }
}

inline void populateResponse(nlohmann::json const& json, RadioBrowserAPIv1& response) {
    std::size_t skippedRecords {0};
    std::size_t acceptedRecords {0};
    std::size_t visitedRecords {0};

    response.stations.clear();
    collectStationsFromJson(json, response.stations, skippedRecords, acceptedRecords, visitedRecords);

    LOG(INFO) << "Parsed " << acceptedRecords << " radio-browser API records from " << visitedRecords << " records.";

    if (skippedRecords > 0) {
        LOG(WARNING) << "Skipped " << skippedRecords << " malformed station records from radio-browser.info.";
    }
}

} // namespace radio_browser_api_v1

inline void from_json(nlohmann::json const& json, RadioBrowserAPIv1& response) {
    radio_browser_api_v1::populateResponse(json, response);
}

#endif // SRC_RADIO_INTERNAL_RADIO_BROWSER_API_V1_H