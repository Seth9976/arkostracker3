#include "../../catch.hpp"

#include <BinaryData.h>

#include "../../../source/import/at2/At2SongImporter.h"
#include "../common/CheckHarmlessGrenade.h"

namespace arkostracker 
{

TEST_CASE("AT2 Import, wrong file", "[At2SongImporter]")
{
    // Loads a wrong song.
    juce::MemoryInputStream inputStream(BinaryData::Kangaroo__Alienall_128, static_cast<size_t>(BinaryData::Kangaroo__Alienall_128Size), false);

    // Parses.
    const At2SongImporter importer;
    REQUIRE_FALSE(importer.doesFormatMatch(inputStream, "aks"));
}

TEST_CASE("AT2 Import, format ok", "[At2SongImporter]")
{
    // Loads a song.
    juce::MemoryInputStream inputStream(BinaryData::At2TarghanAHarmlessGrenade_aks, static_cast<size_t>(BinaryData::At2TarghanAHarmlessGrenade_aksSize), false);

    // Parses.
    const At2SongImporter importer;
    REQUIRE(importer.doesFormatMatch(inputStream, "aks"));
}

TEST_CASE("AT2 Import, load song ok", "[At2SongImporter]")
{
    // Loads a song.
    juce::MemoryInputStream inputStream(BinaryData::At2TarghanAHarmlessGrenade_aks, static_cast<size_t>(BinaryData::At2TarghanAHarmlessGrenade_aksSize), false);

    // Parses.
    At2SongImporter importer;
    REQUIRE(importer.doesFormatMatch(inputStream, "aks"));
    inputStream.setPosition(0);
    auto result = importer.loadSong(inputStream, ImportConfiguration());

    REQUIRE(result != nullptr);
    auto& song = result->song;
    auto& report = result->errorReport;
    REQUIRE(report != nullptr);
    REQUIRE(report->isOk());
    REQUIRE(report->getWarningCount() == 0);
    REQUIRE(song != nullptr);

    // Checks the Song.
    CheckHarmlessGrenade::check(*song);
}

}   // namespace arkostracker
