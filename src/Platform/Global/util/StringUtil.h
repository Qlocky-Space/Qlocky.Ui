#ifndef GLOBAL_STRING_UTIL_H
#define GLOBAL_STRING_UTIL_H

#include <string>
#include <vector>

class StringUtil {
public:

    /**
     * @brief Removes leading and trailing whitespace from the input string.
     * @param str The input string.
     * @return A copy of the trimmed string.
     */
    static void trim(std::string& str);

    /**
     * @brief Splits a string by a single character delimiter.
     * @param str The input string to split.
     * @param delimiter The character to split by.
     * @return A vector of string tokens.
     */
    static std::vector<std::string> split(std::string const& str, std::string const& delimiter);

    StringUtil() = delete;

private:

    static void ltrim(std::string& s);
    static void rtrim(std::string& s);
};

#endif // STRING_UTIL_H
