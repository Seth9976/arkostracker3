#include "../../catch.hpp"

#include <BinaryData.h>
#include <juce_core/juce_core.h>

#include "../../../source/utils/FileUtil.h"
#include "../../../source/utils/MemoryBlockUtil.h"
#include "../../../source/utils/RasmUtil.h"
#include "../../../thirdParty/rasm/rasm.h"
#include "../../helper/RasmHelper.h"

namespace arkostracker
{

static void compare(const unsigned char* data1, const unsigned char* data2, const int length)
{
    // Use this one (faster), but the other below is useful to know where the bug happened.
    //REQUIRE(0 == memcmp(data1, data2, length));

    // Compares each byte.
    for (auto i = 0; i < length; ++i) {
        const auto firstValue = data1[i];
        const auto secondValue = data2[i];
        REQUIRE(firstValue == secondValue);
    }
}

static void assembleSourceFromMemoryBlock(juce::MemoryBlock& sourceMemoryBlock, const bool commentIncludes) {
    auto memoryBlockToCompile = &sourceMemoryBlock;

    // Finds the "includes" and comments them (else, problem with Rasm Include problem, even if
    // they are not supposed to be assembled).
    // Ok, this is done even if not necessary... Who cares?
    auto memoryBlockWithoutInclude = RasmUtil::commentIncludes(sourceMemoryBlock);
    if (commentIncludes) {
        memoryBlockToCompile = &memoryBlockWithoutInclude;
    }

    const auto generatedSourceResult = RasmHelper::assembleSource(*memoryBlockToCompile);

    REQUIRE(generatedSourceResult != nullptr);
    REQUIRE(generatedSourceResult->getSize() > 0);
}

TEST_CASE("Rasm, short AKY", "[Rasm]")
{
    // Given.
    juce::MemoryBlock sourceMusicMemoryBlock(BinaryData::At2SimpleAky_asm, BinaryData::At2SimpleAky_asmSize);
    const juce::MemoryBlock expectedBinaryMemoryBlock(BinaryData::At2SimpleAky_bin, BinaryData::At2SimpleAky_binSize);

    // When.
    const auto generatedSource = RasmHelper::assembleSource(sourceMusicMemoryBlock);

    // Then.
    REQUIRE(generatedSource != nullptr);
    REQUIRE(MemoryBlockUtil::compare(*generatedSource, expectedBinaryMemoryBlock));
}

TEST_CASE("Rasm, simple", "[Rasm]")
{
    const juce::String dataString(" ld b,7 : ld a,9 : nop \r\n nop");
    const auto dataIn = dataString.toRawUTF8();
    const auto dataInLength = dataString.length();

    // Creates a pointer of pointer. Rasm will make it point to a new buffer.
    unsigned char* dataOutPt = nullptr;

    auto lengthOut = 0;
    const auto result = RasmAssemble(dataIn, dataInLength, &dataOutPt, &lengthOut);

    // Checks the result.
    REQUIRE(result == 0);
    REQUIRE(dataOutPt != nullptr);
    REQUIRE(lengthOut == 6);
    constexpr unsigned char rightResult[] = { 6, 7, 0x3eU, 9, 0, 0 };
    compare(dataOutPt, static_cast<const unsigned char*>(rightResult), lengthOut);

    free(dataOutPt);
}

TEST_CASE("Rasm, simple out structure", "[Rasm]")
{
    juce::String dataString(" org #1000 \r\nlabel1 ld b,7 : ld a,9 : nop \r\n nop");
    auto dataIn = dataString.toRawUTF8();
    const auto dataInLength = dataString.length();

    // Creates a pointer of pointer. Rasm will make it point to a new buffer.
    unsigned char* dataOutPt = nullptr;
    s_rasm_info* rasmInfoPt = nullptr;

    auto lengthOut = 0;
    auto result = RasmAssembleInfo(dataIn, dataInLength, &dataOutPt, &lengthOut, &rasmInfoPt);

    // Checks the result.
    REQUIRE(result == 0);
    REQUIRE(dataOutPt != nullptr);
    REQUIRE(lengthOut == 6);
    unsigned char rightResult[] = { 6, 7, 0x3eU, 9, 0, 0 };
    compare(dataOutPt, static_cast<const unsigned char*>(rightResult), lengthOut);

    // Reads the "out".
    REQUIRE(rasmInfoPt != nullptr);
    REQUIRE(rasmInfoPt->nberror == 0);
    REQUIRE(rasmInfoPt->nbsymbol == 3);     // SYNCHRO and RASM_VERSION added.
    REQUIRE(rasmInfoPt->symbol != nullptr);
    REQUIRE(rasmInfoPt->symbol[0].v == 0x1000);
    REQUIRE(strncmp(rasmInfoPt->symbol[0].name, "LABEL1", 6) == 0);

    free(dataOutPt);
    RasmFreeInfoStruct(rasmInfoPt);
}

TEST_CASE("Rasm, undef", "[Rasm]")
{
    const auto dataIn = BinaryData::RasmUndef_asm;

    // Creates a pointer of pointer. Rasm will make it point to a new buffer.
    unsigned char* dataOutPt = nullptr;

    auto lengthOut = 0;
    const auto result = RasmAssemble(dataIn, BinaryData::RasmUndef_asmSize, &dataOutPt, &lengthOut);

    // Checks the result.
    REQUIRE(result == 0);
    REQUIRE(dataOutPt != nullptr);
    REQUIRE(lengthOut == 4);

    constexpr unsigned char rightResult[] = { 0x3eU, 5, 0x3eU, 6 };
    compare(dataOutPt, static_cast<const unsigned char*>(rightResult), lengthOut);

    free(dataOutPt);
}

TEST_CASE("Rasm, limit exceeded", "[Rasm]")
{
    juce::MemoryBlock memoryBlock(BinaryData::RasmAkyDiaEndInput_asm, BinaryData::RasmAkyDiaEndInput_asmSize);

    // Inserts an "org #ffff" at the beginning.
    const juce::String dataString(" org #ffff");
    const auto dataIn = dataString.toRawUTF8();
    const auto dataInLength = static_cast<size_t>(dataString.length());

    memoryBlock.insert(dataIn, dataInLength, 0);

    // Creates a pointer of pointer. Rasm will make it point to a new buffer.
    unsigned char* dataOutPt = nullptr;

    auto lengthOut = 0;
    const auto result = RasmAssemble(static_cast<const char*>(memoryBlock.getData()), static_cast<int>(memoryBlock.getSize()), &dataOutPt, &lengthOut);

    // Checks the result. It must have failed (yet the recovery must be OK)!
    REQUIRE(result != 0);
    REQUIRE(dataOutPt == nullptr);
}

TEST_CASE("Rasm, long aky", "[Rasm]")
{
    // Creates a pointer of pointer. Rasm will make it point to a new buffer.
    unsigned char* dataOutPt = nullptr;
    s_rasm_info* rasmInfoPt = nullptr;

    auto lengthOut = 0;
    const auto result = RasmAssembleInfo(BinaryData::RasmAkyDiaEndInput_asm, BinaryData::RasmAkyDiaEndInput_asmSize, &dataOutPt, &lengthOut, &rasmInfoPt);

    REQUIRE(result == 0);
    REQUIRE(dataOutPt != nullptr);
    REQUIRE(lengthOut == BinaryData::RasmAkyDiaEndResult_binSize);

    // Compares each byte.
    compare(dataOutPt, reinterpret_cast<const unsigned char*>(BinaryData::RasmAkyDiaEndResult_bin), lengthOut);

    free(dataOutPt);
    RasmFreeInfoStruct(rasmInfoPt);
}

TEST_CASE("Rasm, binary export", "[Rasm]")
{
    const auto dataIn = BinaryData::BinarySongShortXmlInput_asm;

    // Creates a pointer of pointer. Rasm will make it point to a new buffer.
    unsigned char* dataOutPt = nullptr;

    auto lengthOut = 0;
    const auto result = RasmAssemble(dataIn, BinaryData::BinarySongShortXmlInput_asmSize, &dataOutPt, &lengthOut);

    REQUIRE(result == 0);
    REQUIRE(dataOutPt != nullptr);
    REQUIRE(lengthOut == BinaryData::BinarySongShortXmlResult_binSize);

    // Compares each byte.
    compare(dataOutPt, reinterpret_cast<const unsigned char*>(BinaryData::BinarySongShortXmlResult_bin), lengthOut);

    free(dataOutPt);
}

TEST_CASE("Rasm, AKG player", "[Rasm]")
{
    // Assembles the Player from the source.
    juce::MemoryBlock sourceMemoryBlock(BinaryData::PlayerAkg_asm, BinaryData::PlayerAkg_asmSize);
    assembleSourceFromMemoryBlock(sourceMemoryBlock, true);
}

TEST_CASE("Rasm, AKY player", "[Rasm]")
{
    // Assembles the Player from the source.
    juce::MemoryBlock sourceMemoryBlock(BinaryData::PlayerAky_asm, BinaryData::PlayerAky_asmSize);
    assembleSourceFromMemoryBlock(sourceMemoryBlock, true);
}

TEST_CASE("Rasm, repeat start", "[Rasm]")
{
    const juce::String dataString(" REPEAT 3, stuff, 2 \r\n ld a,stuff \r\n REND");
    const auto dataIn = dataString.toRawUTF8();
    const auto dataInLength = dataString.length();

    // Creates a pointer of pointer. Rasm will make it point to a new buffer.
    unsigned char* dataOutPt = nullptr;

    auto lengthOut = 0;
    const auto result = RasmAssemble(dataIn, dataInLength, &dataOutPt, &lengthOut);

    // Checks the result.
    REQUIRE(result == 0);
    REQUIRE(dataOutPt != nullptr);
    REQUIRE(lengthOut == 6);
    constexpr unsigned char rightResult[] = { 0x3eU, 2, 0x3eU, 3, 0x3eU, 4 };
    compare(dataOutPt, rightResult, lengthOut);

    free(dataOutPt);
}

TEST_CASE("Rasm, repeat start default", "[Rasm]")
{
    const juce::String dataString(" REPEAT 3, stuff \r\n ld a,stuff \r\n REND");
    const auto dataIn = dataString.toRawUTF8();
    const auto dataInLength = dataString.length();

    // Creates a pointer of pointer. Rasm will make it point to a new buffer.
    unsigned char* dataOutPt = nullptr;

    auto lengthOut = 0;
    const auto result = RasmAssemble(dataIn, dataInLength, &dataOutPt, &lengthOut);

    // Checks the result.
    REQUIRE(result == 0);
    REQUIRE(dataOutPt != nullptr);
    REQUIRE(lengthOut == 6);
    constexpr unsigned char rightResult[] = { 0x3eU, 1, 0x3eU, 2, 0x3eU, 3 };
    compare(dataOutPt, rightResult, lengthOut);

    free(dataOutPt);
}

TEST_CASE("Rasm, buildSna", "[Rasm]")
{
    const auto tempFile = juce::File::createTempFile("sna");
    const auto& tempFilePath = tempFile.getFullPathName();
    //DBG("Path " + tempFilePath);

    const auto dataString(
                                  " buildsna force, '" + tempFilePath + "' \r\n"
                                  " bankset 0 \r\n"
                                  " org #1000 \r\n"
                                  " run $ \r\n"
                                  " di \r\n"
                                  " ld bc,#7f10 \r\n"
                                  " out (c),c \r\n"
                                  " ld a,#4b \r\n"
                                  " out (c),a \r\n"
                                  " jr $ \r\n"
                                  );
    const auto dataIn = dataString.toRawUTF8();
    const auto dataInLength = dataString.length();

    // Creates a pointer of pointer. Rasm will make it point to a new buffer.
    unsigned char* dataOutPt = nullptr;

    auto lengthOut = 0;
    const auto result = RasmAssemble(dataIn, dataInLength, &dataOutPt, &lengthOut);

    // Checks the result.
    REQUIRE((result == 0));
    REQUIRE((dataOutPt == nullptr));        // Because SNA, nothing is produced.

    (void)tempFile.deleteFile();
}

TEST_CASE("Rasm, generate DSK", "[Rasm]")
{
    const auto tempDskFileDsk = juce::File::createTempFile("dsk");
    const auto& tempDskFilePath = tempDskFileDsk.getFullPathName();

    const auto dataString(
          " EDSK create, '" + tempDskFilePath + "', data, 41, interlaced, overwrite \r\n"
                      " org 32768 \r\n"
                      " run $ \r\n"
                      " di \r\n"
                      " ld bc,#7f10 \r\n"
                      " out (c),c \r\n"
                      " ld a,#4c \r\n"
                      " out (c),a \r\n"
                      " jr $ \r\n"
          " EDSK savefile, '" + tempDskFilePath + "', '" + "file1.bin" + "', 32768, 12 \r\n"
                          " org 40000 \r\n"
                       " run $ \r\n"
                       " di \r\n"
                       " ld bc,#7f10 \r\n"
                       " out (c),c \r\n"
                       " ld a,#4b \r\n"
                       " out (c),a \r\n"
                       " jr $ \r\n"
          " EDSK savefile, '" + tempDskFilePath + "', '" + "file2.bin" + "', 40000, 12 \r\n"
          );
    const auto* dataIn = dataString.toRawUTF8();
    const auto dataInLength = dataString.length();

    // Creates a pointer of pointer. Rasm will make it point to a new buffer.
    unsigned char* dataOutPt = nullptr;

    auto lengthOut = 0;
    const auto result = RasmAssemble(dataIn, dataInLength, &dataOutPt, &lengthOut);

    // Checks the result.
    REQUIRE((result == 0));
    REQUIRE((dataOutPt != nullptr));

    REQUIRE((tempDskFileDsk.getSize() > static_cast<juce::int64>(190 * 1024)));

    (void)tempDskFileDsk.deleteFile();
}

TEST_CASE("Rasm, generate DSK with Basic", "[Rasm]")
{
    const auto tempDskFileDsk = juce::File::createTempFile("dsk");
    const auto& tempDskFilePath = tempDskFileDsk.getFullPathName();

    // Saves the basic with header file into temp.
    const juce::MemoryBlock basicFileMemoryBlock(BinaryData::testhead_bas, BinaryData::testhead_basSize);
    const auto tempBasicFile = juce::File::createTempFile("bas");
    FileUtil::saveMemoryBlockToFile(tempBasicFile, basicFileMemoryBlock);
    const auto& tempBasicFilePath = tempBasicFile.getFullPathName();

    const auto dataString(
          " EDSK create, '" + tempDskFilePath + "', data, 41, interlaced, overwrite \r\n"
          " EDSK putfile, '" + tempDskFilePath + "', '" + tempBasicFilePath + "', 'test.bas' \r\n"
          );
    const auto* dataIn = dataString.toRawUTF8();
    const auto dataInLength = dataString.length();

    // Creates a pointer of pointer. Rasm will make it point to a new buffer.
    unsigned char* dataOutPt = nullptr;

    auto lengthOut = 0;
    const auto result = RasmAssemble(dataIn, dataInLength, &dataOutPt, &lengthOut);

    // Checks the result.
    REQUIRE((result == 0));
    REQUIRE((dataOutPt == nullptr));

    REQUIRE((tempDskFileDsk.getSize() > static_cast<juce::int64>(190 * 1024)));

    (void)tempDskFileDsk.deleteFile();
    (void)tempBasicFile.deleteFile();
}

TEST_CASE("Rasm, generate DSK with Binary with header", "[Rasm]")
{
    const auto tempDskFileDsk = juce::File::createTempFile("dsk");
    const auto& tempDskFilePath = tempDskFileDsk.getFullPathName();

    // Saves binary data into a file, without header.
    const auto binaryData = MemoryBlockUtil::fromVector({ 0, 1, 2, 3, 255 });
    const auto tempBinaryFile = juce::File::createTempFile("bin");
    FileUtil::saveMemoryBlockToFile(tempBinaryFile, binaryData);
    const auto& tempBinaryFilePath = tempBinaryFile.getFullPathName();

    {
        const auto dataString(
              " EDSK create, '" + tempDskFilePath + "', data, 41, interlaced, overwrite \r\n"
              " EDSK putfile, '" + tempDskFilePath + "', '" + tempBinaryFilePath + "', 'test.bin', AMSDOS, BINARY, LOAD=0x1000, EXEC=0x1000\r\n"
              );
        const auto* dataIn = dataString.toRawUTF8();
        const auto dataInLength = dataString.length();

        // Creates a pointer of pointer. Rasm will make it point to a new buffer.
        unsigned char* dataOutPt = nullptr;

        auto lengthOut = 0;
        const auto result = RasmAssemble(dataIn, dataInLength, &dataOutPt, &lengthOut);

        // Checks the result.
        REQUIRE((result == 0));
        REQUIRE((dataOutPt == nullptr));

        REQUIRE((tempDskFileDsk.getSize() > static_cast<juce::int64>(190 * 1024)));

        (void)tempBinaryFile.deleteFile();
    }

    {
        // Loads the file back from the DSK.
        const auto dataString(
              " EDSK getfile, '" + tempDskFilePath + "', 'test.bin', '" + tempBinaryFilePath + "', NOHEADER\r\n"
              );
        const auto* dataIn = dataString.toRawUTF8();
        const auto dataInLength = dataString.length();

        // Creates a pointer of pointer. Rasm will make it point to a new buffer.
        unsigned char* dataOutPt = nullptr;

        auto lengthOut = 0;
        const auto result = RasmAssemble(dataIn, dataInLength, &dataOutPt, &lengthOut);

        (void)tempDskFileDsk.deleteFile();

        // Checks the result.
        REQUIRE((result == 0));
        REQUIRE((dataOutPt == nullptr));
    }

    // Is the file the same?
    const auto readBinaryData = MemoryBlockUtil::fromFile(tempBinaryFile);
    REQUIRE((readBinaryData != nullptr));
    REQUIRE((*readBinaryData == binaryData));
}

}   // namespace arkostracker
