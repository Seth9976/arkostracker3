#pragma once

#include <map>
#include <vector>

#include "Region.h"

namespace disark
{

class References;

/**
 * Holds the Regions inside the memory.
 */
class Regions
{
public:
    /** Constructor. */
    Regions() noexcept;

    /**
     * Adds a Region. If empty, nothing is done.
     * @param region
     */
    void addRegion(const Region& region) noexcept;

    /**
     * Returns the type of the Region from the given address. This first sorts the Regions, if needed.
     * @param address the address.
     * @return the Region type. By default, it is code.
     */
    RegionType getRegionTypeSortIfNeeded(int address) noexcept;

private:
    /** Sorts the Regions. */
    void sortRegions() noexcept;
    /** Must be called whenever a Region is added: the whole map is rebuilt. */
    void rebuildMaps();

    std::map<int, RegionType> addressToRegionType;              // Links an address to its region type. Only the ones that are not codes are written! More efficient.
    std::vector<Region> regions;                                // Holds all the Regions.
    bool dirty;                                                 // True when Regions have been added. They must be sorted before getting is possible.
};

}    // namespace disark
