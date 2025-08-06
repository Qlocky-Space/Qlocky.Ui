#include <gmock/gmock.h>

#include "internal/PskEncryption.h"
#include "util/StringUtil.h"

using namespace ::testing;

TEST(TestPskEncryption, encryptPassword) {
    std::string const password = "testPassword";
    std::string const ssid = "testSSID";
    // http://anandam.name/pbkdf2/
    std::string expectedEncryptedPassword = "1f135f00de74e598d5bf7c8cb6bb82d635629d24ed12a1d4ef54208ca56a4e60";

    auto result = StringUtil::bytesToHexDump(PskEncryption::encrypt(password, ssid));

    ASSERT_STREQ(result.c_str(), expectedEncryptedPassword.c_str());
}
