#pragma once

#include <cstdint>

namespace disark
{

/** The type of parameter in an instruction (16 bits number, relative jump value, etc.). */
enum class SourceParameterType : uint8_t
{
    /** There is no parameter. */
    absent,

    /** Such as 0x1234, 0, 0xffff, etc. */
    number16bits,
    /** Such as 0xff, 0, 0x1e, etc. */
    number8bits,
    /** Used by IX/IY (ix + 4, iy - 12 for example). */
    signed8bitsIndex,
    /** Used by relative instruction such as DJNZ, JR, etc.). */
    relativeJump8bits
};

}    // namespace disark
