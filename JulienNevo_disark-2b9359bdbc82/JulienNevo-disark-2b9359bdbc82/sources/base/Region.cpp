#include "Region.h"

namespace disark
{

Region::Region(const int pStartAddress, const int pExclusiveEndAddress, const RegionType pRegionType) noexcept :
    startAddress(pStartAddress),
    exclusiveEndAddress(pExclusiveEndAddress),
    regionType(pRegionType)
{
}

Region::Region() noexcept :
    startAddress(-1),
    exclusiveEndAddress(-1),
    regionType(RegionType::code)
{
}

int Region::getStartAddress() const noexcept
{
    return startAddress;
}

int Region::getExclusiveEndAddress() const noexcept
{
    return exclusiveEndAddress;
}

RegionType Region::getRegionType() const noexcept
{
    return regionType;
}

void Region::setStartAddress(const int address) noexcept
{
    startAddress = address;
}

void Region::setExclusiveEndAddress(const int address) noexcept
{
    exclusiveEndAddress = address;
}

bool Region::isValid() const noexcept
{
    return ((startAddress >= 0) && (startAddress <= 65535) && (exclusiveEndAddress >= 0) && (exclusiveEndAddress <= 65536) && (startAddress <= exclusiveEndAddress));
}

bool Region::isCleared() const noexcept
{
    return ((startAddress <= 0) && (exclusiveEndAddress <= 0));
}

bool Region::isStartAddressPresent() const noexcept
{
    return (startAddress >= 0);
}

bool Region::isExclusiveEndAddressPresent() const noexcept
{
    return (exclusiveEndAddress >= 0);
}

}    // namespace disark
