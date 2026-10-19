#pragma once

#include <map>
#include <set>

#include <juce_core/juce_core.h>

#include "LabelAndAddress.h"
#include "ReferencingType.h"

namespace disark
{

class Symbol;

/** Holds a label name and an offset. */
class Reference
{
public:
    /**
     * Constructor.
     * @param label the label, or empty if no reference was found.
     * @param offset an offset (0, +1, -2, etc.).
     */
    Reference(juce::String label, int offset) noexcept;

    /** @return true if a label is present. */
    bool isReferencePresent() const noexcept;

    const juce::String label;       // The label.
    const int offset;               // An offset (0, +1, -2, etc.).
};

/**
 * Holds the possible references label that the user has injected. It takes care of giving the best reference, with offset if needed, to the caller.
 * NOTE: since external labels can be generated, two Labels can have the same name, but one can be external and not the other.
 */
class References
{
public:

    /** Holds a label and a flag indicating whether it is generated or not. */
    class Label
    {
    public:
        /**
         * Constructor.
         * @param label the label.
         * @param isGenerated true if the label is generated (by Disark).
         * @param external true if the label is external (for assemblers such as SDCC to reach them from C). They may have a special syntax.
         */
        Label(juce::String label, bool isGenerated, bool external = false) noexcept;

        /** @return the name of the label. */
        const juce::String& getName() const noexcept;
        /** True if the label is generated. */
        bool isGenerated() const noexcept;
        /** True if the label is external (for assemblers such as SDCC to reach them from C). They may have a special syntax. */
        bool isExternal() const noexcept;

    private:
        juce::String name;    // The label name.
        bool generated;       // True if generated.
        bool external;        // True if the label is external (for assemblers such as SDCC to reach them from C). They may have a special syntax.
    };

    References() noexcept;

    /**
     * Returns the best reference to the given address, and from a limited selection window by default.
     * If the address belongs a "force reference", a label will be found, even if very far away.
     * @param address the address.
     * @param forceReferencing true to force a reference. The closest label will be chosen, even if far away.
     * @return the reference, maybe with an offset, or empty label if none could be found.
     */
    Reference getReference(int address, bool forceReferencing = false) const noexcept;

    /**
     * Returns labels for this address, without trying to find "around".
     * @param address the address.
     * @return the labels and a flag indicating whether the label is generated.
     */
    std::vector<Label> getExactReferences(int address) const noexcept;

    /**
     * Stores the given Label.
     * @param symbol the symbol.
     */
    void storeSymbol(const Symbol& symbol) noexcept;

    /**
     * Marks a label as "referred to" (jp label, or ld hl,label, for example).
     * @param label the label. It should exist!
     */
    void markLabelAsReferredTo(const juce::String& label) noexcept;

    /**
     * Marks a label as declared. That is, it has a value (via EQU or <label><instruction>).
     * @param label the label. It must exist!
     */
    void markLabelAsDeclared(const juce::String& label) noexcept;

    /**
     * Deletes all the unused labels.
     * @param deletedOnlyGeneratedLabel true to deleted only the generated labels, false to deleted all (generated and not).
     */
    void deleteUnusedReferences(bool deletedOnlyGeneratedLabel) noexcept;

    /** @return all the labels with their addresses, sorted by address. */
    std::vector<LabelAndAddress> getSortedLabelsAndAddresses() const noexcept;

    /**
     * Sets a referencing type to an address. Useful to force referencing, or force non-referencing.
     * @param startAddress the start address.
     * @param endExclusiveAddress the end address, excluded.
     * @param referencingType the type of referencing.
     */
    void setReferencingType(int startAddress, int endExclusiveAddress, ReferencingType referencingType) noexcept;

    /**
     * Indicates the referencing type at the given address. One type of referencing may be forced. "None" means the normal behavior must be applied.
     * @param address the address.
     * @return the referencing type.
     */
    ReferencingType getReferencingType(int address) const noexcept;

    /** @return the possible Labels and their address, for labels that are declared but referenced (so not declaring them will make an error on compiling). */
    std::vector<LabelAndAddress> getUndeclaredReferencedLabels() const noexcept;

private:
    /**
     * Returns the best reference to the given address, and from a limited selection window by default.
     * @param address the address.
     * @return the reference, maybe with an offset, or empty label if none could be found.
     */
    Reference getReferenceAround(int address) const noexcept;

    /**
     * Checks whether the given label may be External (via its possible tag). If yes, a new one is returned.
     * @param label the base label.
     * @param externalOut will be filled, indicating whether it is actually external.
     * @return the label, renamed or not.
     */
    static juce::String checkIfExternalAndRename(const juce::String& label, bool& externalOut) noexcept;

    std::map<int, std::vector<Label>> addressToLabels;                                  // Map linking addresses to their label.
    std::map<juce::String, int> labelToAddress;                                         // Convenience map linking a label to its address.
    std::set<juce::String> referencedLabels;                                            // Set containing the referenced labels (generated or not).

    std::set<juce::String> declaredLabels;                                              // Set containing the declared labels.
    std::map<int, ReferencingType> addressToReferencingType;                            // Links an address to a possible referencing type.
};

}    // namespace disark
