#pragma once

#include "AreaType.h"

namespace disark
{

/**
 * Area, holds a start/end address, and a type. It is a "super Area", in the sense that is contains more different types.
 */
class Area
{
public:
    /**
     * Constructor.
     * @param startAddress the start address, or -1 if no present.
     * @param endAddressExclusive the end address, exclusive. or -1 if no present.
     * @param areaType the type of the Area.
     */
    Area(int startAddress, int endAddressExclusive, AreaType areaType) noexcept;

    /** Default constructor, useful for maps. */
    Area() noexcept;

    /** @return the start address. */
    int getStartAddress() const noexcept;
    /** @return the end address, exclusive. */
    int getExclusiveEndAddress() const noexcept;

    /** Sets the start address. */
    void setStartAddress(int startAddress) noexcept;
    /** Sets the end address, exclusive. */
    void setExclusiveEndAddress(int endAddress) noexcept;

    /** @return the type of the Area. */
    AreaType getAreaType() const noexcept;

    /** @return true if both start/end are present, and start < end. */
    bool isValid() const noexcept;

    /** @return true if the start address is present. */
    bool isStartAddressPresent() const noexcept;
    /** @return true if the end address is present. */
    bool isExclusiveEndAddressPresent() const noexcept;

private:
    int startAddress;                                                       // The start address, or -1 if no present.
    int exclusiveEndAddress;                                                // The end address, exclusive. or -1 if no present.
    AreaType areaType;                                                      // The type of the Area.
};

}    // namespace disark