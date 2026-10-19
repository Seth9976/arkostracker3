#include "References.h"

#include "../utils/MapUtil.h"
#include "AreaTag.h"
#include "Symbol.h"

namespace disark
{

Reference::Reference(juce::String pLabel, const int pOffset) noexcept :
    label(std::move(pLabel)),
    offset(pOffset)
{
}

bool Reference::isReferencePresent() const noexcept
{
    return label.isNotEmpty();
}


// References::Label.
// ============================================================

References::Label::Label(juce::String pLabel, const bool pGenerated, const bool pExternal) noexcept :
    name(std::move(pLabel)),
    generated(pGenerated),
    external(pExternal)
{
}

const juce::String& References::Label::getName() const noexcept
{
    return name;
}

bool References::Label::isGenerated() const noexcept
{
    return generated;
}

bool References::Label::isExternal() const noexcept
{
    return external;
}


// References.
// ============================================================

References::References() noexcept :
    addressToLabels(),
    labelToAddress(),
    referencedLabels(),
    declaredLabels(),
    addressToReferencingType()
{
}

void References::storeSymbol(const Symbol& symbol) noexcept
{
    const auto address = symbol.getAddress();
    const auto& label = symbol.getLabel();

    jassert((address >= 0) && (address <= 65535));
    jassert(label.isNotEmpty());

    // Labels can be external! In which case they are renamed.
    bool isExternal;      // NOLINT(*-init-variables)
    const auto& labelToWrite = checkIfExternalAndRename(label, isExternal);

    // Adds the label in both maps, for easy retrieval.
    MapUtil::addValueToMapOfListOfValues(addressToLabels, address, { labelToWrite, symbol.isGenerated(), isExternal });
    labelToAddress.emplace(labelToWrite, address);
}

Reference References::getReference(const int address, const bool forceReferencing) const noexcept
{
    // First, try "around" (normal behavior).
    auto reference = getReferenceAround(address);
    if (reference.isReferencePresent()) {
        // Found it! We can exit.
        return reference;
    }

    // If a "force reference", searches beyond, else stops here.
    if (!forceReferencing) {
        return reference;
    }

    auto offset = 1;
    while (offset <= 0xffff) {
        auto targetAddress = address + offset;
        // Still within bound?
        if ((targetAddress >= 0) && (targetAddress <= 65535)) {
            // Any label?
            auto references = getExactReferences(targetAddress);
            if (!references.empty()) {
                // Chooses the first one (we don't know which one to choose from anyway!).
                return {references.front().getName(), offset};
            }
        }

        // Sweeps from one "side" to another before increasing.
        if (offset > 0) {
            offset = -offset;
        } else {
            offset = -offset;
            ++offset;
        }
    }

    // Nothing found! This is rather unexpected, and happens only if there is no label at all!
    jassertfalse;
    return reference;
}

Reference References::getReferenceAround(const int address) const noexcept
{
    // Browses all the references which address is within a +/- window.
    // These are the preferred offsets. -1/-2 are preferred to allow:
    // label1 ld hl,0
    // label2 ld hl,0
    //        ld hl,label1 + 1
    //        ld hl,label1 + 2    instead of label2 - 1 for example.
    // These are offsets, so they are inverted.
    std::vector<int> offsets = { 0,   -1, -2,   1, 2,   3, -3,  4, -4,  5, -5,  6, -6,  7, -7,  8, -8,  9, -9 };

    for (auto offset : offsets) {
        auto targetAddress = address + offset;

        auto iterator = addressToLabels.find(targetAddress);
        if (iterator != addressToLabels.cend()) {
            // Retrieves the first label, it is not possible to decide which one to choose from!
            jassert(!iterator->second.empty());
            const auto& label = iterator->second.front();

            return { label.getName(), offset };
        }
    }

    // Not found.
    return { "", 0 };
}

std::vector<References::Label> References::getExactReferences(const int address) const noexcept
{
    auto iterator = addressToLabels.find(address);
    return (iterator != addressToLabels.cend()) ? iterator->second : std::vector<References::Label>{};
}

void References::markLabelAsReferredTo(const juce::String& label) noexcept
{
    // May already exist. Not a problem.
    referencedLabels.insert(label);
}

void References::markLabelAsDeclared(const juce::String& label) noexcept
{
    // It should not be declared before, but as we have several passes, the labels are actually parsed several times... Should be clear them?
    //jassert(declaredLabels.find(label) == declaredLabels.cend());
    declaredLabels.insert(label);
}

void References::deleteUnusedReferences(const bool deletedOnlyGeneratedLabel) noexcept
{
    for (auto& addressToLabel : addressToLabels) {
        // For this address, there are multiple labels. Browses them.
        auto& labels = addressToLabel.second;
        for (auto labelIterator = labels.begin(); labelIterator != labels.end();) {
            // If only delete generated label, skips this if the label is not generated.
            if (deletedOnlyGeneratedLabel && !labelIterator->isGenerated()) {
                ++labelIterator;
                continue;
            }

            // Is it referenced?
            const auto& labelName = labelIterator->getName();
            if (referencedLabels.find(labelName) == referencedLabels.cend()) {
                // The generated label is not referenced.
                labelIterator = labels.erase(labelIterator);
            } else {
                ++labelIterator;
            }
        }
    }
}

std::vector<LabelAndAddress> References::getSortedLabelsAndAddresses() const noexcept
{
    std::vector<LabelAndAddress> labelsAndAddresses;

    // Since a map is used, the sorting is done automatically.
    for (const auto& iterator : addressToLabels) {
        const auto address = iterator.first;
        const auto& labels = iterator.second;

        for (const auto& label : labels) {
            labelsAndAddresses.emplace_back(label.getName(), address);
        }
    }

    return labelsAndAddresses;
}

void References::setReferencingType(const int startAddress, const int endExclusiveAddress, const ReferencingType referencingType) noexcept
{
    jassert(startAddress <= endExclusiveAddress);

    for (auto address = startAddress; address < endExclusiveAddress; ++address) {
        addressToReferencingType[address] = referencingType;
    }
}

ReferencingType References::getReferencingType(const int address) const noexcept
{
    jassert((address >= 0) && (address <= 65535));
    auto iterator = addressToReferencingType.find(address);
    return (iterator == addressToReferencingType.cend()) ? ReferencingType::defaultReferencing : iterator->second;
}

juce::String References::checkIfExternalAndRename(const juce::String& label, bool& externalOut) noexcept
{
    // Is there an "External" tag at the end? Also, if it is ONLY the tag, consider it a normal label.
    const auto tag = AreaTag::tagGenerateExternalLabel;
    if ((!label.endsWithIgnoreCase(tag)) || (label.equalsIgnoreCase(tag))) {        // No tag. Normal label.
        externalOut = false;
        return label;
    }

    // External tag.
    externalOut = true;
    auto tagIndex = label.indexOfIgnoreCase(AreaTag::tagGenerateExternalLabel);
    jassert(tagIndex > 0);      // Already checked before.

    return label.substring(0, tagIndex);
}

std::vector<LabelAndAddress> References::getUndeclaredReferencedLabels() const noexcept
{
    std::vector<LabelAndAddress> result;

    // Finds all the referenced labels. If not declared, adds them to the list.
    // However, their address is also returned, as a convenience.
    for (const auto& referencedLabel : referencedLabels) {
        // Is it declared?
        if (declaredLabels.find(referencedLabel) == declaredLabels.cend()) {
            // Not declared! Finds its address, and stores it.
            jassert(labelToAddress.find(referencedLabel) != labelToAddress.cend());     // The address must exist!
            auto address = labelToAddress.find(referencedLabel)->second;
            result.emplace_back(referencedLabel, address);
        }
    }

    return result;
}

}    // namespace disark
