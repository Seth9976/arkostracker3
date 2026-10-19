#include "../../../catch.hpp"

#include <BinaryData.h>
#include <juce_core/juce_core.h>

#include "../../../../source/business/song/tool/InlineArpeggioConverter.h"
#include "../../../../source/import/loader/SongLoader.h"

namespace arkostracker 
{

static void checkArpeggio(const Song& song, int arpeggioIndex, const std::vector<int>& arpeggioValues) noexcept
{
    const auto& expressionHandler = song.getConstExpressionHandler(true);
    const auto arpeggio = expressionHandler.getExpressionCopy(arpeggioIndex);

    const auto endIndex = arpeggio.getEnd();
    REQUIRE(endIndex == arpeggio.getLength() - 1);
    REQUIRE(arpeggio.getSpeed() == 0);
    REQUIRE(arpeggio.getLoopStart() == 0);

    // Checks all the values.
    for (auto valueIndex = 0; valueIndex <= endIndex; ++valueIndex) {
        const auto value = arpeggio.getValue(valueIndex);
        REQUIRE(value == arpeggioValues.at(static_cast<size_t>(valueIndex)));
    }
}

static void checkCell(Song& song, int lineNumber, int arpeggioNumber, int columnIndex) noexcept
{
    constexpr auto channelIndex = 0;
    constexpr auto position = 0;
    const auto subsongId = song.getFirstSubsongId();
    const auto cell = song.getCell(Location(subsongId, position, lineNumber), channelIndex);

    REQUIRE(cell.hasEffects());
    const auto [effectIndex, effectValue] = cell.findWithIndex(Effect::arpeggioTable);

    // The effect should be where we expect it to be.
    REQUIRE(effectIndex == columnIndex);
    REQUIRE(effectValue.getValueRef().getEffectLogicalValue() == arpeggioNumber);
}






TEST_CASE("InlineArpeggioConverter, success", "[InlineArpeggioConverter]")
{
    // Given.
    juce::MemoryInputStream inputStream(BinaryData::At2ArpeggioInlineConverter_Simple_xml, BinaryData::At2ArpeggioInlineConverter_Simple_xmlSize, false);
    SongLoader loader;
    const auto result = loader.loadSong(inputStream, "aks", false, nullptr);
    REQUIRE(result != nullptr);
    REQUIRE(result->errorReport != nullptr);
    REQUIRE(result->errorReport->isOk());

    const std::shared_ptr song = std::move(result->song);

    // When.
    InlineArpeggioConverter converter(*song);
    const auto success = converter.convert();

    // Then.
    REQUIRE(success);

    // Checks the Arpeggios.
    // 037, 047, 0235, 0c06, 0370, 0470, 0123
    REQUIRE(song->getExpressionHandler(true).getCount() == 8);
    checkArpeggio(*song, 1, std::vector { 0, 3, 7 });
    checkArpeggio(*song, 2, std::vector { 0, 4, 7 });
    checkArpeggio(*song, 3, std::vector { 0, 2, 3, 5 });
    checkArpeggio(*song, 4, std::vector { 0, 0xc, 0, 6 });
    checkArpeggio(*song, 5, std::vector { 0, 3, 7, 0 });
    checkArpeggio(*song, 6, std::vector { 0, 4, 7, 0 });
    checkArpeggio(*song, 7, std::vector { 0, 1, 2, 3 });

    // Checks the Track.
    checkCell(*song, 0,   0, 0);        // Arp 0 on column 0.
    checkCell(*song, 0x5, 1, 0);        // Arp 1 on column 0.
    checkCell(*song, 0x8, 2, 1);        // Arp 2 on column 1.
    checkCell(*song, 0xe, 3, 1);        // Arp 3 on column 1.
    checkCell(*song, 0x12, 4, 1);       // Arp 4 on column 1.
    checkCell(*song, 0x1d, 0, 0);       // Arp 0 on column 0.
    checkCell(*song, 0x20, 5, 1);       // Arp 5 on column 1.
    checkCell(*song, 0x24, 6, 1);       // Arp 6 on column 1.
    checkCell(*song, 0x26, 6, 1);       // Arp 6 on column 1.
    checkCell(*song, 0x2e, 1, 0);       // Arp 1 on column 0.
    checkCell(*song, 0x34, 7, 2);       // Arp 7 on column 2.
}

TEST_CASE("InlineArpeggioConverter, too many arpeggios", "[InlineArpeggioConverter]")
{
    // Given.
    juce::MemoryInputStream inputStream(BinaryData::At2ArpeggioInlineConverter_TooMany_xml, BinaryData::At2ArpeggioInlineConverter_TooMany_xmlSize, false);
    SongLoader loader;
    const auto result = loader.loadSong(inputStream, "aks", false, nullptr);
    REQUIRE(result != nullptr);
    REQUIRE(result->errorReport != nullptr);
    REQUIRE(result->errorReport->isOk());

    const std::shared_ptr song = std::move(result->song);

    // When.
    InlineArpeggioConverter converter(*song);
    const auto success = converter.convert();

    // Then.
    REQUIRE_FALSE(success);
}

}   // namespace arkostracker
