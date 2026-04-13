#include <gmock/gmock.h>

#include "types/Uuid.h"

using namespace ::testing;

TEST(Uuid, parsesCanonicalUuid) {
    Uuid uuid {std::string {"550e8400-e29b-41d4-a716-446655440000"}};

    ASSERT_TRUE(uuid.isValid());
    ASSERT_FALSE(uuid.isNil());
    ASSERT_EQ(uuid.toString(), std::string("550e8400-e29b-41d4-a716-446655440000"));
    ASSERT_EQ(uuid.version(), QUuid::Random);
    ASSERT_EQ(uuid.variant(), QUuid::DCE);
}

TEST(Uuid, normalizesSupportedStringFormats) {
    Uuid uuid {std::string {"URN:UUID:{550E8400-E29B-41D4-A716-446655440000}"}};

    ASSERT_TRUE(uuid.isValid());
    ASSERT_EQ(uuid.toString(), std::string("550e8400-e29b-41d4-a716-446655440000"));
}

TEST(Uuid, acceptsNilUuid) {
    Uuid uuid {std::string {"00000000-0000-0000-0000-000000000000"}};

    ASSERT_TRUE(uuid.isValid());
    ASSERT_TRUE(uuid.isNil());
    ASSERT_EQ(uuid.version(), QUuid::VerUnknown);
}

TEST(Uuid, rejectsInvalidString) {
    Uuid uuid {std::string {"not-a-uuid"}};

    ASSERT_FALSE(uuid.isValid());
    ASSERT_FALSE(uuid.isNil());
    ASSERT_TRUE(uuid.toString().empty());
    ASSERT_EQ(uuid.version(), QUuid::VerUnknown);
    ASSERT_EQ(uuid.variant(), QUuid::VarUnknown);
}

TEST(Uuid, createRandomReturnsValidUuid) {
    Uuid uuid {Uuid::createRandom()};

    ASSERT_TRUE(uuid.isValid());
    ASSERT_FALSE(uuid.isNil());
    ASSERT_EQ(uuid.version(), QUuid::Random);
    ASSERT_EQ(uuid.variant(), QUuid::DCE);
}