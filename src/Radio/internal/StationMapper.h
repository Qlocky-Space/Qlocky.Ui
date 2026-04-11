#ifndef SRC_RADIO_INTERNAL_STATION_MAPPER_H
#define SRC_RADIO_INTERNAL_STATION_MAPPER_H

#include "StationEntity.h"
#include "StationProfile.h"

/**
 * Converts between StationProfile and StationEntity.
 */
class StationMapper {
public:

    /**
     * Convert a station profile to a station entity.
     * @param profile The profile to convert.
     * @return The corresponding entity.
     */
    static StationEntity toEntity(StationProfile const& profile) {
        return StationEntity {
            profile.StationId,
            profile.Name,
            profile.Url,
            profile.Favicon,
            profile.Tags,
            profile.Language,
            profile.CountryCode,
            profile.Votes,
        };
    }

    /**
     * Convert a station entity to a station profile.
     * @param entity The entity to convert.
     * @return The corresponding profile.
     */
    static StationProfile toProfile(StationEntity const& entity) {
        return StationProfile {
            entity.id,
            entity.name,
            entity.url,
            entity.favicon,
            entity.tags,
            entity.language,
            entity.countryCode,
            entity.votes,
        };
    }
};

#endif // SRC_RADIO_INTERNAL_STATION_MAPPER_H