#include "../../../catch.hpp"

#include <BinaryData.h>
#include <juce_core/juce_core.h>

#include "../../../../source/business/song/tool/InstrumentCounter.h"
#include "../../../../source/import/loader/SongLoader.h"

namespace arkostracker
{

TEST_CASE("InstrumentCounter, sarkboteur", "[InstrumentCounter]")
{
    // Given.
    juce::MemoryInputStream inputStream(BinaryData::At3Sarkboteur_xml, BinaryData::At3Sarkboteur_xmlSize, false);
    SongLoader loader;
    const auto result = loader.loadSong(inputStream, "aks", false, nullptr);
    REQUIRE(result != nullptr);
    REQUIRE(result->errorReport != nullptr);
    REQUIRE(result->errorReport->isOk());

    const std::shared_ptr song = std::move(result->song);

    // When.
    const auto countResult = InstrumentCounter::countInstruments(*song);

    // Then.
    REQUIRE(countResult.size() == 17);
    auto index = 1;
    REQUIRE(countResult.at(static_cast<size_t>(index - 1)) ==
                           InstrumentCounter::InstrumentResult(song->getInstrumentId(index).getValue(),
                               "Bass", index, 96, false));
    ++index;

    REQUIRE(countResult.at(static_cast<size_t>(index - 1)) ==
                           InstrumentCounter::InstrumentResult(song->getInstrumentId(index).getValue(),
                               "Arps", index, 0, false));
    ++index;

    REQUIRE(countResult.at(static_cast<size_t>(index - 1)) ==
                           InstrumentCounter::InstrumentResult(song->getInstrumentId(index).getValue(),
                               "ArpsHard", index, 0, false));
    ++index;

    REQUIRE(countResult.at(static_cast<size_t>(index - 1)) ==
                           InstrumentCounter::InstrumentResult(song->getInstrumentId(index).getValue(),
                               "BD", index, 246, true));
    ++index;
    REQUIRE(countResult.at(static_cast<size_t>(index - 1)) ==
                           InstrumentCounter::InstrumentResult(song->getInstrumentId(index).getValue(),
                               "SN", index, 284, true));
    ++index;
    REQUIRE(countResult.at(static_cast<size_t>(index - 1)) ==
                           InstrumentCounter::InstrumentResult(song->getInstrumentId(index).getValue(),
                               "TomHigh", index, 140, true));
    ++index;
    REQUIRE(countResult.at(static_cast<size_t>(index - 1)) ==
                           InstrumentCounter::InstrumentResult(song->getInstrumentId(index).getValue(),
                               "TomLow", index, 84, true));
    ++index;

    REQUIRE(countResult.at(static_cast<size_t>(index - 1)) ==
                           InstrumentCounter::InstrumentResult(song->getInstrumentId(index).getValue(),
                               "Low", index, 38, false));
    ++index;

    REQUIRE(countResult.at(static_cast<size_t>(index - 1)) ==
                           InstrumentCounter::InstrumentResult(song->getInstrumentId(index).getValue(),
                               "Mel", index, 113, false));
    ++index;

    REQUIRE(countResult.at(static_cast<size_t>(index - 1)) ==
                           InstrumentCounter::InstrumentResult(song->getInstrumentId(index).getValue(),
                               "Bass2", index, 810, false));
    ++index;

    REQUIRE(countResult.at(static_cast<size_t>(index - 1)) ==
                           InstrumentCounter::InstrumentResult(song->getInstrumentId(index).getValue(),
                               "Bass3", index, 6, false));
    ++index;

    REQUIRE(countResult.at(static_cast<size_t>(index - 1)) ==
                           InstrumentCounter::InstrumentResult(song->getInstrumentId(index).getValue(),
                               "MelSlow", index, 59, false));
    ++index;

    REQUIRE(countResult.at(static_cast<size_t>(index - 1)) ==
                           InstrumentCounter::InstrumentResult(song->getInstrumentId(index).getValue(),
                               "LowHard", index, 17, false));
    ++index;

    REQUIRE(countResult.at(static_cast<size_t>(index - 1)) ==
                           InstrumentCounter::InstrumentResult(song->getInstrumentId(index).getValue(),
                               "Full", index, 17, false));
    ++index;

    REQUIRE(countResult.at(static_cast<size_t>(index - 1)) ==
                           InstrumentCounter::InstrumentResult(song->getInstrumentId(index).getValue(),
                               "MelAttack", index, 116, false));
    ++index;

    REQUIRE(countResult.at(static_cast<size_t>(index - 1)) ==
                           InstrumentCounter::InstrumentResult(song->getInstrumentId(index).getValue(),
                               "Arps2", index, 5, false));
    ++index;

    REQUIRE(countResult.at(static_cast<size_t>(index - 1)) ==
                           InstrumentCounter::InstrumentResult(song->getInstrumentId(index).getValue(),
                               "Empty", index, 0, false));
}

TEST_CASE("InstrumentCounter, default song", "[InstrumentCounter]")
{
    // Given.
    const auto song = Song::buildDefaultSong(true);

    // When.
    const auto countResult = InstrumentCounter::countInstruments(*song);

    // Then.
    REQUIRE(countResult.size() == 1);
    constexpr auto index = 1;
    REQUIRE(countResult.at(static_cast<size_t>(index - 1)) ==
                           InstrumentCounter::InstrumentResult(song->getInstrumentId(index).getValue(),
                               "Beep", index, 0, false));

}

}   // namespace arkostracker
