#pragma once

#include <cstdint>

namespace disark
{

/**
 * An Area is like a "super Region". It contains all the types of the Regions, but also more.
 */
enum class AreaType : uint8_t
{
    code,
    byte,
    word,
    pointers,

    forceNonReference,
    forceReference,
};

}    // namespace disark
