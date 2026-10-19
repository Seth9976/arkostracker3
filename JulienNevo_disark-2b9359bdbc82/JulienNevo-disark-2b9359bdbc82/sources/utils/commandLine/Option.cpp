#include "Option.h"

#include "CommandLineConstants.h"

namespace disark
{

Option::Option(const juce::String& newShortOption, const juce::String& newLongOption) noexcept
{
    // Makes sure the "-" from is not here.
    jassert(newShortOption.isEmpty() || !newShortOption.startsWith(CommandLineConstants::stringShortOptionTag));
    jassert(newLongOption.isEmpty() || !newLongOption.startsWith(CommandLineConstants::stringLongOptionTag));

    // If used, remove the tags before storage.
    shortOption = (newShortOption.isEmpty() ? juce::String() : newShortOption);
    longOption = (newLongOption.isEmpty() ? juce::String() : newLongOption);
}

Option Option::buildEmptyOption() noexcept
{
    return { juce::String(), juce::String() };
}

Option Option::buildShortOption(const juce::String& option) noexcept
{
    return { option, juce::String() };
}

Option Option::buildLongOption(const juce::String& option) noexcept
{
    return { juce::String(), option };
}

Option Option::buildOption(const juce::String& shortOption, const juce::String& longOption) noexcept
{
    return { shortOption, longOption };
}

bool Option::doesMatchWithStringIfOption(const juce::String& optionWithoutTag, const bool isShortOption) const noexcept
{
    // The option should never be empty.
    jassert(optionWithoutTag.length() > 0);
    if (optionWithoutTag.length() == 0) {
        return false;
    }
    return isShortOption ? (optionWithoutTag == shortOption) : (optionWithoutTag == longOption);
}

std::pair<juce::String, juce::String> Option::getOptionNames() const noexcept
{
    return { shortOption, longOption };
}

}    // namespace disark
