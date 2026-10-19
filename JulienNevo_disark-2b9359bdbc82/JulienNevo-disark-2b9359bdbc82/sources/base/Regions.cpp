#include "Regions.h"

#include <juce_core/juce_core.h>

namespace disark
{

Regions::Regions() noexcept :
    addressToRegionType(),
    regions(),
    dirty(false)
{
}

void Regions::addRegion(const Region& region) noexcept
{
    jassert(region.isValid());
    // Nothing to do if the start is the same as the end.
    if (region.getStartAddress() == region.getExclusiveEndAddress()) {
        return;
    }

    regions.emplace_back(region);

    dirty = true;
}

RegionType Regions::getRegionTypeSortIfNeeded(int address) noexcept
{
    // Have new Regions be added? If yes, they must be sorted, all the data must be rebuilt.
    if (dirty) {
        sortRegions();
        rebuildMaps();

        dirty = false;
    }

    auto iterator = addressToRegionType.find(address);
    // If nothing is the entry, this means "code".
    return (iterator == addressToRegionType.cend()) ? RegionType::code : iterator->second;
}

void Regions::sortRegions() noexcept
{
    std::sort(regions.begin(), regions.end(), [](const auto& left, const auto& right) -> bool {
        // Sorts by start address first.
        const int leftStartAddress = left.getStartAddress();
        const int rightStartAddress = right.getStartAddress();
        if (leftStartAddress != rightStartAddress) {
            return (leftStartAddress < rightStartAddress);
        }

        // Then sorts by end address.
        // Inner ones are put AFTER, because they will be added in this order. So the smaller internal one will be encoded after the outer
        // one, and thus will gain priority.
        return (right.getExclusiveEndAddress() < left.getExclusiveEndAddress());
    });
}

void Regions::rebuildMaps()
{
    addressToRegionType.clear();

    for (const auto& region : regions) {
        // Not efficient... Who cares.
        const auto regionType = region.getRegionType();
        if (regionType == RegionType::code) {
            // Code: removes all the entries in the range, in the map.
            for (auto address = region.getStartAddress(), exclusiveEndAddress = region.getExclusiveEndAddress(); address < exclusiveEndAddress; ++address) {
                auto iterator = addressToRegionType.find(address);
                if (iterator != addressToRegionType.cend()) {
                    addressToRegionType.erase(iterator);
                }
            }
        } else {
            // The region is not a code, so is added to the map.
            for (auto address = region.getStartAddress(), exclusiveEndAddress = region.getExclusiveEndAddress(); address < exclusiveEndAddress; ++address) {
                addressToRegionType[address] = regionType;
            }
        }
    }
}

}    // namespace disark
