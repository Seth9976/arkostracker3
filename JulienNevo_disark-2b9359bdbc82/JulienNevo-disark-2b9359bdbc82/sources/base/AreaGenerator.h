#pragma once

#include <map>
#include <utility>
#include <vector>

#include <juce_core/juce_core.h>

#include "Area.h"
#include "AreaType.h"
#include "Region.h"
#include "Symbol.h"

namespace disark
{

class References;
class Regions;

/**
 * Reads the given symbols and generates the Areas (composed of Regions and referencing types).
 */
class AreaGenerator
{
public:
    /**
     * Constructor.
     * @param regions the Regions object, to populate it if needed.
     * @param references the References object, to populate it if needed.
     */
    AreaGenerator(Regions& regions, References& references) noexcept;


    /**
     * Infers regions from the given labels. The start/end and their nature depends on the label. Example *DisarkCodeRegionStart*.
     * If the label/tag has no postfix, it is considered an error.
     * @param symbols the Symbols. The order is not important, the regions are sorted. Technically, ends can be declared before the start.
     * @return the symbols that are not markers (and should be visible). The other item is empty if success, else human-readable messages indicating what went wrong.
     */
    std::pair<std::vector<Symbol>, std::vector<juce::String>> fillFromSymbols(const std::vector<Symbol>& symbols) noexcept;

private:
    /**
     * Checks whether the given label is considered a Region label, and builds the Region map accordingly.
     * @param symbol contains the label with its address.
     * @param tagToCheck the tag to check (DisarkCodeRegionStart for example).
     * @param baseTag the base tag to check (DisarkCodeRegion for example).
     * @param isTagEnd true if the tag to check is about the end region, false if start.
     * @param areaType the type of the Area to generate.
     * @param tagToArea map linking a tag to a possible Area. It will be generated as "prefix + base tag (without start/end) + postfix".
     * @param errorMessages the error messages to fill, in case or error.
     * @param found set to true by the method if the label was interesting, false if nothing has been done.
     * @return false in case of error, else true.
     */
    static bool checkAndManageLabelForArea(const Symbol& symbol, const juce::String& tagToCheck, const juce::String& baseTag, bool isTagEnd,
                                           AreaType areaType,
                                           std::map<juce::String, Area>& tagToArea, std::vector<juce::String>& errorMessages, bool& found) noexcept;

    /**
     * Stores the given Area. It may be a Region or a Referencing type area.
     * @param area the area. It must be valid.
     */
    void addArea(const Area& area) noexcept;

    /**
     * Checks whether the label is a "forced" or "non-forced" reference, with a possible built in size, and builds the region accordingly.
     * @param symbol contains the label with its address.
     * @param tagToCheck the tag to check.
     * @param forcedReference true to search for forced reference tag, false for forced-non references.
     * @param sizeOfAreaIfKnown the size of the area if known, else 0. If not known, it will be searched in the possible digit after.
     * @param references the object to which to indicate the possible new forced/forced-non reference found.
     * @param errorMessages the error messages to fill, in case or error.
     * @param found set to true by the method if the label was interesting, false if nothing has been done.
     * @return false in case of error, else true.
     */
    static bool checkAndManageLabelForForcedOrNotReference(const Symbol& symbol, const juce::String& tagToCheck, bool forcedReference, int sizeOfAreaIfKnown,
            References& references, std::vector<juce::String>& errorMessages, bool& found) noexcept;

    static bool createPointerRegion(std::map<juce::String, Area>& tagToArea, const Symbol& symbol);

    /**
     * Converts an Area type to a Region type. It MUST be a type that can be converted!
     * @param areaType the type of the Area.
     * @return the Region type.
     */
    static RegionType areaTypeToRegionType(AreaType areaType) noexcept;
    Regions& regions;                                           // The Regions object, to populate it if needed.
    References& references;                                     // The References object, to populate in needed.
};

}    // namespace disark
