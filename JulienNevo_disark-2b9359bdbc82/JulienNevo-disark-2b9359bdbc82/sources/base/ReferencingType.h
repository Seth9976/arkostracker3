#pragma once

#include <cstdint>

namespace disark
{

/** A referencing type, linked to an address. */
enum class ReferencingType : uint8_t
{
    /** Nothing special here. May try to encode a reference if relevant. */
    defaultReferencing,
    /** No reference must be encoded in this area. */
    forceNonReference,
    /** References must be encoded in this area, no matter what. */
    forceReference
};

}    // namespace disark
