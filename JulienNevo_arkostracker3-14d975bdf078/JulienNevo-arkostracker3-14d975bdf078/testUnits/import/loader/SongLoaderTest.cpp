#include "../../catch.hpp"

#include <BinaryData.h>

#include "../../../source/import/loader/SongLoader.h"
#include "../../../source/utils/FileUtil.h"
#include "../../../source/utils/MemoryBlockUtil.h"

namespace arkostracker 
{

TEST_CASE("load song, no match", "[SongLoader]")
{
    // Loads the (wrong) song.
    juce::MemoryInputStream inputStream(BinaryData::RetrigInBars_png, BinaryData::RetrigInBars_pngSize, false);

    SongLoader loader;
    const auto result = loader.loadSong(inputStream, "128", false, nullptr);

    REQUIRE(result != nullptr);
    REQUIRE(result->status == SongLoader::ImportStatus::noMatchingFormat);
    REQUIRE(result->song == nullptr);
    REQUIRE(result->errorReport == nullptr);
}

TEST_CASE("load song, soundtrakker, no configuration", "[SongLoader]")
{
    // Loads the song.
    juce::MemoryInputStream inputStream(BinaryData::Targhan__Golio_128, BinaryData::Targhan__Golio_128Size, false);

    SongLoader loader;
    const auto result = loader.loadSong(inputStream, "128", false, nullptr);

    REQUIRE(result != nullptr);
    REQUIRE(result->status == SongLoader::ImportStatus::ok);
    REQUIRE(result->song != nullptr);
    REQUIRE(result->song->getTitle() == "GOLIO");
    REQUIRE(result->errorReport != nullptr);
    REQUIRE(result->errorReport->isOk());
}

TEST_CASE("load song, at2, no configuration", "[SongLoader]")
{
    // Loads the song.
    juce::MemoryInputStream inputStream(BinaryData::At2TarghanAHarmlessGrenade_aks, BinaryData::At2TarghanAHarmlessGrenade_aksSize, false);

    SongLoader loader;
    const auto result = loader.loadSong(inputStream, "abc", false, nullptr);

    REQUIRE(result != nullptr);
    REQUIRE(result->status == SongLoader::ImportStatus::ok);
    REQUIRE(result->song != nullptr);
    REQUIRE(result->song->getTitle() == "A Harmless Grenade");
    REQUIRE(result->errorReport != nullptr);
    REQUIRE(result->errorReport->isOk());
}

TEST_CASE("load song, starkos, no configuration", "[SongLoader]")
{
    // Loads the song.
    juce::MemoryInputStream inputStream(BinaryData::Targhan__DemoIzArt__Twist_Part_sks, BinaryData::Targhan__DemoIzArt__Twist_Part_sksSize, false);

    SongLoader loader;
    const auto result = loader.loadSong(inputStream, "abc", false, nullptr);

    REQUIRE(result != nullptr);
    REQUIRE(result->status == SongLoader::ImportStatus::ok);
    REQUIRE(result->song != nullptr);
    REQUIRE(result->song->getTitle() == "Untitled");
    REQUIRE(result->errorReport != nullptr);
    REQUIRE(result->errorReport->isOk());
}

TEST_CASE("load song, at1, zipped", "[SongLoader]")
{
    // Loads the song.
    juce::MemoryInputStream inputStream(BinaryData::At1Demo_aks, BinaryData::At1Demo_aksSize, false);

    // Creates a temporary file with the music data.
    const auto tempFile = juce::File::createTempFile("aks");
    FileUtil::saveMemoryBlockToFile(tempFile, MemoryBlockUtil::fromInputStream(inputStream));

    SongLoader loader;
    const auto result = loader.loadSong(tempFile, false);

    REQUIRE(result != nullptr);
    REQUIRE(result->status == SongLoader::ImportStatus::ok);
    REQUIRE(result->song != nullptr);
    REQUIRE(result->song->getTitle() == "Demo");
    REQUIRE(result->errorReport != nullptr);
    REQUIRE(result->errorReport->isOk());

    (void)tempFile.deleteFile();
}

TEST_CASE("load song, at2, zipped", "[SongLoader]")
{
    // Loads the song.
    juce::MemoryInputStream inputStream(BinaryData::At2SlapFight2Zipped_aks, BinaryData::At2SlapFight2Zipped_aksSize, false);

    // Creates a temporary file with the music data.
    const auto tempFile = juce::File::createTempFile("aks");
    FileUtil::saveMemoryBlockToFile(tempFile, MemoryBlockUtil::fromInputStream(inputStream));

    SongLoader loader;
    const auto result = loader.loadSong(tempFile, false);

    REQUIRE(result != nullptr);
    REQUIRE(result->status == SongLoader::ImportStatus::ok);
    REQUIRE(result->song != nullptr);
    REQUIRE(result->song->getTitle() == "New song");
    REQUIRE(result->errorReport != nullptr);
    REQUIRE(result->errorReport->isOk());

    (void)tempFile.deleteFile();
}

TEST_CASE("load song, at3, unzipped", "[SongLoader]")
{
    // Loads the song.
    juce::MemoryInputStream inputStream(BinaryData::At3Sarkboteur_xml, BinaryData::At3Sarkboteur_xmlSize, false);

    // Creates a temporary file with the music data.
    const auto tempFile = juce::File::createTempFile("aks");
    FileUtil::saveMemoryBlockToFile(tempFile, MemoryBlockUtil::fromInputStream(inputStream));

    SongLoader loader;
    const auto result = loader.loadSong(tempFile, false);

    REQUIRE(result != nullptr);
    REQUIRE(result->status == SongLoader::ImportStatus::ok);
    REQUIRE(result->song != nullptr);
    REQUIRE(result->song->getTitle() == "Sarkboteur");
    REQUIRE(result->errorReport != nullptr);
    REQUIRE(result->errorReport->isOk());

    (void)tempFile.deleteFile();
}

TEST_CASE("load song, sid custom", "[SongLoader]")
{
    // Loads the song.
    juce::MemoryInputStream inputStream(BinaryData::AT3SidCapabilityCustom_xml, BinaryData::AT3SidCapabilityCustom_xmlSize, false);

    // Creates a temporary file with the music data.
    const auto tempFile = juce::File::createTempFile("aks");
    FileUtil::saveMemoryBlockToFile(tempFile, MemoryBlockUtil::fromInputStream(inputStream));

    SongLoader loader;
    const auto result = loader.loadSong(tempFile, false);
    (void)tempFile.deleteFile();

    const auto& song = result->song;
    REQUIRE((result != nullptr));
    REQUIRE((result->status == SongLoader::ImportStatus::ok));
    REQUIRE((song != nullptr));
    REQUIRE((song->getTitle() == "Untitled"));
    REQUIRE((result->errorReport != nullptr));
    REQUIRE(result->errorReport->isOk());

    const auto metadata = song->getSubsongMetadata(song->getFirstSubsongId());
    REQUIRE((metadata.getSidPlayerCapability() == SidPlayerCapability::buildForCustom(8000, 5, 8)));
}

TEST_CASE("load song, sid atari st", "[SongLoader]")
{
    // Loads the song.
    juce::MemoryInputStream inputStream(BinaryData::AT3SidCapabilityAtariSt_xml, BinaryData::AT3SidCapabilityAtariSt_xmlSize, false);

    // Creates a temporary file with the music data.
    const auto tempFile = juce::File::createTempFile("aks");
    FileUtil::saveMemoryBlockToFile(tempFile, MemoryBlockUtil::fromInputStream(inputStream));

    SongLoader loader;
    const auto result = loader.loadSong(tempFile, false);
    (void)tempFile.deleteFile();

    const auto& song = result->song;
    REQUIRE((result != nullptr));
    REQUIRE((result->status == SongLoader::ImportStatus::ok));
    REQUIRE((song != nullptr));
    REQUIRE((song->getTitle() == "Untitled"));
    REQUIRE((result->errorReport != nullptr));
    REQUIRE(result->errorReport->isOk());

    const auto metadata = song->getSubsongMetadata(song->getFirstSubsongId());
    REQUIRE((metadata.getSidPlayerCapability() == SidPlayerCapability::buildForAtariSt()));
}

// TODO more tests with importer with configuration.

}   // namespace arkostracker

