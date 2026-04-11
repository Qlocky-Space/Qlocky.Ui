#ifndef RADIO_INFO_H
#define RADIO_INFO_H

#include <cstdint>
#include <string>
#include <types/Uuid.h>

/**
 * StationProfile holds information about the current radio station.
 * @note https://docs.radio-browser.info/#station
 */
struct StationProfile {
    Uuid StationId; // A globally unique identifier for the station

    std::string Name;        // The name of the station
    std::string Url;         // The URL of the station's stream
    std::string Favicon;     // URL to an icon or picture that represents the stream. (PNG, JPG)
    std::string Tags;        // Tags of the stream with more information about it. Comma separated list of tags.
    std::string Language;    // Languages that are spoken in this stream. Comma separated list of languages.
    std::string CountryCode; // Official countrycodes as in ISO 3166-1 alpha-2
    uint32_t Votes;          // Number of votes for this station. This number is by server and only ever increases. It will never be reset to 0.
};

#endif
