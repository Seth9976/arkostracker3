#pragma once

#include <juce_core/juce_core.h>

namespace arkostracker
{

class SongBuilder;

class FurnaceInstrumentReader
{
public:
    /** Reads an instrument. */
    static bool readInstrument(SongBuilder& songBuilder, juce::InputStream& inputStream, int blockSize, int currentInstrumentIndex) noexcept;
    /** Reads the instrument macro, filling the current instrument. */
    static bool readInstrumentMacro(SongBuilder& songBuilder, juce::InputStream& inputStream) noexcept;

private:
    static const std::map<std::pair<int, int>, int> numDenToRatio;

    /**
     * @return the value inside a given table, at the index, of the last item if not possible.
     * If the table is empty, a default value is returned.
     */
    template<class T>
    static T getValue(const size_t index, const std::vector<T>& table) noexcept
    {
        if (table.empty()) {        // Security, shouldn't happen.
            return T();
        }
        return table.at(std::min(index, table.size() - 1));
    }
};

}   // namespace arkostracker
