#ifndef GLOBAL_RAW_STRING_H
#define GLOBAL_RAW_STRING_H

/**
 * Represents a raw string type.
 * This is used because cpp17 does not support constexpr strings.
 */
using RawString = char const*;

#endif