#include "LabelAndAddress.h"

namespace disark
{

LabelAndAddress::LabelAndAddress(juce::String pLabel, const int pAddress) noexcept :
        label(std::move(pLabel)),
        address(pAddress)
{
}

const juce::String& LabelAndAddress::getLabel() const noexcept
{
    return label;
}

int LabelAndAddress::getAddress() const noexcept
{
    return address;
}

LabelAndAddress LabelAndAddress::buildError() noexcept
{
    return { juce::String(), -1 };
}

}    // namespace disark
