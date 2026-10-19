#include "Area.h"

namespace disark
{

Area::Area(const int pStartAddress, const int pExclusiveEndAddress, const AreaType pAreaType) noexcept :
        startAddress(pStartAddress),
        exclusiveEndAddress(pExclusiveEndAddress),
        areaType(pAreaType)
{
}

Area::Area() noexcept :
        startAddress(-1),
        exclusiveEndAddress(-1),
        areaType(AreaType::code)
{
}

int Area::getStartAddress() const noexcept
{
    return startAddress;
}

int Area::getExclusiveEndAddress() const noexcept
{
    return exclusiveEndAddress;
}

AreaType Area::getAreaType() const noexcept
{
    return areaType;
}

void Area::setStartAddress(const int address) noexcept
{
    startAddress = address;
}

void Area::setExclusiveEndAddress(const int address) noexcept
{
    exclusiveEndAddress = address;
}

bool Area::isValid() const noexcept
{
    return ((startAddress >= 0) && (startAddress <= 65535) && (exclusiveEndAddress >= 0) && (exclusiveEndAddress <= 65536) && (startAddress <= exclusiveEndAddress));
}

bool Area::isStartAddressPresent() const noexcept
{
    return (startAddress >= 0);
}

bool Area::isExclusiveEndAddressPresent() const noexcept
{
    return (exclusiveEndAddress >= 0);
}

}    // namespace disark
