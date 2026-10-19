#include "AreaGenerator.h"

#include "../utils/StringUtil.h"
#include "AreaTag.h"
#include "References.h"
#include "Regions.h"

namespace disark
{

AreaGenerator::AreaGenerator(Regions& pRegions, References& pReferences) noexcept :
    regions(pRegions),
    references(pReferences)
{
}

std::pair<std::vector<Symbol>, std::vector<juce::String>> AreaGenerator::fillFromSymbols(const std::vector<Symbol>& symbols) noexcept
{
    std::vector<juce::String> errorMessages;
    std::vector<Symbol> symbolsToKeep;      // The symbols that are not markers.
    std::map<juce::String, Area> tagToArea;

    // Browses each label, creating regions for each type.
    auto success = true;
    for (const auto& symbol : symbols) {
        // Not a very elegant code... Oh, well.
        auto found = false;
        // Is it a label about code/byte/word/pointer region?
        success = checkAndManageLabelForArea(symbol, AreaTag::tagCodeRegionStart, AreaTag::tagCodeRegion, false, AreaType::code, tagToArea, errorMessages, found);

        if (!found && success) {
            success = checkAndManageLabelForArea(symbol, AreaTag::tagCodeRegionEnd, AreaTag::tagCodeRegion, true, AreaType::code, tagToArea, errorMessages, found);
        }

        if (!found && success) {
            success = checkAndManageLabelForArea(symbol, AreaTag::tagByteRegionStart, AreaTag::tagByteRegion, false, AreaType::byte, tagToArea, errorMessages, found);
        }
        if (!found && success) {
            success = checkAndManageLabelForArea(symbol, AreaTag::tagByteRegionEnd, AreaTag::tagByteRegion, true, AreaType::byte, tagToArea, errorMessages, found);
        }

        if (!found && success) {
            success = checkAndManageLabelForArea(symbol, AreaTag::tagWordRegionStart, AreaTag::tagWordRegion, false, AreaType::word, tagToArea, errorMessages, found);
        }
        if (!found && success) {
            success = checkAndManageLabelForArea(symbol, AreaTag::tagWordRegionEnd, AreaTag::tagWordRegion, true, AreaType::word, tagToArea, errorMessages, found);
        }

        if (!found && success) {
            success = checkAndManageLabelForArea(symbol, AreaTag::tagPointerRegionStart, AreaTag::tagPointerRegion, false, AreaType::pointers, tagToArea, errorMessages, found);
        }
        if (!found && success) {
            success = checkAndManageLabelForArea(symbol, AreaTag::tagPointerRegionEnd, AreaTag::tagPointerRegion, true, AreaType::pointers, tagToArea, errorMessages, found);
        }

        if (!found && success) {
            success = checkAndManageLabelForArea(symbol, AreaTag::tagForceReferenceAreaStart, AreaTag::tagForceReferenceArea, false, AreaType::forceReference, tagToArea, errorMessages, found);
        }
        if (!found && success) {
            success = checkAndManageLabelForArea(symbol, AreaTag::tagForceReferenceAreaEnd, AreaTag::tagForceReferenceArea, true, AreaType::forceReference, tagToArea, errorMessages, found);
        }

        if (!found && success) {
            success = checkAndManageLabelForArea(symbol, AreaTag::tagForceNonReferenceAreaStart, AreaTag::tagForceNonReferenceArea, false, AreaType::forceNonReference, tagToArea, errorMessages, found);
        }
        if (!found && success) {
            success = checkAndManageLabelForArea(symbol, AreaTag::tagForceNonReferenceAreaEnd, AreaTag::tagForceNonReferenceArea, true, AreaType::forceNonReference, tagToArea, errorMessages, found);
        }

        // ---------------
        // Not areas: there is no start/end. The length is inferred from the label.
        if (!found && success) {
            success = checkAndManageLabelForForcedOrNotReference(symbol, AreaTag::baseTagForceNonReferenceDuring, false, 0, // The size is inferred from the label postfix.
                    references, errorMessages, found);
        }
        if (!found && success) {
            success = checkAndManageLabelForForcedOrNotReference(symbol, AreaTag::baseTagForceReferenceDuring, true, 0,
                    references, errorMessages, found);
        }

        // Word.
        if (!found && success) {
            success = checkAndManageLabelForForcedOrNotReference(symbol, AreaTag::tagForceOneWordAreaWithForceReference, true, 2,
                                                                 references, errorMessages, found);
            if (found) {
                // A pointer Region must be created.
                success = createPointerRegion(tagToArea, symbol);
            }
        }
        if (!found && success) {
            success = checkAndManageLabelForForcedOrNotReference(symbol, AreaTag::tagForceOneWordAreaWithForceNonReference, false, 2,
                                                                 references, errorMessages, found);
            if (found) {
                // A pointer Region must be created.
                success = createPointerRegion(tagToArea, symbol);
            }
        }

        if (!success) {
            break;
        }

        if (!found) {
            // This Symbol is not a marker, so it is kept.
            symbolsToKeep.emplace_back(symbol);
        }
    }

    // Makes sure all the regions are finished.
    if (success) {
        for (const auto& iterator : tagToArea) {
            const auto& area = iterator.second;
            if (!area.isValid()) {
                errorMessages.emplace_back(juce::translate("An area is invalid (start or end not defined). Tag = ") + iterator.first);
                const auto start = juce::translate("    Start: ") + (area.isStartAddressPresent() ? juce::String(area.getStartAddress()) : juce::translate("undefined."));
                errorMessages.emplace_back(start);
                const auto end = juce::translate("    End (excluded): ") + (area.isExclusiveEndAddressPresent() ? juce::String(area.getExclusiveEndAddress()) :
                        juce::translate("undefined."));
                errorMessages.emplace_back(end);
                
                success = false;
            } else {
                // Inserts the Regions.
                addArea(area);
            }
        }
    }

    jassert((success && errorMessages.empty()) || (!success && !errorMessages.empty()));

    return { symbolsToKeep, errorMessages };
}

bool AreaGenerator::checkAndManageLabelForArea(const Symbol& symbol, const juce::String& tagToCheck, const juce::String& baseTag, bool isTagEnd, AreaType areaType,
                                               std::map<juce::String, Area>& tagToArea, std::vector<juce::String>& errorMessages, bool& found) noexcept
{
    // Does the label contain the tag? If not, nothing to do.
    const auto& label = symbol.getLabel();
    jassert(label.isNotEmpty());
    const auto tagIndex = label.indexOfIgnoreCase(tagToCheck);             // Important to ignore case! Rasm generates uppercase labels.
    if (tagIndex < 0) {
        found = false;
        return true;
    }
    found = true;

    // Gets the prefix. It might be empty.
    const auto prefix = label.substring(0, tagIndex);

    // What is the postfix? It must be present.
    const auto postfix = label.substring(tagIndex + tagToCheck.length());
    if (postfix.isEmpty()) {
        // Error! No postfix.
        errorMessages.emplace_back(translate("The region label has no postfix: " + label));
        return false;
    }
    // A tag is generated from the prefix, base tag (without start/end) and postfix.
    const auto prefixAndShortTagAndPostFix = prefix + baseTag + postfix;

    const auto address = symbol.getAddress();

    // Does a Region already exist?
    auto iterator = tagToArea.find(prefixAndShortTagAndPostFix);
    if (iterator == tagToArea.cend()) {
        // The Region does not exist. Generates it.
        const auto startAddress = isTagEnd ? -1 : address;
        const auto endAddress = isTagEnd ? address : -1;
        tagToArea.emplace(prefixAndShortTagAndPostFix, Area { startAddress, endAddress, areaType });
    } else {
        // The Region exists. If a value already exist in the start or end where we need to write, an error occurs.
        auto area = iterator->second;
        if (isTagEnd) {
            if (area.isExclusiveEndAddressPresent()) {
                // Error! The end address already set.
                errorMessages.emplace_back(translate("Writing the end in a region, for the second time for label: " + label));
                return false;
            }
            area.setExclusiveEndAddress(address);
        } else {
            if (area.isStartAddressPresent()) {
                // Error! The start address already set.
                errorMessages.emplace_back(translate("Writing the start in a region, for the second time for label: " + label));
                return false;
            }
            area.setStartAddress(address);
        }
        // Writes it back.
        tagToArea[prefixAndShortTagAndPostFix] = area;
    }

    return true;
}

bool AreaGenerator::checkAndManageLabelForForcedOrNotReference(const Symbol& symbol, const juce::String& tagToCheck, bool forcedReference, int sizeOfArea,
        References& references, std::vector<juce::String>& errorMessages, bool& found) noexcept
{
    // Does the label contain the tag? If not, nothing to do.
    const auto& label = symbol.getLabel();
    jassert(label.isNotEmpty());
    const auto tagIndex = label.indexOfIgnoreCase(tagToCheck);             // Important to ignore case! Rasm generates uppercase labels.
    if (tagIndex < 0) {
        found = false;
        return true;
    }
    found = true;

    // Is the size known?
    if (sizeOfArea <= 0) {
        // One digit must be following. Other data may be following, we don't care.
        const auto digitIndex = tagIndex + tagToCheck.length();
        const auto digitString = label.substring(digitIndex, digitIndex + 1);
        auto success = (digitString.length() == 1);
        auto digit = 0;
        if (success) {
            // Is it a digit ?
            digit = StringUtil::stringToInt(digitString, success);
            success = ((digit > 0) && (digit < 10));        // Size 0 is not accepted.
        }
        if (!success) {
            // Error! There is no room for a digit.
            errorMessages.emplace_back(translate("Illegal construction for a forced/forced non-reference. Must be followed by a digit (>0): " + label));
            return false;
        }

        sizeOfArea = digit;
    }

    jassert((sizeOfArea > 0) && (sizeOfArea < 10));

    // Declares the area as forced/forced-non referenced.
    const auto address = symbol.getAddress();
    references.setReferencingType(address, address + sizeOfArea, forcedReference ? ReferencingType::forceReference : ReferencingType::forceNonReference);

    return true;
}

void AreaGenerator::addArea(const Area& area) noexcept
{
    jassert(area.isValid());

    // Is it a Region?
    switch (const auto areaType = area.getAreaType()) {
        case AreaType::code: [[fallthrough]];
        case AreaType::byte: [[fallthrough]];
        case AreaType::word: [[fallthrough]];
        case AreaType::pointers: {
            auto regionType = areaTypeToRegionType(areaType);
            regions.addRegion(Region{area.getStartAddress(), area.getExclusiveEndAddress(), regionType});
            break;
        }
        case AreaType::forceReference:
            references.setReferencingType(area.getStartAddress(), area.getExclusiveEndAddress(), ReferencingType::forceReference);
            break;
        case AreaType::forceNonReference:
            references.setReferencingType(area.getStartAddress(), area.getExclusiveEndAddress(), ReferencingType::forceNonReference);
            break;
    }
}

RegionType AreaGenerator::areaTypeToRegionType(AreaType areaType) noexcept
{
    switch (areaType) {
        case AreaType::code:
            return RegionType::code;
        case AreaType::byte:
            return RegionType::byte;
        case AreaType::word:
            return RegionType::word;
        case AreaType::pointers:
            return RegionType::pointers;
        case AreaType::forceNonReference: [[fallthrough]];
        case AreaType::forceReference: [[fallthrough]];
        default:
            // Shouldn't happen!
            jassertfalse;
            return RegionType::code;
    }
}

bool AreaGenerator::createPointerRegion(std::map<juce::String, Area>& tagToArea, const Symbol& symbol)
{
    const auto& label = symbol.getLabel();

    // The symbol mustn't exist.
    if (tagToArea.find(label) != tagToArea.cend()) {
        jassertfalse;       // Not a normal case.
        return false;
    }

    const auto startAddress = symbol.getAddress();
    const Area area(startAddress, startAddress + 2, AreaType::pointers);
    tagToArea[label] = area;

    return true;
}

}    // namespace disark
