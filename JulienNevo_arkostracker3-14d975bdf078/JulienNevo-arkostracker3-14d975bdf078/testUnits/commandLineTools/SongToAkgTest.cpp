#include "../catch.hpp"

#include <juce_core/juce_core.h>

#include "../../source/commandLineTools/songToAkg/ToolSongToAkg.h"
#include "../../source/export/akg/AkgExporter.h"
#include "../../source/utils/MemoryBlockUtil.h"
#include "../helper/CommandLineToolTestHelper.h"
#include "../helper/RasmHelper.h"
#include "../helper/SongTestHelper.h"
#include "BinaryData.h"

namespace arkostracker
{

class TestHelper
{
public:
    static std::pair<bool, std::unique_ptr<SongExportResult>> loadAndExportToAkg()
    {
        const auto song = SongTestHelper::loadSong(BinaryData::Targhan__Midline_Process__Molusk_sks, BinaryData::Targhan__Midline_Process__Molusk_sksSize);
        const ExportConfiguration exportConfiguration(SourceGeneratorConfiguration::buildZ80(), { song->getFirstSubsongId() }, "label");
        AkgExporter akgExporter(*song, exportConfiguration);
        auto result = akgExporter.performTask();
        REQUIRE(result.first);

        return result;
    }
};

TEST_CASE("akg, help", "[SongToAkgTest]")
{
    const juce::String paramExec = "exec";

    char* args[] = {
        paramExec.getCharPointer().getAddress(),
        nullptr,
    };

    const auto result = ToolSongToAkg::execute(1, args);
    REQUIRE((result == 0));
}

TEST_CASE("akg, unknown parameter, error", "[SongToAkgTest]")
{
    const juce::String paramExec = "exec";
    const juce::String param1 = "--unknown";

    char* args[] = {
        paramExec.getCharPointer().getAddress(),
        param1.getCharPointer().getAddress(),
        nullptr,
    };

    const auto result = ToolSongToAkg::execute(2, args);
    REQUIRE((result == -1));
}

TEST_CASE("akg, binary without address, error", "[SongToAkgTest]")
{
    const auto [inputFilePath, inputFile] = CommandLineToolTestHelper::createTempMusicFile();

    const juce::String paramExec = "exec";
    const juce::String paramOutputFile = "outputFile";
    const juce::String paramExportAsBinary = "--exportAsBinary";

    char* args[] = {
        paramExec.getCharPointer().getAddress(),
        inputFilePath.getCharPointer().getAddress(),
        paramOutputFile.getCharPointer().getAddress(),
        paramExportAsBinary.getCharPointer().getAddress(),
        nullptr,
    };

    const auto result = ToolSongToAkg::execute(4, args);
    REQUIRE((result == -1));

    CommandLineToolTestHelper::deleteFile(inputFilePath);
}

TEST_CASE("akg to source", "[SongToAkgTest]")
{
    const auto [inputFilePath, inputFile] = CommandLineToolTestHelper::createTempMusicFile();
    const auto [outputFilePath, outputFile] = CommandLineToolTestHelper::createTempFile();

    const juce::String paramExec = "exec";

    char* args[] = {
        paramExec.getCharPointer().getAddress(),
        inputFilePath.getCharPointer().getAddress(),
        outputFilePath.getCharPointer().getAddress(),
        nullptr,
    };

    // Performs the tool operation.
    const auto result = ToolSongToAkg::execute(3, args);
    REQUIRE((result == 0));

    // Gets the generated data.
    const auto generatedMusicSourceMemoryBlock = MemoryBlockUtil::fromFile(outputFile);
    REQUIRE((generatedMusicSourceMemoryBlock != nullptr));

    // Exports the Song as a stand alone source.
    const auto [success, songExportResult] = TestHelper::loadAndExportToAkg();

    CommandLineToolTestHelper::deleteFile(inputFilePath);
    CommandLineToolTestHelper::deleteFile(outputFilePath);

    // Compiles the sources and compares the binaries.
    const auto sameBinary = RasmHelper::assembleAndCompareSources(*generatedMusicSourceMemoryBlock, songExportResult->getAggregatedData());
    REQUIRE(sameBinary);
}

TEST_CASE("akg to binary", "[SongToAkgTest]")
{
    const auto [inputFilePath, inputFile] = CommandLineToolTestHelper::createTempMusicFile();
    const auto [outputFilePath, outputFile] = CommandLineToolTestHelper::createTempFile();

    const juce::String paramExec = "exec";
    const juce::String paramExportAsBinary = "--exportAsBinary";
    const juce::String paramEncodingAddress = "--encodingAddress";
    const juce::String paramEncodingAddressAddress = "0x4000";

    char* args[] = {
        paramExec.getCharPointer().getAddress(),
        inputFilePath.getCharPointer().getAddress(),
        outputFilePath.getCharPointer().getAddress(),
        paramExportAsBinary.getCharPointer().getAddress(),
        paramEncodingAddress.getCharPointer().getAddress(),
        paramEncodingAddressAddress.getCharPointer().getAddress(),
        nullptr,
    };

    // Performs the tool operation.
    const auto result = ToolSongToAkg::execute(6, args);
    REQUIRE((result == 0));

    // Gets the generated data.
    const auto generatedMusicBinaryMemoryBlock = MemoryBlockUtil::fromFile(outputFile);
    REQUIRE((generatedMusicBinaryMemoryBlock != nullptr));

    // Exports the Song as a source.
    const auto [success, songExportResult] = TestHelper::loadAndExportToAkg();
    auto expectedSourcesMemoryBlock = songExportResult->getAggregatedData();
    const auto expectedBinaryMemoryBlock = RasmHelper::assembleSource(expectedSourcesMemoryBlock, 0x4000);

    CommandLineToolTestHelper::deleteFile(inputFilePath);
    CommandLineToolTestHelper::deleteFile(outputFilePath);

    // Compiles the sources and compares the binaries.
    const auto comparisonSuccess = MemoryBlockUtil::compare(*generatedMusicBinaryMemoryBlock, *expectedBinaryMemoryBlock);
    REQUIRE(comparisonSuccess);
}

}   // namespace arkostracker
