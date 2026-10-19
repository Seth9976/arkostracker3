#include "../catch.hpp"

#include <juce_core/juce_core.h>

#include "BinaryData.h"
#include "../../source/commandLineTools/z80Profiler/ToolZ80Profiler.h"
#include "../../source/utils/FileUtil.h"
#include "../../source/utils/MemoryBlockUtil.h"
#include "../helper/CommandLineToolTestHelper.h"
#include "../helper/RasmHelper.h"

namespace arkostracker
{

TEST_CASE("profiler, help", "[Z80ProfilerTest]")
{
    const juce::String paramExec = "exec";

    char* args[] = {
        paramExec.getCharPointer().getAddress(),
        nullptr,
    };

    const auto result = ToolZ80Profiler::execute(1, args);
    REQUIRE((result == 0));
}

TEST_CASE("profiler, simple with csv", "[Z80ProfilerTest]")
{
    const juce::String paramExec = "exec";
    const juce::String paramLoadAddress = "-l";
    const juce::String paramLoadAddressValue = "0x2000";
    const juce::String paramExecCalls = "--execCalls";
    const juce::String paramExecCallsValue = "5";

    const auto [inputFilePath, inputFile] = CommandLineToolTestHelper::createTempFile();
    const auto [outputFilePath, outputFile] = CommandLineToolTestHelper::createTempFile();

    auto source = juce::String(
        R"(
   org #2000
    ;Hooks.
    jp Init     ;Start +0.
    jp Exec     ;Start +3.

Init
    ds 10,0
    jp #ffff    ;Go back to the profiler.

Exec
    ds 20,0
    jp #ffff    ;Go back to the profiler.
)"
    );

    // Generates a binary into a file.
    auto sourceMemoryBlock = MemoryBlockUtil::fromString(source);
    const auto binaryMemoryBlock = RasmHelper::assembleSource(sourceMemoryBlock);
    REQUIRE((binaryMemoryBlock != nullptr));
    const auto saveFileSuccess = FileUtil::saveMemoryBlockToFile(inputFile, *binaryMemoryBlock);
    REQUIRE(saveFileSuccess);

    char* args[] = {
        paramExec.getCharPointer().getAddress(),
        inputFilePath.getCharPointer().getAddress(),
        outputFilePath.getCharPointer().getAddress(),
        paramLoadAddress.getCharPointer().getAddress(),
        paramLoadAddressValue.getCharPointer().getAddress(),
        paramExecCalls.getCharPointer().getAddress(),
        paramExecCallsValue.getCharPointer().getAddress(),
        nullptr,
    };

    // Performs.
    const auto result = ToolZ80Profiler::execute(7, args);
    REQUIRE((result == 0));

    REQUIRE((ToolZ80Profiler::getInitNops() == 10));

    // Checks the CSV.
    const auto csvMemoryBlock = MemoryBlockUtil::fromFile(outputFile);
    CommandLineToolTestHelper::deleteFile(inputFilePath);
    CommandLineToolTestHelper::deleteFile(outputFilePath);
    REQUIRE((csvMemoryBlock != nullptr));
    const auto csvLines = MemoryBlockUtil::extractStrings(*csvMemoryBlock);
    REQUIRE((
        csvLines == std::vector<juce::String> {
            "Execution index,nop count",
            "0,20",
            "1,20",
            "2,20",
            "3,20",
            "4,20",
        }
    ));
}

class ProfilerTestHelper
{
public:
    static void perform(const void* data, size_t dataSize)
    {
        const juce::String paramExec = "exec";
        const juce::String paramLoadAddress = "--loadAddress";
        const juce::String paramLoadAddressValue = "0x500";
        const juce::String paramExecCalls = "--execCalls";
        const juce::String paramExecCallsValue = "5";

        const auto [inputFilePath, inputFile] = CommandLineToolTestHelper::createTempFile();
        const auto [outputFilePath, outputFile] = CommandLineToolTestHelper::createTempFile();

        // Generates a binary into a file.
        const auto binaryMemoryBlock = juce::MemoryBlock(data, dataSize);
        const auto saveFileSuccess = FileUtil::saveMemoryBlockToFile(inputFile, binaryMemoryBlock);
        REQUIRE(saveFileSuccess);

        char* args[] = {
            paramExec.getCharPointer().getAddress(),
            inputFilePath.getCharPointer().getAddress(),
            outputFilePath.getCharPointer().getAddress(),
            paramLoadAddress.getCharPointer().getAddress(),
            paramLoadAddressValue.getCharPointer().getAddress(),
            paramExecCalls.getCharPointer().getAddress(),
            paramExecCallsValue.getCharPointer().getAddress(),
            nullptr,
        };

        // Performs.
        const auto result = ToolZ80Profiler::execute(7, args);
        REQUIRE((result == 0));

        REQUIRE((ToolZ80Profiler::getInitNops() == 0));

        // Checks the CSV.
        const auto csvMemoryBlock = MemoryBlockUtil::fromFile(outputFile);
        CommandLineToolTestHelper::deleteFile(inputFilePath);
        CommandLineToolTestHelper::deleteFile(outputFilePath);
        REQUIRE((csvMemoryBlock != nullptr));
        const auto csvLines = MemoryBlockUtil::extractStrings(*csvMemoryBlock);
        REQUIRE((
            csvLines == std::vector<juce::String> {
                "Execution index,nop count",
                "0,1806",
                "1,541",
                "2,541",
                "3,541",
                "4,586",
            }
        ));
    }
};

TEST_CASE("profiler, abadia_chp, with csv, no amsdos header", "[Z80ProfilerTest]")
{
    ProfilerTestHelper::perform(BinaryData::ABADIA1_CHPZ80_Load500_BIN, BinaryData::ABADIA1_CHPZ80_Load500_BINSize);
}

TEST_CASE("profiler, abadia_chp, with csv, with amsdos header", "[Z80ProfilerTest]")
{
    ProfilerTestHelper::perform(BinaryData::ABADIA1_CHPZ80_withHeader_BIN, BinaryData::ABADIA1_CHPZ80_withHeader_BINSize);
}

}   // namespace arkostracker
