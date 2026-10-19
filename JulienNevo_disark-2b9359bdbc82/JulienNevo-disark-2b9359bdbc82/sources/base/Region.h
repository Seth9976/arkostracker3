#pragma once

#include <cstdint>

namespace disark
{

/** The type of data inside a Region. */
enum class RegionType : uint8_t
{
    code,
    byte,
    word,
    pointers
};

/**
 * A Region is a part of the memory, and is of a certain type (code, byte data, pointers).
 */
class Region
{
public:
    /**
     * Constructor.
     * @param startAddress the start address, or -1 if no present.
     * @param endAddressExclusive the end address, exclusive. or -1 if no present.
     * @param regionType the type of the Region.
     */
    Region(int startAddress, int endAddressExclusive, RegionType regionType) noexcept;

    /** Default constructor, useful for maps. */
    Region() noexcept;

    /** @return the start address. */
    int getStartAddress() const noexcept;
    /** @return the end address, exclusive. */
    int getExclusiveEndAddress() const noexcept;

    /** Sets the start address. */
    void setStartAddress(int startAddress) noexcept;
    /** Sets the end address, exclusive. */
    void setExclusiveEndAddress(int endAddress) noexcept;

    /** @return the type of the Region. */
    RegionType getRegionType() const noexcept;

    /** @return true if both start/end are present, and start < end. */
    bool isValid() const noexcept;
    /** @return true if both start/end are absent. */
    bool isCleared() const noexcept;

    /** @return true if the start address is present. */
    bool isStartAddressPresent() const noexcept;
    /** @return true if the end address is present. */
    bool isExclusiveEndAddressPresent() const noexcept;

private:
    int startAddress;                                                       // The start address, or -1 if no present.
    int exclusiveEndAddress;                                                // The end address, exclusive. or -1 if no present.
    RegionType regionType;                                                  // The type of the Region.
};

}    // namespace disark
