#include "Symbol.h"

namespace disark
{

Symbol::Symbol(juce::String pLabel, const int pAddress, const bool pGenerated) noexcept :
    label(std::move(pLabel)),
    address(pAddress),
    generated(pGenerated)
{
}

const juce::String& Symbol::getLabel() const
{
    return label;
}

int Symbol::getAddress() const
{
    return address;
}

bool Symbol::isGenerated() const
{
    return generated;
}

}    // namespace disark
