#pragma once

#include <juce_core/juce_core.h>

namespace disark
{

/** Holds a label name and its address. */
class LabelAndAddress
{
public:
    /**
     * Constructor.
     * @param label the label.
     * @param address the address.
     */
    LabelAndAddress(juce::String label, int address) noexcept;

    /**
     * Builds an instance with data indicating an error.
     * @return the instance.
     */
    static LabelAndAddress buildError() noexcept;

    /** @return the label. */
    const juce::String& getLabel() const noexcept;
    /** @return the address. */
    int getAddress() const noexcept;

private:
    juce::String label;     // The name of the label.
    int address;            // The address. Must be valid.
};

}    // namespace disark
