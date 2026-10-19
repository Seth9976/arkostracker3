#include "catch.hpp"

#include <BinaryData.h>

#include "../sources/Disassembler.h"
#include "../sources/base/AreaTag.h"
#include "../sources/base/ExportConfiguration.h"
#include "utils/DisassemblerTest.h"
#include "utils/MemoryBlockUtil.h"
#include "utils/PlayerType.h"
#include "utils/RasmHelper.h"
#include "utils/TargetHardware.h"

namespace disark
{

// Utility methods.
// ==================================================

static void testUndocumentedInstructionUseBytesSpecific(const std::vector<unsigned char>& inputBytes)
{
    auto inputBytesMemoryBlock = MemoryBlockUtil::fromVector(inputBytes);
    juce::MemoryInputStream inputBytesInputStream(inputBytesMemoryBlock, true);

    // Disarks its bytes, but as we use undocumented opcodes, we retrieve bytes.
    ExportConfiguration exportConfiguration;
    exportConfiguration.setUndocumentedOpcodesAsBytes(true);
    exportConfiguration.setEncode8BitNumberAsHex(false);
    exportConfiguration.setEncode16BitNumberAsHex(false);
    Disassembler disassembler(exportConfiguration);
    juce::MemoryOutputStream disarkSourceOutputStream;
    auto errorStrings = disassembler.disassemble(inputBytesInputStream, disarkSourceOutputStream);
    REQUIRE(errorStrings.empty());

    auto disarkSourceMemoryBlock = disarkSourceOutputStream.getMemoryBlock();

    // Now makes sure that the Disark output is ONLY DBs! Not the real instruction. And makes sure the DBs are right of course.
    const auto disarkedStrings = MemoryBlockUtil::extractStrings(disarkSourceMemoryBlock);

    REQUIRE((disarkedStrings.size() == inputBytes.size()));   // As much "DB x" as there are bytes in the instruction.
    size_t index = 0U;
    for (auto b : inputBytes) {
        const auto& disarkString = disarkedStrings[index];
        const auto expectedString = "    db " + juce::String(b);
        REQUIRE((disarkString == expectedString));
        ++index;
    }
}


static std::vector<juce::String> compileAndDisark(const ExportConfiguration& exportConfiguration, const std::vector<juce::String>& sourceStrings)
{
    // Gathers the source lines into a MemoryBlock, compiles it.
    auto originalSourceMemoryBlock = MemoryBlockUtil::fromStrings(sourceStrings);

    RasmHelper rasmHelper;
    std::vector<Symbol> symbolsToFill;
    const auto binary = rasmHelper.assembleSource(originalSourceMemoryBlock, -1, &symbolsToFill);
    REQUIRE((binary != nullptr));

    // Disarks the binary.
    juce::MemoryInputStream inputStream(*binary, false);
    juce::MemoryOutputStream outputStream;
    Disassembler disassembler(exportConfiguration);
    disassembler.addSymbols(symbolsToFill);
    const auto errors = disassembler.disassemble(inputStream, outputStream);
    REQUIRE(errors.empty());

    return MemoryBlockUtil::extractStrings(outputStream.getMemoryBlock());
}




static void testUndocumentedInstructionAsBytes(const juce::String& lineToAssemble)
{
    // Assembles the line with Rasm.
    auto memoryBlockToAssemble = MemoryBlockUtil::fromString(lineToAssemble);

    // Extracts its bytes.
    RasmHelper rasmHelper;
    auto rasmMemoryBlock = rasmHelper.assembleSource(memoryBlockToAssemble);
    REQUIRE((rasmMemoryBlock != nullptr));
    const auto rasmMemoryBlockList = MemoryBlockUtil::toVector(*rasmMemoryBlock);

    // Disarks its bytes, but as we use undocumented opcodes, we retrieve bytes.
    juce::MemoryInputStream rasmBinaryInputStream(*rasmMemoryBlock, true);
    juce::MemoryOutputStream disarkSourceOutputStream;

    ExportConfiguration exportConfiguration;
    exportConfiguration.setUndocumentedOpcodesAsBytes(true);
    exportConfiguration.setEncode8BitNumberAsHex(false);
    exportConfiguration.setEncode16BitNumberAsHex(false);
    Disassembler disassembler(exportConfiguration);
    auto errorStrings = disassembler.disassemble(rasmBinaryInputStream, disarkSourceOutputStream);
    REQUIRE(errorStrings.empty());

    auto disarkSourceMemoryBlock = disarkSourceOutputStream.getMemoryBlock();
    //auto disarkedMemoryBlockList = MemoryBlockUtil::toVector(*rasmMemoryBlock);     // For debug.

    // The bytes should be the same as the ones from Rasm.
    // Reassemble the Disarked source to get raw bytes.
    auto disarkedRasmMemoryBlock = rasmHelper.assembleSource(disarkSourceMemoryBlock);
    REQUIRE(rasmMemoryBlock != nullptr);

    REQUIRE(*disarkedRasmMemoryBlock == *rasmMemoryBlock);

    // Now makes sure that the Disark output is ONLY DBs! Not the real instruction. And makes sure the DBs are right of course.
    const auto disarkedStrings = MemoryBlockUtil::extractStrings(disarkSourceMemoryBlock);
    REQUIRE(disarkedStrings.size() == rasmMemoryBlockList.size());   // As much "DB x" as there are bytes in the instruction.
    size_t index = 0;
    for (auto b : rasmMemoryBlockList) {
        const auto& disarkString = disarkedStrings[index];
        auto expectedString = "    db " + juce::String(b);
        REQUIRE(disarkString == expectedString);
        ++index;
    }
}


static void compileAndCheckSource(const void* sourceData, size_t dataSize, int loadAddress)
{
    // Loads the original source in Rasm, compiles it. It gives a binary.
    juce::MemoryBlock originalSourceMemoryBlock(sourceData, dataSize);
    RasmHelper rasmHelper;
    auto binaryMemoryBlock = rasmHelper.assembleSource(originalSourceMemoryBlock, loadAddress);
    REQUIRE(binaryMemoryBlock != nullptr);

    // Now disassembles this binary with Disark.
    auto exportConfiguration = ExportConfiguration::buildWithCommentsAndGeneratedLabels();
    exportConfiguration.setGenerateOrg(true);
    Disassembler disassembler(exportConfiguration);
    disassembler.setStartAddress(loadAddress);

    juce::MemoryInputStream rasmBinaryInputStream(*binaryMemoryBlock, true);
    juce::MemoryOutputStream disarkSourceOutputStream;
    auto errorStrings = disassembler.disassemble(rasmBinaryInputStream, disarkSourceOutputStream);
    REQUIRE(errorStrings.empty());

    auto disarkSourceMemoryBlock = disarkSourceOutputStream.getMemoryBlock();

    // TEST
    //FileUtil::saveMemoryBlockToFile("/home/julien/Documents/localDev/test.asm", disarkSourceMemoryBlock);

    // All the instructions are known, yay.
    // Now assembles the source with Rasm, and compares the new binary with the first binary! They should be equal!
    auto secondBinaryMemoryBlock = rasmHelper.assembleSource(disarkSourceMemoryBlock);
    REQUIRE(secondBinaryMemoryBlock != nullptr);

    REQUIRE(*secondBinaryMemoryBlock == *binaryMemoryBlock);
}

static void compileAndCheckSource(const void* sourceData, size_t dataSize)
{
    compileAndCheckSource(sourceData, dataSize, 0);
    compileAndCheckSource(sourceData, dataSize, 0x1234);
    compileAndCheckSource(sourceData, dataSize, 0x4567);
}



static void validateDisarkedSourceAtLocation(const juce::MemoryBlock& originalSourceMemoryBlockWithoutOrgImmutable, int addressWhereToRecompile, PlayerType playerType,
                                      TargetHardware targetHardware, bool useRomPlayer, bool insertSoundEffectPlayer)
{
    DBG("--------------------------");
    DBG("TargetHardware: " + juce::String(static_cast<int>(targetHardware)));
    juce::String romString = (useRomPlayer ? "true" : "false");
    DBG("ROM? " + romString);
    juce::String soundEffectsString = (insertSoundEffectPlayer ? "true" : "false");
    DBG("Sound effects player? " + soundEffectsString);
    DBG("Location = " + juce::String(addressWhereToRecompile));

    jassert(addressWhereToRecompile < 0xf000);          // Don't go too high, it will collide with the ROM buffer address.

    RasmHelper rasmHelper;
    const auto romBufferAddress = 0xfa00;

    // Copies the original source, as it can not be modified. Needed to add the target hardware, and ROM flag is wanted.
    // Also removes the "include", as we will possibly add the sound effect player.
    auto originalSourceMemoryBlockWithoutOrg = rasmHelper.commentIncludes(originalSourceMemoryBlockWithoutOrgImmutable);
    auto sourceTagPrefix = rasmHelper.getSourceTagPrefix(playerType);
    rasmHelper.addRomPlayerDeclaration(originalSourceMemoryBlockWithoutOrg, sourceTagPrefix, romBufferAddress, useRomPlayer);
    rasmHelper.addHardwareDeclaration(originalSourceMemoryBlockWithoutOrg, sourceTagPrefix, targetHardware);

    if (insertSoundEffectPlayer) {
        // What sound effect player to plug?
        const char* playerCode;
        size_t playerSize;
        switch (playerType) {
            case PlayerType::Akg:
                playerCode = BinaryData::PlayerAkg_SoundEffects_asm;
                playerSize = BinaryData::PlayerAkg_SoundEffects_asmSize;
                break;
            case PlayerType::AkyMultiplePsgs:
                playerCode = BinaryData::PlayerAkyMultiPsg_SoundEffects_asm;
                playerSize = BinaryData::PlayerAkyMultiPsg_SoundEffects_asmSize;
                rasmHelper.addVariableDeclaration(originalSourceMemoryBlockWithoutOrg, "PLY_AKY_SFX_PSG_NUMBER");
                break;
            case PlayerType::Lightweight:
                playerCode = BinaryData::PlayerLightweight_SoundEffects_asm;
                playerSize = BinaryData::PlayerLightweight_SoundEffects_asmSize;
                break;
            case PlayerType::LightweightSharpMz700:
                playerCode = BinaryData::PlayerLightweight_SoundEffects_SHARPMZ700_asm;
                playerSize = BinaryData::PlayerLightweight_SoundEffects_SHARPMZ700_asmSize;
                break;
            case PlayerType::Akm:
                playerCode = BinaryData::PlayerAkm_SoundEffects_asm;
                playerSize = BinaryData::PlayerAkm_SoundEffects_asmSize;
                break;
            case PlayerType::Aky:
            case PlayerType::StandAloneSoundEffects:
            default:
                FAIL("This player has not SFX!");
                return;
        }
        // Puts the sound effect flag.
        rasmHelper.addVariableDeclaration(originalSourceMemoryBlockWithoutOrg, rasmHelper.getSourceTagPrefix(playerType) + "_MANAGE_SOUND_EFFECTS");
        // Appends the code of the sound effect player inside the main player.
        rasmHelper.insertAfterTag("[[INSERT_SOUND_EFFECT_SOURCE]]", originalSourceMemoryBlockWithoutOrg, juce::MemoryBlock(playerCode, playerSize));
    }



    // Loads the original source in Rasm, without org, compiles it. It gives a binary. The labels are extracted.
    // --------------------------------------
    std::vector<Symbol> symbols;
    auto binaryFromOriginalSourceWithoutOrgMemoryBlock = rasmHelper.assembleSourceWithoutAddingOrg(originalSourceMemoryBlockWithoutOrg, &symbols);

    // Useful for testing
    //if (binaryFromOriginalSourceWithoutOrgMemoryBlock == nullptr) {
        //FileUtil::saveMemoryBlockToFile("/home/julien/Documents/dev/test/test1.asm", originalSourceMemoryBlockWithoutOrg);
    //}
    REQUIRE(binaryFromOriginalSourceWithoutOrgMemoryBlock != nullptr);

    // Disarks the binary.
    // ------------------------------
    auto exportConfiguration = ExportConfiguration::buildWithCommentsAndGeneratedLabels(true, false);       // For easy debugging.
    exportConfiguration.setGenerateOrg(false);
    Disassembler disassembler(exportConfiguration);
    disassembler.addSymbols(symbols);           // Injects all the Symbols.

    juce::MemoryInputStream rasmBinaryInputStream(*binaryFromOriginalSourceWithoutOrgMemoryBlock, true);
    juce::MemoryOutputStream disarkSourceOutputStream;
    auto errorStrings = disassembler.disassemble(rasmBinaryInputStream, disarkSourceOutputStream);
    REQUIRE(errorStrings.empty());
    auto disarkSourceMemoryBlock = disarkSourceOutputStream.getMemoryBlock();

    // Compiles the new Disarked Source, with an ORG.
    // ------------------------------
    auto binaryRedisarkedWithOrgMemoryBlock = rasmHelper.assembleSource(disarkSourceMemoryBlock, addressWhereToRecompile, nullptr);

    // Useful for testing
    //if (binaryRedisarkedWithOrgMemoryBlock == nullptr) {
        //FileUtil::saveMemoryBlockToFile("/home/julien/Documents/dev/test/test2.asm", disarkSourceMemoryBlock);
    //}
    REQUIRE(binaryRedisarkedWithOrgMemoryBlock != nullptr);

    // The Disarked source must be the same as the original source to which would be added an ORG.
    // ------------------------------------------------
    auto originalSourceMemoryBlockWithOrg = originalSourceMemoryBlockWithoutOrg;

    // Adds the Org to the original song, and compiles it.
    auto binaryOriginalSourceWithOrgMemoryBlock = rasmHelper.assembleSource(originalSourceMemoryBlockWithOrg, addressWhereToRecompile, nullptr);
    REQUIRE(binaryOriginalSourceWithOrgMemoryBlock != nullptr);


    // Compares both!
    // --------------------------------
    REQUIRE(MemoryBlockUtil::compare(*binaryRedisarkedWithOrgMemoryBlock, *binaryOriginalSourceWithOrgMemoryBlock));
}

static void validateDisarkedSource(const juce::MemoryBlock& originalSourceMemoryBlockWithoutOrg, bool checkMultiPlatform, PlayerType playerType, bool specialPlatform = false,
                            bool insertSoundEffectPlayer = false)
{
    // Browses all the platform and RAM/ROM, if wanted.
    std::vector<TargetHardware> targets;
    if (checkMultiPlatform) {
        if (specialPlatform) {
            targets = std::vector<TargetHardware>{ TargetHardware::cpcPlayCity, TargetHardware::spectrumNext, TargetHardware::spectrumTurboSound,
                                                   TargetHardware::msxDarky, TargetHardware::msxFpgaPsg };
        } else {
            targets = std::vector<TargetHardware>{ TargetHardware::cpc, TargetHardware::spectrum, TargetHardware::pentagon, TargetHardware::msx };
        }
    } else {
        targets = { TargetHardware::cpc };
    }
    for (const auto targetHardware : targets) {
        for (auto i = 0; i < (checkMultiPlatform ? 2 : 1); ++i) {
            const auto useRomPlayer = (i > 0);

            validateDisarkedSourceAtLocation(originalSourceMemoryBlockWithoutOrg, 0x0, playerType, targetHardware, useRomPlayer, insertSoundEffectPlayer);
            validateDisarkedSourceAtLocation(originalSourceMemoryBlockWithoutOrg, 0x1234, playerType, targetHardware, useRomPlayer, insertSoundEffectPlayer);
            validateDisarkedSourceAtLocation(originalSourceMemoryBlockWithoutOrg, 0x4567, playerType, targetHardware, useRomPlayer, insertSoundEffectPlayer);
        }
    }
}

// ==================================================







TEST_CASE("Disark, simple", "[Disark]")
{
    // Given.
    ExportConfiguration exportConfiguration;
    Disassembler disassembler(exportConfiguration);

    juce::MemoryOutputStream outputStream;

    // No region, no references.
    juce::MemoryBlock memoryBlock;
    const unsigned char dataIn[] = {
            0x01U, 0x40U, 0x50U,           // ld bc,&5040
            0x04U,                                // inc b
            0xddU, 0x09U                      // add ix,bc
    };
    memoryBlock.insert(dataIn, 6, 0);
    juce::MemoryInputStream inputStream(memoryBlock, false);

    // When.
    auto errorStrings = disassembler.disassemble(inputStream, outputStream);
    REQUIRE(errorStrings.empty());

    // Then.
    auto strings = MemoryBlockUtil::extractStrings(outputStream.getMemoryBlock());

    size_t index = 0;
    REQUIRE(strings.at(index++) == "    ld bc,#5040");
    REQUIRE(strings.at(index++) == "    inc b");
    REQUIRE(strings.at(index++) == "    add ix,bc");
    REQUIRE(strings.size() == index);
}

TEST_CASE("Disark, one reference", "[Disark]")
{
    ExportConfiguration exportConfiguration;
    Disassembler disassembler(exportConfiguration);
    disassembler.addSymbol({ "label1", 0x5040 });

    juce::MemoryOutputStream outputStream;

    // No region, no references.
    juce::MemoryBlock memoryBlock;
    const unsigned char dataIn[] = {
            0x04U,                       // inc b
            0x01U, 0x40U, 0x50U,           // ld bc,&5040
            0xddU, 0x09U                  // add ix,bc
    };
    memoryBlock.insert(dataIn, 6, 0);
    juce::MemoryInputStream inputStream(memoryBlock, false);

    auto errorStrings = disassembler.disassemble(inputStream, outputStream);
    REQUIRE(errorStrings.empty());

    // Checks.
    auto strings = MemoryBlockUtil::extractStrings(outputStream.getMemoryBlock());

    size_t index = 0;
    REQUIRE(strings.at(index++) == "    inc b");
    REQUIRE(strings.at(index++) == "    ld bc,label1");
    REQUIRE(strings.at(index++) == "    add ix,bc");
    REQUIRE(strings.at(index++) == "label1 equ #5040");      // Label 1 is generated because referenced.
    REQUIRE(strings.size() == index);
}

TEST_CASE("Disark, references and offsets", "[Disark]")
{
    ExportConfiguration exportConfiguration;
    Disassembler disassembler(exportConfiguration);
    disassembler.addSymbol({ "label1", 0x5040 });
    disassembler.addSymbol({ "label2", 0x4000 });
    disassembler.addSymbol({ "label3", 0x5000 });

    juce::MemoryOutputStream outputStream;

    // No region, no references.
    juce::MemoryBlock memoryBlock;
    const unsigned char dataIn[] = {
            0x01U, 0x02U, 0x40U,           // ld bc,&4002
            0x01U, 0x40U, 0x50U,           // ld bc,&5040
            0x01U, 0xffU, 0x4fU,           // ld bc,&4fff
            0xddU, 0x09U                  // add ix,bc
    };
    memoryBlock.insert(dataIn, 11, 0);
    juce::MemoryInputStream inputStream(memoryBlock, false);

    auto errorStrings = disassembler.disassemble(inputStream, outputStream);
    REQUIRE(errorStrings.empty());

    // Checks.
    auto strings = MemoryBlockUtil::extractStrings(outputStream.getMemoryBlock());

    size_t index = 0;
    REQUIRE(strings.at(index++) == "    ld bc,label2+2");
    REQUIRE(strings.at(index++) == "    ld bc,label1");
    REQUIRE(strings.at(index++) == "    ld bc,label3-1");
    REQUIRE(strings.at(index++) == "    add ix,bc");
    REQUIRE(strings.at(index++) == "label1 equ #5040");      // Labels are generated because referenced.
    REQUIRE(strings.at(index++) == "label2 equ #4000");
    REQUIRE(strings.at(index++) == "label3 equ #5000");
    REQUIRE(strings.size() == index);
}


TEST_CASE("Disark, references and offsets regions", "[Disark]")
{
    ExportConfiguration exportConfiguration;
    exportConfiguration.setGenerateOrg(true);
    Disassembler disassembler(exportConfiguration);
    disassembler.setStartAddress(0x1000);

    disassembler.addSymbol({ "label1", 0x5040 });
    disassembler.addSymbol({ "label2", 0x4000 });
    disassembler.addSymbol({ "label3", 0x5000 });

    disassembler.addRegion(Region {0x1000, 0x1004, RegionType::word});
    disassembler.addRegion(Region {0x1004, 0x1008, RegionType::pointers});

    juce::MemoryOutputStream outputStream;

    // No region, no references.
    juce::MemoryBlock memoryBlock;
    const unsigned char dataIn[] = {
            0x00U, 0x40U,           // &4000        (adr = #1000)
            0x02U, 0x40U,           // &4002        (adr = #1002)
            0x00U, 0x40U,           // &4002        (adr = #1004)
            0x03U, 0x40U,           // &4003        (adr = #1006)
    };
    memoryBlock.insert(dataIn, 4 * 2, 0);
    juce::MemoryInputStream inputStream(memoryBlock, false);

    auto errorStrings = disassembler.disassemble(inputStream, outputStream);
    REQUIRE(errorStrings.empty());

    // Checks.
    auto strings = MemoryBlockUtil::extractStrings(outputStream.getMemoryBlock());

    size_t index = 0;
    REQUIRE(strings.at(index++) == "    org #1000");
    REQUIRE(strings.at(index++) == "    dw #4000");              // Words: not inferred.
    REQUIRE(strings.at(index++) == "    dw #4002");
    REQUIRE(strings.at(index++) == "    dw label2");             // Pointers: labels inferred.
    REQUIRE(strings.at(index++) == "    dw label2+3");
    REQUIRE(strings.at(index++) == "label2 equ #4000");          // Labels are generated because referenced.
    REQUIRE(strings.size() == index);
}

TEST_CASE("Disark, one label", "[Disark]")
{
    ExportConfiguration exportConfiguration;
    exportConfiguration.setGenerateOrg(true);
    Disassembler disassembler(exportConfiguration);
    disassembler.setStartAddress(0x4000);
    disassembler.addSymbol({ "label1", 0x4002 });

    juce::MemoryOutputStream outputStream;

    // No region, no references.
    juce::MemoryBlock memoryBlock;
    const unsigned char dataIn[] = {
            0xddU, 0x09U,                 // add ix,bc
            0x01U, 0x02U, 0x40U,           // ld bc,&4002
            0x01U, 0x00U, 0x20U,           // ld bc,&2000
            0x01U, 0xfeU, 0x3fU,           // ld bc,&3ffe

    };
    memoryBlock.insert(dataIn, 11, 0);
    juce::MemoryInputStream inputStream(memoryBlock, false);

    auto errorStrings = disassembler.disassemble(inputStream, outputStream);
    REQUIRE(errorStrings.empty());

    // Checks.
    auto strings = MemoryBlockUtil::extractStrings(outputStream.getMemoryBlock());

    size_t index = 0;
    REQUIRE(strings.at(index++) == "    org #4000");
    REQUIRE(strings.at(index++) == "    add ix,bc");
    REQUIRE(strings.at(index++) == "label1 ld bc,label1");
    REQUIRE(strings.at(index++) == "    ld bc,#2000");
    REQUIRE(strings.at(index++) == "    ld bc,label1-4");
    REQUIRE(strings.size() == index);
}

TEST_CASE("Disark, multiple labels", "[Disark]")
{
    ExportConfiguration exportConfiguration;
    exportConfiguration.setGenerateOrg(true);
    Disassembler disassembler(exportConfiguration);
    disassembler.setStartAddress(0x4000);
    disassembler.addSymbol({ "label1a", 0x4000 });
    disassembler.addSymbol({ "label1b", 0x4000 });
    disassembler.addSymbol({ "label1c", 0x4000 });
    disassembler.addSymbol({ "label2", 0x4005 });
    disassembler.addSymbol({ "label3a", 0x4008 });
    disassembler.addSymbol({ "label3b", 0x4008 });
    disassembler.addSymbol({ "label3c", 0x4008 });
    disassembler.addSymbol({ "label3d", 0x4008 });

    juce::MemoryOutputStream outputStream;

    // No region, no references.
    juce::MemoryBlock memoryBlock;
    const unsigned char dataIn[] = {
            0xddU, 0x09U,                 // add ix,bc
            0x01U, 0x02U, 0x40U,           // ld bc,&4002
            0x01U, 0x00U, 0x20U,           // ld bc,&2000
            0x01U, 0xfeU, 0x3fU,           // ld bc,&3ffe
            0x01U, 0x00U, 0x40U,           // ld bc,&4000

    };
    memoryBlock.insert(dataIn, 14, 0);
    juce::MemoryInputStream inputStream(memoryBlock, false);

    auto errorStrings = disassembler.disassemble(inputStream, outputStream);
    REQUIRE(errorStrings.empty());

    // Checks.
    auto strings = MemoryBlockUtil::extractStrings(outputStream.getMemoryBlock());

    size_t index = 0;
    REQUIRE(strings.at(index++) == "    org #4000");
    REQUIRE(strings.at(index++) == "label1a");
    REQUIRE(strings.at(index++) == "label1b");
    REQUIRE(strings.at(index++) == "label1c add ix,bc");
    REQUIRE(strings.at(index++) == "    ld bc,label1a+2");
    REQUIRE(strings.at(index++) == "label2 ld bc,#2000");
    REQUIRE(strings.at(index++) == "label3a");
    REQUIRE(strings.at(index++) == "label3b");
    REQUIRE(strings.at(index++) == "label3c");
    REQUIRE(strings.at(index++) == "label3d ld bc,label1a-2");
    REQUIRE(strings.at(index++) == "    ld bc,label1a");
    REQUIRE(strings.size() == index);
}

TEST_CASE("Disark, past labels", "[Disark]")
{
    ExportConfiguration exportConfiguration;
    exportConfiguration.setGenerateOrg(true);
    Disassembler disassembler(exportConfiguration);
    disassembler.setStartAddress(0x4000);
    disassembler.addSymbol({ "label1", 0x4001 });
    disassembler.addSymbol({ "label2", 0x4002 });

    juce::MemoryOutputStream outputStream;

    // No region, no references.
    juce::MemoryBlock memoryBlock;
    const unsigned char dataIn[] = {
            0x01U, 0xeeU, 0xffU,           // ld bc,&ffee
    };
    memoryBlock.insert(dataIn, 3, 0);
    juce::MemoryInputStream inputStream(memoryBlock, false);

    auto errorStrings = disassembler.disassemble(inputStream, outputStream);
    REQUIRE(errorStrings.empty());

    // Checks.
    auto strings = MemoryBlockUtil::extractStrings(outputStream.getMemoryBlock());
    size_t index = 0;
    REQUIRE(strings.at(index++) == "    org #4000");
    REQUIRE(strings.at(index++) == "label1 equ $+1");
    REQUIRE(strings.at(index++) == "label2 equ $+2");
    REQUIRE(strings.at(index++) == "    ld bc,#ffee");
    REQUIRE(strings.size() == index);
}

TEST_CASE("Disark, best reference", "[Disark]")
{
    ExportConfiguration exportConfiguration;
    exportConfiguration.setGenerateOrg(true);
    Disassembler disassembler(exportConfiguration);
    disassembler.setStartAddress(0x4000);
    disassembler.addSymbol({ "label1", 0x4000 });
    disassembler.addSymbol({ "label2", 0x4003 });

    juce::MemoryOutputStream outputStream;

    juce::MemoryBlock memoryBlock;
    const unsigned char dataIn[] = {
            0x01U, 0x01U, 0x00U,           // ld bc,#0001
            0x01U, 0x02U, 0x00U,           // ld bc,#0002
            0x01U, 0x03U, 0x00U,           // ld bc,#0003
            0x01U, 0x04U, 0x00U,           // ld bc,#0004
            0x01U, 0x01U, 0x40U,           // ld bc,#4001
            0x01U, 0x02U, 0x40U,           // ld bc,#4002
    };
    memoryBlock.insert(dataIn, 6 * 3, 0);
    juce::MemoryInputStream inputStream(memoryBlock, false);

    auto errorStrings = disassembler.disassemble(inputStream, outputStream);
    REQUIRE(errorStrings.empty());

    // Checks.
    // Label1 is chosen over label2 because +1/+2 has more priority on -1 -2.
    auto strings = MemoryBlockUtil::extractStrings(outputStream.getMemoryBlock());
    size_t index = 0;
    REQUIRE(strings.at(index++) == "    org #4000");
    REQUIRE(strings.at(index++) == "label1 ld bc,#1");
    REQUIRE(strings.at(index++) == "label2 ld bc,#2");
    REQUIRE(strings.at(index++) == "    ld bc,#3");
    REQUIRE(strings.at(index++) == "    ld bc,#4");
    REQUIRE(strings.at(index++) == "    ld bc,label1+1");
    REQUIRE(strings.at(index++) == "    ld bc,label1+2");
    REQUIRE(strings.size() == index);
}

TEST_CASE("Disark, relative jumps", "[Disark]")
{
    ExportConfiguration exportConfiguration;
    exportConfiguration.setGenerateOrg(true);
    Disassembler disassembler(exportConfiguration);
    disassembler.setStartAddress(0x4000);

    juce::MemoryOutputStream outputStream;

    juce::MemoryBlock memoryBlock;
    const unsigned char dataIn[] = {
            0x18U, 0x7fU,                 // jr $ + 129
            0x18U, 0x01U,                 // jr $ + 3
            0x18U, 0x00U,                 // jr $ + 2
            0x18U, 0xffU,                 // jr $ + 1

            0x18U, 0xfeU,                 // jr $
            0x18U, 0xfdU,                 // jr $ - 1
            0x18U, 0xfcU,                 // jr $ - 2
            0x18U, 0x80U,                 // jr $ - 128
    };
    memoryBlock.insert(dataIn, 8 * 2, 0);
    juce::MemoryInputStream inputStream(memoryBlock, false);

    auto errorStrings = disassembler.disassemble(inputStream, outputStream);
    REQUIRE(errorStrings.empty());

    // Checks.
    auto strings = MemoryBlockUtil::extractStrings(outputStream.getMemoryBlock());
    size_t index = 0;
    REQUIRE(strings.at(index++) == "    org #4000");
    REQUIRE(strings.at(index++) == "    jr $+129");
    REQUIRE(strings.at(index++) == "    jr $+3");
    REQUIRE(strings.at(index++) == "    jr $+2");
    REQUIRE(strings.at(index++) == "    jr $+1");
    REQUIRE(strings.at(index++) == "    jr $");
    REQUIRE(strings.at(index++) == "    jr $-1");
    REQUIRE(strings.at(index++) == "    jr $-2");
    REQUIRE(strings.at(index++) == "    jr $-126");
    REQUIRE(strings.size() == index);
}

TEST_CASE("Disark, signed indexes", "[Disark]")
{
    ExportConfiguration exportConfiguration;
    exportConfiguration.setGenerateOrg(true);
    Disassembler disassembler(exportConfiguration);
    disassembler.setStartAddress(0x4000);

    juce::MemoryOutputStream outputStream;

    juce::MemoryBlock memoryBlock;
    const unsigned char dataIn[] = {
            0xddU, 0x36U, 0x0U, 0x40U,               // ld (ix+0),#40
            0xddU, 0x36U, 0x1U, 0x40U,               // ld (ix+1),#40
            0xddU, 0x36U, 0x2U, 0x40U,               // ld (ix+2),#40
            0xddU, 0x36U, 0x20U, 0x40U,              // ld (ix+32),#40
            0xddU, 0x36U, 0x70U, 0x40U,              // ld (ix+111),#40
            0xddU, 0x36U, 0x7fU, 0x40U,              // ld (ix+127),#40

            0xddU, 0x36U, 0xffU, 0x00U,              // ld (ix-1),#00
            0xddU, 0x36U, 0xfeU, 0x10U,              // ld (ix-2),#10
            0xddU, 0x36U, 0xe0U, 0x30U,              // ld (ix-32),#30
            0xddU, 0x36U, 0x90U, 0x50U,              // ld (ix-112),#50
            0xddU, 0x36U, 0x80U, 0xffU,              // ld (ix-128),#ff
    };
    memoryBlock.insert(dataIn, 11 * 4, 0);
    juce::MemoryInputStream inputStream(memoryBlock, false);

    auto errorStrings = disassembler.disassemble(inputStream, outputStream);
    REQUIRE(errorStrings.empty());

    // Checks.
    auto strings = MemoryBlockUtil::extractStrings(outputStream.getMemoryBlock());
    size_t index = 0;
    REQUIRE(strings.at(index++) == "    org #4000");
    REQUIRE(strings.at(index++) == "    ld (ix+0),#40");
    REQUIRE(strings.at(index++) == "    ld (ix+1),#40");
    REQUIRE(strings.at(index++) == "    ld (ix+2),#40");
    REQUIRE(strings.at(index++) == "    ld (ix+32),#40");
    REQUIRE(strings.at(index++) == "    ld (ix+112),#40");
    REQUIRE(strings.at(index++) == "    ld (ix+127),#40");

    REQUIRE(strings.at(index++) == "    ld (ix-1),#0");
    REQUIRE(strings.at(index++) == "    ld (ix-2),#10");
    REQUIRE(strings.at(index++) == "    ld (ix-32),#30");
    REQUIRE(strings.at(index++) == "    ld (ix-112),#50");
    REQUIRE(strings.at(index++) == "    ld (ix-128),#ff");
    REQUIRE(strings.size() == index);
}

TEST_CASE("Disark, undocumentedInstruction", "[Disark]")
{
    ExportConfiguration exportConfiguration;
    Disassembler disassembler(exportConfiguration);

    juce::MemoryOutputStream outputStream;

    // No region, no references.
    juce::MemoryBlock memoryBlock;
    const unsigned char dataIn[] = {
            0xedU, 0x71U,                 // out (c),0
            0xddU, 0xcbU, 0x00U, 0x10U      // rl (ix+0),b
    };
    memoryBlock.insert(dataIn, 6, 0);
    juce::MemoryInputStream inputStream(memoryBlock, false);

    auto errorStrings = disassembler.disassemble(inputStream, outputStream);
    REQUIRE(errorStrings.empty());

    // Checks.
    auto strings = MemoryBlockUtil::extractStrings(outputStream.getMemoryBlock());

    size_t index = 0;
    REQUIRE(strings.at(index++) == "    out (c),0");
    REQUIRE(strings.at(index++) == "    rl (ix+0),b");
    REQUIRE(strings.size() == index);
}

TEST_CASE("Disark, undocumented instruction use bytes specific", "[Disark]")
{
    // These instructions have a "normal" opcode too, so only the undocumented ones must be tested.
    const std::vector<std::vector<unsigned char>> opcodesArray = {
            // NEG.
            { 0xedU, 0x64U },
            { 0xedU, 0x4cU },
            { 0xedU, 0x6cU },
            { 0xedU, 0x54U },
            { 0xedU, 0x74U },
            { 0xedU, 0x5cU },
            { 0xedU, 0x7cU },

            // RETN.
            { 0xedU, 0x65U },
            { 0xedU, 0x6dU },
            { 0xedU, 0x55U },
            { 0xedU, 0x75U },
            { 0xedU, 0x5dU },
            { 0xedU, 0x7dU },

            // IM 0.
            { 0xedU, 0x66U },
            { 0xedU, 0x4eU },
            { 0xedU, 0x6eU },

            // IM 1.
            { 0xedU, 0x76U },

            // IM 2.
            { 0xedU, 0x7eU },

            // BIT 0,(IX +d).
            { 0xddU, 0xcbU, 0U, 0x40U },
            { 0xddU, 0xcbU, 255U, 0x41U },
            { 0xddU, 0xcbU, 127U, 0x42U },
            { 0xddU, 0xcbU, 32U, 0x43U },
            { 0xddU, 0xcbU, 1U, 0x44U },
            { 0xddU, 0xcbU, 79U, 0x45U },
            //0x46 is the normal instruction, so not put here.
            { 0xddU, 0xcbU, 232U, 0x47U },

            // BIT 1,(IX +d).
            { 0xddU, 0xcbU, 0U, 0x48U },
            { 0xddU, 0xcbU, 255U, 0x49U },
            { 0xddU, 0xcbU, 127U, 0x4aU },
            { 0xddU, 0xcbU, 32U, 0x4bU },
            { 0xddU, 0xcbU, 1U, 0x4cU },
            { 0xddU, 0xcbU, 79U, 0x4dU },
            //0x4e is the normal instruction, so not put here.
            { 0xddU, 0xcbU, 232U, 0x4fU },

            // BIT 2,(IX +d).
            { 0xddU, 0xcbU, 0U, 0x50U },
            { 0xddU, 0xcbU, 255U, 0x51U },
            { 0xddU, 0xcbU, 127U, 0x52U },
            { 0xddU, 0xcbU, 32U, 0x53U },
            { 0xddU, 0xcbU, 1U, 0x54U },
            { 0xddU, 0xcbU, 79U, 0x55U },
            //0x56 is the normal instruction, so not put here.
            { 0xddU, 0xcbU, 232U, 0x57U },

            // BIT 3,(IX +d).
            { 0xddU, 0xcbU, 0U, 0x58U },
            { 0xddU, 0xcbU, 255U, 0x59U },
            { 0xddU, 0xcbU, 127U, 0x5aU },
            { 0xddU, 0xcbU, 32U, 0x5bU },
            { 0xddU, 0xcbU, 1U, 0x5cU },
            { 0xddU, 0xcbU, 79U, 0x5dU },
            //0x5e is the normal instruction, so not put here.
            { 0xddU, 0xcbU, 232U, 0x5fU },

            // BIT 4,(IX +d).
            { 0xddU, 0xcbU, 0U, 0x60U },
            { 0xddU, 0xcbU, 255U, 0x61U },
            { 0xddU, 0xcbU, 127U, 0x62U },
            { 0xddU, 0xcbU, 32U, 0x63U },
            { 0xddU, 0xcbU, 1U, 0x64U },
            { 0xddU, 0xcbU, 79U, 0x65U },
            //0x66 is the normal instruction, so not put here.
            { 0xddU, 0xcbU, 232U, 0x67U },

            // BIT 5,(IX +d).
            { 0xddU, 0xcbU, 0U, 0x68U },
            { 0xddU, 0xcbU, 255U, 0x69U },
            { 0xddU, 0xcbU, 127U, 0x6aU },
            { 0xddU, 0xcbU, 32U, 0x6bU },
            { 0xddU, 0xcbU, 1U, 0x6cU },
            { 0xddU, 0xcbU, 79U, 0x6dU },
            //0x6e is the normal instruction, so not put here.
            { 0xddU, 0xcbU, 232U, 0x6fU },

            // BIT 6,(IX +d).
            { 0xddU, 0xcbU, 0U, 0x70U },
            { 0xddU, 0xcbU, 255U, 0x71U },
            { 0xddU, 0xcbU, 127U, 0x72U },
            { 0xddU, 0xcbU, 32U, 0x73U },
            { 0xddU, 0xcbU, 1U, 0x74U },
            { 0xddU, 0xcbU, 79U, 0x75U },
            //0x76 is the normal instruction, so not put here.
            { 0xddU, 0xcbU, 232U, 0x77U },

            // BIT 7,(IX +d).
            { 0xddU, 0xcbU, 0U, 0x78U },
            { 0xddU, 0xcbU, 255U, 0x79U },
            { 0xddU, 0xcbU, 127U, 0x7aU },
            { 0xddU, 0xcbU, 32U, 0x7bU },
            { 0xddU, 0xcbU, 1U, 0x7cU },
            { 0xddU, 0xcbU, 79U, 0x7dU },
            //0x7e is the normal instruction, so not put here.
            { 0xddU, 0xcbU, 232U, 0x7fU },



            // BIT 0,(IY +d).
            { 0xfdU, 0xcbU, 0U, 0x40U },
            { 0xfdU, 0xcbU, 255U, 0x41U },
            { 0xfdU, 0xcbU, 127U, 0x42U },
            { 0xfdU, 0xcbU, 32U, 0x43U },
            { 0xfdU, 0xcbU, 1U, 0x44U },
            { 0xfdU, 0xcbU, 79U, 0x45U },
            //0x46 is the normal instruction, so not put here.
            { 0xfdU, 0xcbU, 232U, 0x47U },

            // BIT 1,(IY +d).
            { 0xfdU, 0xcbU, 0U, 0x48U },
            { 0xfdU, 0xcbU, 255U, 0x49U },
            { 0xfdU, 0xcbU, 127U, 0x4aU },
            { 0xfdU, 0xcbU, 32U, 0x4bU },
            { 0xfdU, 0xcbU, 1U, 0x4cU },
            { 0xfdU, 0xcbU, 79U, 0x4dU },
            //0x4e is the normal instruction, so not put here.
            { 0xfdU, 0xcbU, 232U, 0x4fU },

            // BIT 2,(IY +d).
            { 0xfdU, 0xcbU, 0U, 0x50U },
            { 0xfdU, 0xcbU, 255U, 0x51U },
            { 0xfdU, 0xcbU, 127U, 0x52U },
            { 0xfdU, 0xcbU, 32U, 0x53U },
            { 0xfdU, 0xcbU, 1U, 0x54U },
            { 0xfdU, 0xcbU, 79U, 0x55U },
            //0x56 is the normal instruction, so not put here.
            { 0xfdU, 0xcbU, 232U, 0x57U },

            // BIT 3,(IY +d).
            { 0xfdU, 0xcbU, 0U, 0x58U },
            { 0xfdU, 0xcbU, 255U, 0x59U },
            { 0xfdU, 0xcbU, 127U, 0x5aU },
            { 0xfdU, 0xcbU, 32U, 0x5bU },
            { 0xfdU, 0xcbU, 1U, 0x5cU },
            { 0xfdU, 0xcbU, 79U, 0x5dU },
            //0x5e is the normal instruction, so not put here.
            { 0xfdU, 0xcbU, 232U, 0x5fU },

            // BIT 4,(IY +d).
            { 0xfdU, 0xcbU, 0U, 0x60U },
            { 0xfdU, 0xcbU, 255U, 0x61U },
            { 0xfdU, 0xcbU, 127U, 0x62U },
            { 0xfdU, 0xcbU, 32U, 0x63U },
            { 0xfdU, 0xcbU, 1U, 0x64U },
            { 0xfdU, 0xcbU, 79U, 0x65U },
            //0x66 is the normal instruction, so not put here.
            { 0xfdU, 0xcbU, 232U, 0x67U },

            // BIT 5,(IY +d).
            { 0xfdU, 0xcbU, 0U, 0x68U },
            { 0xfdU, 0xcbU, 255U, 0x69U },
            { 0xfdU, 0xcbU, 127U, 0x6aU },
            { 0xfdU, 0xcbU, 32U, 0x6bU },
            { 0xfdU, 0xcbU, 1U, 0x6cU },
            { 0xfdU, 0xcbU, 79U, 0x6dU },
            //0x6e is the normal instruction, so not put here.
            { 0xfdU, 0xcbU, 232U, 0x6fU },

            // BIT 6,(IY +d).
            { 0xfdU, 0xcbU, 0U, 0x70U },
            { 0xfdU, 0xcbU, 255U, 0x71U },
            { 0xfdU, 0xcbU, 127U, 0x72U },
            { 0xfdU, 0xcbU, 32U, 0x73U },
            { 0xfdU, 0xcbU, 1U, 0x74U },
            { 0xfdU, 0xcbU, 79U, 0x75U },
            //0x76 is the normal instruction, so not put here.
            { 0xfdU, 0xcbU, 232U, 0x77U },

            // BIT 7,(IY +d).
            { 0xfdU, 0xcbU, 0U, 0x78U },
            { 0xfdU, 0xcbU, 255U, 0x79U },
            { 0xfdU, 0xcbU, 127U, 0x7aU },
            { 0xfdU, 0xcbU, 32U, 0x7bU },
            { 0xfdU, 0xcbU, 1U, 0x7cU },
            { 0xfdU, 0xcbU, 79U, 0x7dU },
            //0x7e is the normal instruction, so not put here.
            { 0xfdU, 0xcbU, 232U, 0x7fU },
    };

    for (const auto& opcodes : opcodesArray) {
        testUndocumentedInstructionUseBytesSpecific(opcodes);
    }
}

TEST_CASE("Disark, undocumented instruction use bytes", "[Disark]")
{
    // These come from OpcodesFiller.
    const std::vector<juce::String> instructions = {
            "RRC (IX +d),A",

            "SLL B",
            "SLL C",
            "SLL D",
            "SLL E",
            "SLL H",
            "SLL L",
            "SLL (HL)",
            "SLL A",

            "INC IXH",
            "DEC IXH",
            "LD IXH,0",
            "LD IXH,12",
            "LD IXH,255",

            "INC IXL",
            "DEC IXL",
            "LD IXL,0",
            "LD IXL,109",
            "LD IXL,255",

            "LD B,IXH",
            "LD B,IXL",

            "LD C,IXH",
            "LD C,IXL",
            "LD D,IXH",
            "LD D,IXL",
            "LD E,IXH",
            "LD E,IXL",
            "LD IXH,B",             // dd 60
            "LD IXH,C",
            "LD IXH,D",
            "LD IXH,E",
            "LD IXH,IXH",
            "LD IXH,IXL",
            "LD IXH,A",
            "LD IXL,B",
            "LD IXL,C",
            "LD IXL,D",
            "LD IXL,E",
            "LD IXL,IXH",
            "LD IXL,IXL",
            "LD IXL,A",
            "LD (IX +d),B",
            "LD (IX +d),C",
            "LD (IX +d),D",
            "LD (IX +d),E",
            "LD (IX +d),H",
            "LD (IX +d),L",
            "LD A,IXH",
            "LD A,IXL",
            "ADD A,IXH",
            "ADD A,IXL",
            "ADC A,IXH",
            "ADC A,IXL",
            "SUB IXH",
            "SUB IXL",
            "SBC A,IXH",
            "SBC A,IXL",
            "AND IXH",
            "AND IXL",
            "XOR IXH",
            "XOR IXL",
            "OR IXH",
            "OR IXL",
            "CP IXH",
            "CP IXL",

            //"NEG",    // NEG is not tested here, as the "documented" instruction will be used by default by RASM, the test won't work!
            "RETI",
            //"NEG",    // Only one is needed, even though there are several way of encoding it.
            //"RETN",
            //"NEG",
            //"RETN",
            //"NEG",
            //"RETN",
            //"IM 0",
            //"NEG",
            //"RETN",
            //"IM 0",
            "IN F,(C)",
            "OUT (C),0",
            //"NEG",
            //"RETN",
            //"IM 1",
            //"NEG",
            //"RETN",
            //"IM 2",             // ed 7e
            "INC IYH",
            "DEC IYH",
            "LD IYH,0",
            "LD IYH,212",
            "LD IYH,255",
            "INC IYL",
            "DEC IYL",
            "LD IYL,0",
            "LD IYL,100",
            "LD IYL,255",
            "LD B,IYH",
            "LD B,IYL",
            "LD C,IYH",
            "LD C,IYL",
            "LD D,IYH",
            "LD D,IYL",
            "LD E,IYH",
            "LD E,IYL",
            "LD IYH,B",
            "LD IYH,C",
            "LD IYH,D",
            "LD IYH,E",
            "LD IYH,IYH",
            "LD IYH,IYL",
            "LD IYH,A",
            "LD IYL,B",
            "LD IYL,C",
            "LD IYL,D",
            "LD IYL,E",
            "LD IYL,IYH",
            "LD IYL,IYL",
            "LD IYL,A",
            "LD A,IYH",
            "LD A,IYL",
            "ADD A,IYH",
            "ADD A,IYL",
            "ADC A,IYH",
            "ADC A,IYL",
            "SUB IYH",
            "SUB IYL",
            "SBC A,IYH",
            "SBC A,IYL",
            "AND IYH",
            "AND IYL",
            "XOR IYH",
            "XOR IYL",
            "OR IYH",
            "OR IYL",
            "CP IYH",
            "CP IYL",
            "RLC (IX +d),B",      // The RASM syntax. Official way: LD B,RLC (IX +d).
            "RLC (IX +d),C",
            "RLC (IX +d),D",
            "RLC (IX +d),E",
            "RLC (IX +d),H",
            "RLC (IX +d),L",
            "RLC (IX +d),A",
            "RRC (IX +d),B",
            "RRC (IX +d),C",
            "RRC (IX +d),D",
            "RRC (IX +d),E",
            "RRC (IX +d),H",
            "RRC (IX +d),L",
            "RRC (IX +d),A",
            "RL (IX +d),B",
            "RL (IX +d),C",
            "RL (IX +d),D",
            "RL (IX +d),E",
            "RL (IX +d),H",
            "RL (IX +d),L",
            "RL (IX +d)",
            "RL (IX +d),A",
            "RR (IX +d),B",
            "RR (IX +d),C",
            "RR (IX +d),D",
            "RR (IX +d),E",
            "RR (IX +d),H",
            "RR (IX +d),L",
            "RR (IX +d),A",
            "SLA (IX +d),B",
            "SLA (IX +d),C",
            "SLA (IX +d),D",
            "SLA (IX +d),E",
            "SLA (IX +d),H",
            "SLA (IX +d),L",
            "SLA (IX +d),A",
            "SRA (IX +d),B",
            "SRA (IX +d),C",
            "SRA (IX +d),D",
            "SRA (IX +d),E",
            "SRA (IX +d),H",
            "SRA (IX +d),L",
            "SRA (IX +d),A",
            "SLL (IX +d),B",
            "SLL (IX +d),C",
            "SLL (IX +d),D",
            "SLL (IX +d),E",
            "SLL (IX +d),H",
            "SLL (IX +d),L",
            "SLL (IX +d),A",
            "SRL (IX +d),B",
            "SRL (IX +d),C",
            "SRL (IX +d),D",
            "SRL (IX +d),E",
            "SRL (IX +d),H",
            "SRL (IX +d),L",
            "SRL (IX +d),A",
            /*"BIT 0,(IX +d)",  // Each has a normal instruction.
            "BIT 0,(IX +d)",
            "BIT 0,(IX +d)",
            "BIT 0,(IX +d)",
            "BIT 0,(IX +d)",
            "BIT 0,(IX +d)",
            "BIT 0,(IX +d)",
            "BIT 1,(IX +d)",
            "BIT 1,(IX +d)",
            "BIT 1,(IX +d)",
            "BIT 1,(IX +d)",
            "BIT 1,(IX +d)",
            "BIT 1,(IX +d)",
            "BIT 1,(IX +d)",
            "BIT 2,(IX +d)",
            "BIT 2,(IX +d)",
            "BIT 2,(IX +d)",
            "BIT 2,(IX +d)",
            "BIT 2,(IX +d)",
            "BIT 2,(IX +d)",
            "BIT 2,(IX +d)",
            "BIT 3,(IX +d)",
            "BIT 3,(IX +d)",
            "BIT 3,(IX +d)",
            "BIT 3,(IX +d)",
            "BIT 3,(IX +d)",
            "BIT 3,(IX +d)",
            "BIT 3,(IX +d)",
            "BIT 4,(IX +d)",
            "BIT 4,(IX +d)",
            "BIT 4,(IX +d)",
            "BIT 4,(IX +d)",
            "BIT 4,(IX +d)",
            "BIT 4,(IX +d)",
            "BIT 4,(IX +d)",
            "BIT 5,(IX +d)",
            "BIT 5,(IX +d)",
            "BIT 5,(IX +d)",
            "BIT 5,(IX +d)",
            "BIT 5,(IX +d)",
            "BIT 5,(IX +d)",
            "BIT 5,(IX +d)",
            "BIT 6,(IX +d)",
            "BIT 6,(IX +d)",
            "BIT 6,(IX +d)",
            "BIT 6,(IX +d)",
            "BIT 6,(IX +d)",
            "BIT 6,(IX +d)",
            "BIT 6,(IX +d)",
            "BIT 7,(IX +d)",
            "BIT 7,(IX +d)",
            "BIT 7,(IX +d)",
            "BIT 7,(IX +d)",
            "BIT 7,(IX +d)",
            "BIT 7,(IX +d)",
            "BIT 7,(IX +d)",*/
            "RES 0,(IX +d),B",
            "RES 0,(IX +d),C",
            "RES 0,(IX +d),D",
            "RES 0,(IX +d),E",
            "RES 0,(IX +d),H",
            "RES 0,(IX +d),L",
            "RES 0,(IX +d),A",
            "RES 1,(IX +d),B",
            "RES 1,(IX +d),C",
            "RES 1,(IX +d),D",
            "RES 1,(IX +d),E",
            "RES 1,(IX +d),H",
            "RES 1,(IX +d),L",
            "RES 1,(IX +d),A",
            "RES 2,(IX +d),B",
            "RES 2,(IX +d),C",
            "RES 2,(IX +d),D",
            "RES 2,(IX +d),E",
            "RES 2,(IX +d),H",
            "RES 2,(IX +d),L",
            "RES 2,(IX +d),A",
            "RES 3,(IX +d),B",
            "RES 3,(IX +d),C",
            "RES 3,(IX +d),D",
            "RES 3,(IX +d),E",
            "RES 3,(IX +d),H",
            "RES 3,(IX +d),L",
            "RES 3,(IX +d),A",
            "RES 4,(IX +d),B",
            "RES 4,(IX +d),C",
            "RES 4,(IX +d),D",
            "RES 4,(IX +d),E",
            "RES 4,(IX +d),H",
            "RES 4,(IX +d),L",
            "RES 4,(IX +d),A",
            "RES 5,(IX +d),B",
            "RES 5,(IX +d),C",
            "RES 5,(IX +d),D",
            "RES 5,(IX +d),E",
            "RES 5,(IX +d),H",
            "RES 5,(IX +d),L",
            "RES 5,(IX +d),A",
            "RES 6,(IX +d),B",
            "RES 6,(IX +d),C",
            "RES 6,(IX +d),D",
            "RES 6,(IX +d),E",
            "RES 6,(IX +d),H",
            "RES 6,(IX +d),L",
            "RES 6,(IX +d),A",
            "RES 7,(IX +d),B",
            "RES 7,(IX +d),C",
            "RES 7,(IX +d),D",
            "RES 7,(IX +d),E",
            "RES 7,(IX +d),H",
            "RES 7,(IX +d),L",
            "RES 7,(IX +d),A",
            "SET 0,(IX +d),B",
            "SET 0,(IX +d),C",
            "SET 0,(IX +d),D",
            "SET 0,(IX +d),E",
            "SET 0,(IX +d),H",
            "SET 0,(IX +d),L",
            "SET 0,(IX +d),A",
            "SET 1,(IX +d),B",
            "SET 1,(IX +d),C",
            "SET 1,(IX +d),D",
            "SET 1,(IX +d),E",
            "SET 1,(IX +d),H",
            "SET 1,(IX +d),L",
            "SET 1,(IX +d),A",
            "SET 2,(IX +d),B",
            "SET 2,(IX +d),C",
            "SET 2,(IX +d),D",
            "SET 2,(IX +d),E",
            "SET 2,(IX +d),H",
            "SET 2,(IX +d),L",
            "SET 2,(IX +d),A",
            "SET 3,(IX +d),B",
            "SET 3,(IX +d),C",
            "SET 3,(IX +d),D",
            "SET 3,(IX +d),E",
            "SET 3,(IX +d),H",
            "SET 3,(IX +d),L",
            "SET 3,(IX +d),A",
            "SET 4,(IX +d),B",
            "SET 4,(IX +d),C",
            "SET 4,(IX +d),D",
            "SET 4,(IX +d),E",
            "SET 4,(IX +d),H",
            "SET 4,(IX +d),L",
            "SET 4,(IX +d),A",
            "SET 5,(IX +d),B",
            "SET 5,(IX +d),C",
            "SET 5,(IX +d),D",
            "SET 5,(IX +d),E",
            "SET 5,(IX +d),H",
            "SET 5,(IX +d),L",
            "SET 5,(IX +d),A",
            "SET 6,(IX +d),B",
            "SET 6,(IX +d),C",
            "SET 6,(IX +d),D",
            "SET 6,(IX +d),E",
            "SET 6,(IX +d),H",
            "SET 6,(IX +d),L",
            "SET 6,(IX +d),A",
            "SET 7,(IX +d),B",
            "SET 7,(IX +d),C",
            "SET 7,(IX +d),D",
            "SET 7,(IX +d),E",
            "SET 7,(IX +d),H",
            "SET 7,(IX +d),L",
            "SET 7,(IX +d),A",


            "RLC (IY +d),B",
            "RLC (IY +d),C",
            "RLC (IY +d),D",
            "RLC (IY +d),E",
            "RLC (IY +d),H",
            "RLC (IY +d),L",
            "RLC (IY +d),A",
            "RRC (IY +d),B",
            "RRC (IY +d),C",
            "RRC (IY +d),D",
            "RRC (IY +d),E",
            "RRC (IY +d),H",
            "RRC (IY +d),L",
            "RRC (IY +d),A",
            "RL (IY +d),B",
            "RL (IY +d),C",
            "RL (IY +d),D",
            "RL (IY +d),E",
            "RL (IY +d),H",
            "RL (IY +d),L",
            "RL (IY +d),A",
            "RR (IY +d),B",
            "RR (IY +d),C",
            "RR (IY +d),D",
            "RR (IY +d),E",
            "RR (IY +d),H",
            "RR (IY +d),L",
            "RR (IY +d),A",
            "SLA (IY +d),B",
            "SLA (IY +d),C",
            "SLA (IY +d),D",
            "SLA (IY +d),E",
            "SLA (IY +d),H",
            "SLA (IY +d),L",
            "SLA (IY +d),A",
            "SRA (IY +d),B",
            "SRA (IY +d),C",
            "SRA (IY +d),D",
            "SRA (IY +d),E",
            "SRA (IY +d),H",
            "SRA (IY +d),L",
            "SRA (IY +d),A",
            "SLL (IY +d),B",
            "SLL (IY +d),C",
            "SLL (IY +d),D",
            "SLL (IY +d),E",
            "SLL (IY +d),H",
            "SLL (IY +d),L",
            "SLL (IY +d),A",
            "SRL (IY +d),B",
            "SRL (IY +d),C",
            "SRL (IY +d),D",
            "SRL (IY +d),E",
            "SRL (IY +d),H",
            "SRL (IY +d),L",
            "SRL (IY +d),A",
            /*"BIT 0,(IY +d)",      // Each has a normal instruction.
            "BIT 0,(IY +d)",
            "BIT 0,(IY +d)",
            "BIT 0,(IY +d)",
            "BIT 0,(IY +d)",
            "BIT 0,(IY +d)",
            "BIT 0,(IY +d)",
            "BIT 1,(IY +d)",
            "BIT 1,(IY +d)",
            "BIT 1,(IY +d)",
            "BIT 1,(IY +d)",
            "BIT 1,(IY +d)",
            "BIT 1,(IY +d)",
            "BIT 1,(IY +d)",
            "BIT 2,(IY +d)",
            "BIT 2,(IY +d)",
            "BIT 2,(IY +d)",
            "BIT 2,(IY +d)",
            "BIT 2,(IY +d)",
            "BIT 2,(IY +d)",
            "BIT 2,(IY +d)",
            "BIT 3,(IY +d)",
            "BIT 3,(IY +d)",
            "BIT 3,(IY +d)",
            "BIT 3,(IY +d)",
            "BIT 3,(IY +d)",
            "BIT 3,(IY +d)",
            "BIT 3,(IY +d)",
            "BIT 4,(IY +d)",
            "BIT 4,(IY +d)",
            "BIT 4,(IY +d)",
            "BIT 4,(IY +d)",
            "BIT 4,(IY +d)",
            "BIT 4,(IY +d)",
            "BIT 4,(IY +d)",
            "BIT 5,(IY +d)",
            "BIT 5,(IY +d)",
            "BIT 5,(IY +d)",
            "BIT 5,(IY +d)",
            "BIT 5,(IY +d)",
            "BIT 5,(IY +d)",
            "BIT 5,(IY +d)",
            "BIT 6,(IY +d)",
            "BIT 6,(IY +d)",
            "BIT 6,(IY +d)",
            "BIT 6,(IY +d)",
            "BIT 6,(IY +d)",
            "BIT 6,(IY +d)",
            "BIT 6,(IY +d)",
            "BIT 7,(IY +d)",
            "BIT 7,(IY +d)",
            "BIT 7,(IY +d)",
            "BIT 7,(IY +d)",
            "BIT 7,(IY +d)",
            "BIT 7,(IY +d)",
            "BIT 7,(IY +d)",*/
            "RES 0,(IY +d),B",
            "RES 0,(IY +d),C",
            "RES 0,(IY +d),D",
            "RES 0,(IY +d),E",
            "RES 0,(IY +d),H",
            "RES 0,(IY +d),L",
            "RES 0,(IY +d),A",
            "RES 1,(IY +d),B",
            "RES 1,(IY +d),C",
            "RES 1,(IY +d),D",
            "RES 1,(IY +d),E",
            "RES 1,(IY +d),H",
            "RES 1,(IY +d),L",
            "RES 1,(IY +d),A",
            "RES 2,(IY +d),B",
            "RES 2,(IY +d),C",
            "RES 2,(IY +d),D",
            "RES 2,(IY +d),E",
            "RES 2,(IY +d),H",
            "RES 2,(IY +d),L",
            "RES 2,(IY +d),A",
            "RES 3,(IY +d),B",
            "RES 3,(IY +d),C",
            "RES 3,(IY +d),D",
            "RES 3,(IY +d),E",
            "RES 3,(IY +d),H",
            "RES 3,(IY +d),L",
            "RES 3,(IY +d),A",
            "RES 4,(IY +d),B",
            "RES 4,(IY +d),C",
            "RES 4,(IY +d),D",
            "RES 4,(IY +d),E",
            "RES 4,(IY +d),H",
            "RES 4,(IY +d),L",
            "RES 4,(IY +d),A",
            "RES 5,(IY +d),B",
            "RES 5,(IY +d),C",
            "RES 5,(IY +d),D",
            "RES 5,(IY +d),E",
            "RES 5,(IY +d),H",
            "RES 5,(IY +d),L",
            "RES 5,(IY +d),A",
            "RES 6,(IY +d),B",
            "RES 6,(IY +d),C",
            "RES 6,(IY +d),D",
            "RES 6,(IY +d),E",
            "RES 6,(IY +d),H",
            "RES 6,(IY +d),L",
            "RES 6,(IY +d),A",
            "RES 7,(IY +d),B",
            "RES 7,(IY +d),C",
            "RES 7,(IY +d),D",
            "RES 7,(IY +d),E",
            "RES 7,(IY +d),H",
            "RES 7,(IY +d),L",
            "RES 7,(IY +d),A",
            "SET 0,(IY +d),B",
            "SET 0,(IY +d),C",
            "SET 0,(IY +d),D",
            "SET 0,(IY +d),E",
            "SET 0,(IY +d),H",
            "SET 0,(IY +d),L",
            "SET 0,(IY +d),A",
            "SET 1,(IY +d),B",
            "SET 1,(IY +d),C",
            "SET 1,(IY +d),D",
            "SET 1,(IY +d),E",
            "SET 1,(IY +d),H",
            "SET 1,(IY +d),L",
            "SET 1,(IY +d),A",
            "SET 2,(IY +d),B",
            "SET 2,(IY +d),C",
            "SET 2,(IY +d),D",
            "SET 2,(IY +d),E",
            "SET 2,(IY +d),H",
            "SET 2,(IY +d),L",
            "SET 2,(IY +d),A",
            "SET 3,(IY +d),B",
            "SET 3,(IY +d),C",
            "SET 3,(IY +d),D",
            "SET 3,(IY +d),E",
            "SET 3,(IY +d),H",
            "SET 3,(IY +d),L",
            "SET 3,(IY +d),A",
            "SET 4,(IY +d),B",
            "SET 4,(IY +d),C",
            "SET 4,(IY +d),D",
            "SET 4,(IY +d),E",
            "SET 4,(IY +d),H",
            "SET 4,(IY +d),L",
            "SET 4,(IY +d),A",
            "SET 5,(IY +d),B",
            "SET 5,(IY +d),C",
            "SET 5,(IY +d),D",
            "SET 5,(IY +d),E",
            "SET 5,(IY +d),H",
            "SET 5,(IY +d),L",
            "SET 5,(IY +d),A",
            "SET 6,(IY +d),B",
            "SET 6,(IY +d),C",
            "SET 6,(IY +d),D",
            "SET 6,(IY +d),E",
            "SET 6,(IY +d),H",
            "SET 6,(IY +d),L",
            "SET 6,(IY +d),A",
            "SET 7,(IY +d),B",
            "SET 7,(IY +d),C",
            "SET 7,(IY +d),D",
            "SET 7,(IY +d),E",
            "SET 7,(IY +d),H",
            "SET 7,(IY +d),L",
            "SET 7,(IY +d),A",
    };

    signed char d = 0;
    for (auto instruction : instructions) {
        // Converts "+d" into a value.
        if (instruction.contains("+d")) {
            auto shift = (d >= 0) ? ("+" + juce::String(d)) : juce::String(d);        // Keeps the + sign.
            instruction = instruction.replace("+d", shift);

            ++d;
        }

        //DBG(instruction);

        testUndocumentedInstructionAsBytes(instruction);
    }
}

TEST_CASE("Disark, referencingType forceNoReference", "[Disark]")
{
    // Tests that the reference is not encoded, even though it could have been.
    ExportConfiguration exportConfiguration;
    exportConfiguration.setGenerateOrg(true);
    DisassemblerTest disassembler(exportConfiguration);
    disassembler.setStartAddress(0x4000);
    disassembler.addSymbol({ "label1", 0x2000 });
    disassembler.addSymbol({ "label2", 0x3000 });

    disassembler.references().setReferencingType(0x4000, 0x4006, ReferencingType::forceNonReference);
    disassembler.references().setReferencingType(0x400c, 0x400f, ReferencingType::forceNonReference);
    juce::MemoryOutputStream outputStream;

    juce::MemoryBlock memoryBlock;
    const char dataIn[] = {
            0x01, 0x00, 0x20,           // ld bc,#2000      #4000
            0x01, 0x00, 0x30,           // ld bc,#3000      #4003
            0x01, 0x00, 0x20,           // ld bc,#2000      #4006
            0x01, 0x00, 0x30,           // ld bc,#3000      #4009
            0x01, 0x02, 0x20,           // ld bc,#2002      #400c
            0x01, 0x02, 0x30,           // ld bc,#3002      #400f
    };
    memoryBlock.insert(dataIn, 6 * 3, 0);
    juce::MemoryInputStream inputStream(memoryBlock, false);

    auto errorStrings = disassembler.disassemble(inputStream, outputStream);
    REQUIRE(errorStrings.empty());

    // Checks.
    auto strings = MemoryBlockUtil::extractStrings(outputStream.getMemoryBlock());
    size_t index = 0;
    REQUIRE(strings.at(index++) == "    org #4000");
    REQUIRE(strings.at(index++) == "    ld bc,#2000");
    REQUIRE(strings.at(index++) == "    ld bc,#3000");
    REQUIRE(strings.at(index++) == "    ld bc,label1");
    REQUIRE(strings.at(index++) == "    ld bc,label2");
    REQUIRE(strings.at(index++) == "    ld bc,#2002");
    REQUIRE(strings.at(index++) == "    ld bc,label2+2");
    REQUIRE(strings.at(index++) == "label1 equ #2000");      // Labels are generated because referenced.
    REQUIRE(strings.at(index++) == "label2 equ #3000");
    REQUIRE(strings.size() == index);
}


TEST_CASE("Disark, referencing type, forceReference", "[Disark]")
{
    // Tests that the reference is encoded.
    ExportConfiguration exportConfiguration;
    exportConfiguration.setGenerateOrg(true);
    DisassemblerTest disassembler(exportConfiguration);
    disassembler.setStartAddress(0x4000);
    disassembler.addSymbol({ "label1", 0x2000 });
    disassembler.addSymbol({ "label2", 0xf000 });

    disassembler.references().setReferencingType(0x4000, 0x4006, ReferencingType::forceReference);
    disassembler.references().setReferencingType(0x400c, 0x400f, ReferencingType::forceReference);
    juce::MemoryOutputStream outputStream;

    juce::MemoryBlock memoryBlock;
    const unsigned char dataIn[] = {
            0x01U, 0x00U, 0x00U,           // ld bc,#0000      #4000
            0x01U, 0x00U, 0x10U,           // ld bc,#1000      #4003
            0x01U, 0x00U, 0x20U,           // ld bc,#2000      #4006
            0x01U, 0x00U, 0xf0U,           // ld bc,#f000      #4009
            0x01U, 0x02U, 0xf0U,           // ld bc,#f002      #400c
            0x01U, 0x02U, 0x30U,           // ld bc,#3002      #400f
    };
    memoryBlock.insert(dataIn, 6 * 3, 0);
    juce::MemoryInputStream inputStream(memoryBlock, false);

    auto errorStrings = disassembler.disassemble(inputStream, outputStream);
    REQUIRE(errorStrings.empty());

    // Checks.
    auto strings = MemoryBlockUtil::extractStrings(outputStream.getMemoryBlock());
    size_t index = 0;
    REQUIRE(strings.at(index++) == "    org #4000");
    REQUIRE(strings.at(index++) == "    ld bc,label1-8192");
    REQUIRE(strings.at(index++) == "    ld bc,label1-4096");
    REQUIRE(strings.at(index++) == "    ld bc,label1");
    REQUIRE(strings.at(index++) == "    ld bc,label2");
    REQUIRE(strings.at(index++) == "    ld bc,label2+2");
    REQUIRE(strings.at(index++) == "    ld bc,#3002");
    REQUIRE(strings.at(index++) == "label1 equ #2000");      // Labels are generated because referenced.
    REQUIRE(strings.at(index++) == "label2 equ #f000");
    REQUIRE(strings.size() == index);
}


TEST_CASE("Disark, referencing Type, forceNoReferenceArea", "[Disark]")
{
    ExportConfiguration exportConfiguration;
    exportConfiguration.setGenerateOrg(true);
    Disassembler disassembler(exportConfiguration);
    disassembler.setStartAddress(0x4000);
    disassembler.addSymbol({ "label1", 0x2000 });
    disassembler.addSymbol({ "label2", 0x3000 });

    disassembler.addSymbol({ "xxx" + AreaTag::tagForceNonReferenceAreaStart + "1", 0x4003 });
    disassembler.addSymbol({ "xxx" + AreaTag::tagForceNonReferenceAreaEnd + "1", 0x4006 });

    disassembler.addSymbol({ "xxx" + AreaTag::tagForceNonReferenceAreaStart + "2", 0x4009 });
    disassembler.addSymbol({ "xxx" + AreaTag::tagForceNonReferenceAreaEnd + "2", 0x400f });

    juce::MemoryOutputStream outputStream;

    juce::MemoryBlock memoryBlock;
    const char dataIn[] = {
            0x01, 0x00, 0x20,           // ld bc,#2000      #4000
            0x01, 0x00, 0x30,           // ld bc,#3000      #4003   ;Non Ref.
            0x01, 0x00, 0x20,           // ld bc,#2000      #4006
            0x01, 0x00, 0x30,           // ld bc,#3000      #4009   ;Non Ref.
            0x01, 0x02, 0x20,           // ld bc,#2002      #400c   ;Non Ref.
            0x01, 0x02, 0x30,           // ld bc,#3002      #400f
    };
    memoryBlock.insert(dataIn, 6 * 3, 0);
    juce::MemoryInputStream inputStream(memoryBlock, false);

    auto errorStrings = disassembler.disassemble(inputStream, outputStream);
    REQUIRE(errorStrings.empty());

    // Checks.
    auto strings = MemoryBlockUtil::extractStrings(outputStream.getMemoryBlock());
    size_t index = 0;
    REQUIRE(strings.at(index++) == "    org #4000");
    REQUIRE(strings.at(index++) == "    ld bc,label1");
    REQUIRE(strings.at(index++) == "    ld bc,#3000");
    REQUIRE(strings.at(index++) == "    ld bc,label1");
    REQUIRE(strings.at(index++) == "    ld bc,#3000");
    REQUIRE(strings.at(index++) == "    ld bc,#2002");
    REQUIRE(strings.at(index++) == "    ld bc,label2+2");
    REQUIRE(strings.at(index++) == "label1 equ #2000");      // Labels are generated because referenced.
    REQUIRE(strings.at(index++) == "label2 equ #3000");
    REQUIRE(strings.size() == index);
}

TEST_CASE("Disark, referencing type, forceNoReferenceArea", "[Disark]")
{
    ExportConfiguration exportConfiguration;
    exportConfiguration.setGenerateOrg(true);
    Disassembler disassembler(exportConfiguration);
    disassembler.setStartAddress(0x4000);
    disassembler.addSymbol({ "label1", 0x4000 });

    disassembler.addSymbol({ "xxx" + AreaTag::tagForceReferenceAreaStart + "1", 0x4003 });
    disassembler.addSymbol({ "xxx" + AreaTag::tagForceReferenceAreaEnd + "1", 0x4006 });

    disassembler.addSymbol({ "xxx" + AreaTag::tagForceReferenceAreaStart + "2", 0x4009 });
    disassembler.addSymbol({ "xxx" + AreaTag::tagForceReferenceAreaEnd + "2", 0x400f });

    juce::MemoryOutputStream outputStream;

    juce::MemoryBlock memoryBlock;
    const char dataIn[] = {
            0x01, 0x00, 0x50,           // ld bc,#5000      #4000
            0x01, 0x00, 0x50,           // ld bc,#5000      #4003   ;Ref.
            0x01, 0x00, 0x50,           // ld bc,#5000      #4006
            0x01, 0x00, 0x60,           // ld bc,#6000      #4009   ;Ref.
            0x01, 0x02, 0x50,           // ld bc,#5002      #400c   ;Ref.
            0x01, 0x02, 0x60,           // ld bc,#6002      #400f
    };
    memoryBlock.insert(dataIn, 6 * 3, 0);
    juce::MemoryInputStream inputStream(memoryBlock, false);

    auto errorStrings = disassembler.disassemble(inputStream, outputStream);
    REQUIRE(errorStrings.empty());

    // Checks.
    auto strings = MemoryBlockUtil::extractStrings(outputStream.getMemoryBlock());
    size_t index = 0;
    REQUIRE(strings.at(index++) == "    org #4000");
    REQUIRE(strings.at(index++) == "label1 ld bc,#5000");
    REQUIRE(strings.at(index++) == "    ld bc,label1+4096");
    REQUIRE(strings.at(index++) == "    ld bc,#5000");
    REQUIRE(strings.at(index++) == "    ld bc,label1+8192");
    REQUIRE(strings.at(index++) == "    ld bc,label1+4098");
    REQUIRE(strings.at(index++) == "    ld bc,#6002");
    REQUIRE(strings.size() == index);
}


TEST_CASE("Disark, referencing type, pointerForceReferenceArea", "[Disark]")
{
    // Creates a byte area, declares a word with forced reference. The Word region should declare the Word.
    ExportConfiguration exportConfiguration;
    exportConfiguration.setGenerateOrg(true);
    Disassembler disassembler(exportConfiguration);
    disassembler.setStartAddress(0x4000);
    disassembler.addSymbol({ "label1", 0x4000 });

    disassembler.addSymbol({ "xxx" + AreaTag::tagByteRegionStart + "1", 0x4000 });
    disassembler.addSymbol({ "xxx" + AreaTag::tagByteRegionEnd + "1", 0x5000 });

    disassembler.addSymbol({ "xxx" + AreaTag::tagForceOneWordAreaWithForceReference + "1", 0x4002 });
    disassembler.addSymbol({ "xxx" + AreaTag::tagForceOneWordAreaWithForceReference + "2", 0x4006 });
    disassembler.addSymbol({ "xxx" + AreaTag::tagForceOneWordAreaWithForceReference + "3", 0x4008 });

    juce::MemoryOutputStream outputStream;
    juce::MemoryBlock memoryBlock;
    const char dataIn[] = {
            0x00, 0x50,           // dw #5000      #4000
            0x00, 0x50,           // dw #5000      #4002   ;Ref.
            0x00, 0x50,           // dw #5000      #4004
            0x00, 0x60,           // dw #6000      #4006   ;Ref.
            0x02, 0x50,           // dw #5002      #4008   ;Ref.
            0x02, 0x60,           // dw #6002      #400a
    };
    memoryBlock.insert(dataIn, 6 * 2, 0);
    juce::MemoryInputStream inputStream(memoryBlock, false);

    auto errorStrings = disassembler.disassemble(inputStream, outputStream);
    REQUIRE(errorStrings.empty());

    // Checks.
    auto strings = MemoryBlockUtil::extractStrings(outputStream.getMemoryBlock());
    size_t index = 0;
    REQUIRE(strings.at(index++) == "    org #4000");
    REQUIRE(strings.at(index++) == "label1 db #0");
    REQUIRE(strings.at(index++) == "    db #50");
    REQUIRE(strings.at(index++) == "    dw label1+4096");
    REQUIRE(strings.at(index++) == "    db #0");
    REQUIRE(strings.at(index++) == "    db #50");
    REQUIRE(strings.at(index++) == "    dw label1+8192");
    REQUIRE(strings.at(index++) == "    dw label1+4098");
    REQUIRE(strings.at(index++) == "    db #2");
    REQUIRE(strings.at(index++) == "    db #60");
    REQUIRE(strings.size() == index);
}

TEST_CASE("Disark, referencing type, pointerForceNonReferenceArea", "[Disark]")
{
    ExportConfiguration exportConfiguration;
    exportConfiguration.setGenerateOrg(true);
    Disassembler disassembler(exportConfiguration);
    disassembler.setStartAddress(0x4000);
    disassembler.addSymbol({ "label1", 0x5000 });
    disassembler.addSymbol({ "label2", 0x6000 });

    // Creates a Pointer area.
    disassembler.addSymbol({ "xxx" + AreaTag::tagPointerRegionStart + "1", 0x4000 });
    disassembler.addSymbol({ "xxx" + AreaTag::tagPointerRegionEnd + "1", 0x5000 });

    disassembler.addSymbol({ "xxx" + AreaTag::tagForceOneWordAreaWithForceNonReference + "1", 0x4002 });
    disassembler.addSymbol({ "xxx" + AreaTag::tagForceOneWordAreaWithForceNonReference + "2", 0x4006 });
    disassembler.addSymbol({ "xxx" + AreaTag::tagForceOneWordAreaWithForceNonReference + "3", 0x4008 });

    juce::MemoryOutputStream outputStream;
    juce::MemoryBlock memoryBlock;
    const char dataIn[] = {
            0x00, 0x50,           // dw #5000      #4000
            0x00, 0x50,           // dw #5000      #4002   ;Non ref.
            0x00, 0x60,           // dw #5000      #4004
            0x02, 0x60,           // dw #6000      #4006   ;Non ref.
            0x02, 0x50,           // dw #5002      #4008   ;Non ref.
            0x04, 0x60,           // dw #6004      #400a
    };
    memoryBlock.insert(dataIn, 6 * 2, 0);
    juce::MemoryInputStream inputStream(memoryBlock, false);

    auto errorStrings = disassembler.disassemble(inputStream, outputStream);
    REQUIRE(errorStrings.empty());

    // Checks.
    auto strings = MemoryBlockUtil::extractStrings(outputStream.getMemoryBlock());
    size_t index = 0;
    REQUIRE(strings.at(index++) == "    org #4000");
    REQUIRE(strings.at(index++) == "    dw label1");
    REQUIRE(strings.at(index++) == "    dw #5000");
    REQUIRE(strings.at(index++) == "    dw label2");
    REQUIRE(strings.at(index++) == "    dw #6002");
    REQUIRE(strings.at(index++) == "    dw #5002");
    REQUIRE(strings.at(index++) == "    dw label2+4");
    REQUIRE(strings.at(index++) == "label1 equ #5000");      // Labels are generated because referenced.
    REQUIRE(strings.at(index++) == "label2 equ #6000");
    REQUIRE(strings.size() == index);
}

TEST_CASE("Disark, referencing type, forceNoReference from label", "[Disark]")
{
    ExportConfiguration exportConfiguration;
    exportConfiguration.setGenerateOrg(true);
    Disassembler disassembler(exportConfiguration);
    disassembler.setStartAddress(0x4000);
    disassembler.addSymbol({ "label1", 0x2000 });
    disassembler.addSymbol({ "label2", 0x3000 });
    disassembler.addSymbol({ "bob_DisarkForceNonReferenceDuring3_1", 0x4000 });
    disassembler.addSymbol({ "bob_DisarkForceNonReferenceDuring3_2", 0x4003 });
    disassembler.addSymbol({ "bob_DisarkForceNonReferenceDuring3_3", 0x400c });

    juce::MemoryOutputStream outputStream;

    juce::MemoryBlock memoryBlock;
    const char dataIn[] = {
            0x01, 0x00, 0x20,           // ld bc,#2000      #4000
            0x01, 0x00, 0x30,           // ld bc,#3000      #4003
            0x01, 0x00, 0x20,           // ld bc,#2000      #4006
            0x01, 0x00, 0x30,           // ld bc,#3000      #4009
            0x01, 0x02, 0x20,           // ld bc,#2002      #400c
            0x01, 0x02, 0x30,           // ld bc,#3002      #400f
    };
    memoryBlock.insert(dataIn, 6 * 3, 0);
    juce::MemoryInputStream inputStream(memoryBlock, false);

    auto errorStrings = disassembler.disassemble(inputStream, outputStream);
    REQUIRE(errorStrings.empty());

    // Checks.
    auto strings = MemoryBlockUtil::extractStrings(outputStream.getMemoryBlock());
    size_t index = 0;
    REQUIRE(strings.at(index++) == "    org #4000");
    REQUIRE(strings.at(index++) == "    ld bc,#2000");
    REQUIRE(strings.at(index++) == "    ld bc,#3000");
    REQUIRE(strings.at(index++) == "    ld bc,label1");
    REQUIRE(strings.at(index++) == "    ld bc,label2");
    REQUIRE(strings.at(index++) == "    ld bc,#2002");
    REQUIRE(strings.at(index++) == "    ld bc,label2+2");
    REQUIRE(strings.at(index++) == "label1 equ #2000");      // Labels are generated because referenced.
    REQUIRE(strings.at(index++) == "label2 equ #3000");
    REQUIRE(strings.size() == index);
}

TEST_CASE("Disark, referencing type, forceReference from label", "[Disark]")
{
    ExportConfiguration exportConfiguration;
    exportConfiguration.setGenerateOrg(true);
    Disassembler disassembler(exportConfiguration);
    disassembler.setStartAddress(0x4000);
    disassembler.addSymbol({ "label1", 0x2000 });
    disassembler.addSymbol({ "label2", 0xf000 });

    disassembler.addSymbol({ "bob_DisarkForceReferenceDuring6_1", 0x4000 });
    disassembler.addSymbol({ "bob_DisarkForceReferenceDuring3_1", 0x400c });
    disassembler.addSymbol({ "bob_DisarkForceReferenceDuring3_2", 0x400f });

    juce::MemoryOutputStream outputStream;

    juce::MemoryBlock memoryBlock;
    const unsigned char dataIn[] = {
            0x01U, 0x00U, 0x00U,           // ld bc,#0000      #4000
            0x01U, 0x00U, 0x10U,           // ld bc,#1000      #4003
            0x01U, 0x00U, 0x20U,           // ld bc,#2000      #4006
            0x01U, 0x00U, 0xf0U,           // ld bc,#f000      #4009
            0x01U, 0x02U, 0xf0U,           // ld bc,#f002      #400c
            0x01U, 0x00U, 0x30U,           // ld bc,#3000      #400f
    };
    memoryBlock.insert(dataIn, 6 * 3, 0);
    juce::MemoryInputStream inputStream(memoryBlock, false);

    auto errorStrings = disassembler.disassemble(inputStream, outputStream);
    REQUIRE(errorStrings.empty());

    // Checks.
    auto strings = MemoryBlockUtil::extractStrings(outputStream.getMemoryBlock());
    size_t index = 0;
    REQUIRE(strings.at(index++) == "    org #4000");
    REQUIRE(strings.at(index++) == "    ld bc,label1-8192");
    REQUIRE(strings.at(index++) == "    ld bc,label1-4096");
    REQUIRE(strings.at(index++) == "    ld bc,label1");
    REQUIRE(strings.at(index++) == "    ld bc,label2");
    REQUIRE(strings.at(index++) == "    ld bc,label2+2");
    REQUIRE(strings.at(index++) == "    ld bc,label1+4096");       // Interesting test, because shows a marker label can not be used as a reference.
    REQUIRE(strings.at(index++) == "label1 equ #2000");      // Labels are generated because referenced.
    REQUIRE(strings.at(index++) == "label2 equ #f000");
    REQUIRE(strings.size() == index);
}

TEST_CASE("Disark, referencing type, forceReference errors", "[Disark]")
{
    {
        // Error, not followed by a number.
        ExportConfiguration exportConfiguration;
        exportConfiguration.setGenerateOrg(true);
        Disassembler disassembler(exportConfiguration);
        disassembler.setStartAddress(0x4000);

        disassembler.addSymbol({"bob_DisarkForceReferenceDuringa_1", 0x4000});          // Error, no digit.

        juce::MemoryOutputStream outputStream;

        juce::MemoryBlock memoryBlock;
        const char dataIn[] = {
                0x01, 0x00, 0x00,           // ld bc,#0000      #4000
        };
        memoryBlock.insert(dataIn, 3 * 3, 0);
        juce::MemoryInputStream inputStream(memoryBlock, false);

        auto errorStrings = disassembler.disassemble(inputStream, outputStream);
        REQUIRE(errorStrings.size() == 1);
    }

    {
        // Error, not followed by a digit.
        ExportConfiguration exportConfiguration;
        exportConfiguration.setGenerateOrg(true);
        Disassembler disassembler(exportConfiguration);
        disassembler.setStartAddress(0x4000);

        disassembler.addSymbol({"bob_DisarkForceReferenceDuring", 0x4000});          // Error, no digit present.

        juce::MemoryOutputStream outputStream;

        juce::MemoryBlock memoryBlock;
        const char dataIn[] = {
                0x01, 0x00, 0x00,           // ld bc,#0000      #4000
        };
        memoryBlock.insert(dataIn, 3 * 3, 0);
        juce::MemoryInputStream inputStream(memoryBlock, false);

        auto errorStrings = disassembler.disassemble(inputStream, outputStream);
        REQUIRE(errorStrings.size() == 1);
    }

    {
        // Error, size 0.
        ExportConfiguration exportConfiguration;
        exportConfiguration.setGenerateOrg(true);
        Disassembler disassembler(exportConfiguration);
        disassembler.setStartAddress(0x4000);

        disassembler.addSymbol({"bob_DisarkForceReferenceDuring0_1", 0x4000});

        juce::MemoryOutputStream outputStream;

        juce::MemoryBlock memoryBlock;
        const char dataIn[] = {
                0x01, 0x00, 0x00,           // ld bc,#0000      #4000
        };
        memoryBlock.insert(dataIn, 3 * 3, 0);
        juce::MemoryInputStream inputStream(memoryBlock, false);

        auto errorStrings = disassembler.disassemble(inputStream, outputStream);
        REQUIRE(errorStrings.size() == 1);
    }
}

TEST_CASE("Disark, rstAsIndex", "[Disark]")
{
    std::vector<juce::String> originalSourceStrings = {
            "rst 0",
            "rst #8",
            "rst #10",
            "rst #18",
            "rst #20",
            "rst #28",
            "rst #30",
            "rst #38",
    };
    ExportConfiguration exportConfiguration;
    exportConfiguration.setRstAsIndex(true);
    auto outputStrings = compileAndDisark(exportConfiguration, originalSourceStrings);

    size_t index = 0;
    REQUIRE(outputStrings.at(index++) == "    rst 0");
    REQUIRE(outputStrings.at(index++) == "    rst 1");
    REQUIRE(outputStrings.at(index++) == "    rst 2");
    REQUIRE(outputStrings.at(index++) == "    rst 3");
    REQUIRE(outputStrings.at(index++) == "    rst 4");
    REQUIRE(outputStrings.at(index++) == "    rst 5");
    REQUIRE(outputStrings.at(index++) == "    rst 6");
    REQUIRE(outputStrings.at(index++) == "    rst 7");
    REQUIRE(outputStrings.size() == index);
}

TEST_CASE("Disark, sdccRelativeRegisterSyntax", "[Disark]")
{
    std::vector<juce::String> originalSourceStrings = {
            "ld a,(ix+0)",
            "ld b,(ix-4)",
            "ld (ix+127),l",
            "ld (ix-128),e",
            "inc (ix+4)",
            "dec (ix)",
            "cp (ix+5)",
            "xor (ix +4)",
            "and (ix +99)",
            "or (ix -10)",
            "sub (ix -127)",
            "sbc a,(ix +12)",
            "add a,(ix +7)",

            "ld d,(iy+1)",
            "ld e,(iy-1)",
            "ld (iy+4),c",
            "ld (iy-46),d",
            "inc (iy)",
            "dec (iy-78)",
            "cp (iy-1)",
            "xor (iy +5)",
            "and (iy -12)",
            "or (iy)",
            "sub (iy +5)",
            "sbc a,(iy +127)",
            "add a,(iy-128)",
    };
    ExportConfiguration exportConfiguration;
    exportConfiguration.setSdccRelativeRegisterSyntax(true);
    auto outputStrings = compileAndDisark(exportConfiguration, originalSourceStrings);

    size_t index = 0;
    REQUIRE(outputStrings.at(index++) == "    ld a,+0(ix)");
    REQUIRE(outputStrings.at(index++) == "    ld b,-4(ix)");
    REQUIRE(outputStrings.at(index++) == "    ld +127(ix),l");
    REQUIRE(outputStrings.at(index++) == "    ld -128(ix),e");
    REQUIRE(outputStrings.at(index++) == "    inc +4(ix)");
    REQUIRE(outputStrings.at(index++) == "    dec +0(ix)");
    REQUIRE(outputStrings.at(index++) == "    cp +5(ix)");
    REQUIRE(outputStrings.at(index++) == "    xor +4(ix)");
    REQUIRE(outputStrings.at(index++) == "    and +99(ix)");
    REQUIRE(outputStrings.at(index++) == "    or -10(ix)");
    REQUIRE(outputStrings.at(index++) == "    sub -127(ix)");
    REQUIRE(outputStrings.at(index++) == "    sbc a,+12(ix)");
    REQUIRE(outputStrings.at(index++) == "    add a,+7(ix)");

    REQUIRE(outputStrings.at(index++) == "    ld d,+1(iy)");
    REQUIRE(outputStrings.at(index++) == "    ld e,-1(iy)");
    REQUIRE(outputStrings.at(index++) == "    ld +4(iy),c");
    REQUIRE(outputStrings.at(index++) == "    ld -46(iy),d");
    REQUIRE(outputStrings.at(index++) == "    inc +0(iy)");
    REQUIRE(outputStrings.at(index++) == "    dec -78(iy)");
    REQUIRE(outputStrings.at(index++) == "    cp -1(iy)");
    REQUIRE(outputStrings.at(index++) == "    xor +5(iy)");
    REQUIRE(outputStrings.at(index++) == "    and -12(iy)");
    REQUIRE(outputStrings.at(index++) == "    or +0(iy)");
    REQUIRE(outputStrings.at(index++) == "    sub +5(iy)");
    REQUIRE(outputStrings.at(index++) == "    sbc a,+127(iy)");
    REQUIRE(outputStrings.at(index++) == "    add a,-128(iy)");
    REQUIRE(outputStrings.size() == index);
}

TEST_CASE("Disark, sdccImmediateSyntax", "[Disark]")
{
    std::vector<juce::String> originalSourceStrings = {
            "add a,10",
            "sub a,20",
            "sbc a,30",
            "ld a,255",
            "ld a,0",
            "ld b,45",
            "ld c,-98",
            "ld d,-1",
            "label1 ld hl,label1",
            "ld hl,label1+2",
            "ld de,label1+3",
            "ld hl,(65530)"
    };
    ExportConfiguration exportConfiguration;
    exportConfiguration.setImmediateDataDeclarationSymbol("#");
    exportConfiguration.setEncode8BitNumberAsHex(false);
    exportConfiguration.setEncode16BitNumberAsHex(false);
    exportConfiguration.setNoPostFixAfterLabelWithEqu(true);
    auto outputStrings = compileAndDisark(exportConfiguration, originalSourceStrings);

    size_t index = 0;
    REQUIRE(outputStrings.at(index++) == "    add a,#10");
    REQUIRE(outputStrings.at(index++) == "    sub #20");
    REQUIRE(outputStrings.at(index++) == "    sbc a,#30");
    REQUIRE(outputStrings.at(index++) == "    ld a,#255");
    REQUIRE(outputStrings.at(index++) == "    ld a,#0");
    REQUIRE(outputStrings.at(index++) == "    ld b,#45");
    REQUIRE(outputStrings.at(index++) == "    ld c,#158");
    REQUIRE(outputStrings.at(index++) == "    ld d,#255");
    REQUIRE(outputStrings.at(index++) == "LABEL1 ld hl,#LABEL1");
    REQUIRE(outputStrings.at(index++) == "    ld hl,#LABEL1+2");
    REQUIRE(outputStrings.at(index++) == "    ld de,#LABEL1+3");
    REQUIRE(outputStrings.at(index++) == "    ld hl,(65530)");
    REQUIRE(outputStrings.size() == index);
}

TEST_CASE("Disark, sdccImmediateSyntaxHex", "[Disark]")
{
    std::vector<juce::String> originalSourceStrings = {
            "ld a,0xff",
            "ld a,0x0",
            "ld b,0x45",
            "ld c,-0x12",
            "ld d,-1",
            "sub a,0x10",
            "sbc a,0x30",
            "label1 ld hl,label1",
            "ld hl,label1+2",
            "ld de,label1+3",
            "ld hl,(65530)"
    };
    ExportConfiguration exportConfiguration;
    exportConfiguration.setImmediateDataDeclarationSymbol("#");
    exportConfiguration.setHexadecimalPrefix("0x");
    exportConfiguration.setNoPostFixAfterLabelWithEqu(true);
    auto outputStrings = compileAndDisark(exportConfiguration, originalSourceStrings);

    size_t index = 0;
    REQUIRE(outputStrings.at(index++) == "    ld a,#0xff");
    REQUIRE(outputStrings.at(index++) == "    ld a,#0x0");
    REQUIRE(outputStrings.at(index++) == "    ld b,#0x45");
    REQUIRE(outputStrings.at(index++) == "    ld c,#0xee");
    REQUIRE(outputStrings.at(index++) == "    ld d,#0xff");
    REQUIRE(outputStrings.at(index++) == "    sub #0x10");
    REQUIRE(outputStrings.at(index++) == "    sbc a,#0x30");
    REQUIRE(outputStrings.at(index++) == "LABEL1 ld hl,#LABEL1");
    REQUIRE(outputStrings.at(index++) == "    ld hl,#LABEL1+2");
    REQUIRE(outputStrings.at(index++) == "    ld de,#LABEL1+3");
    REQUIRE(outputStrings.at(index++) == "    ld hl,(0xfffa)");
    REQUIRE(outputStrings.size() == index);
}

TEST_CASE("Disark, sdccEqu", "[Disark]")
{
    ExportConfiguration exportConfiguration;
    exportConfiguration.setHexadecimalPrefix("0x");
    exportConfiguration.setLabelPostfix(":");           // However, for EQU, shouldn't be present! What a pain...
    exportConfiguration.setEquMnemonic("=");
    exportConfiguration.setNoPostFixAfterLabelWithEqu(true);

    Disassembler disassembler(exportConfiguration);
    disassembler.addSymbol({ "deb", 0 });
    disassembler.addSymbol({ "label1", 0x5040 });

    juce::MemoryOutputStream outputStream;

    // No region, no references.
    juce::MemoryBlock memoryBlock;
    const unsigned char dataIn[] = {
            0x21, 0, 0,                 // ld hl,deb
            0x04,                       // inc b
            0x01, 0x40, 0x50,           // ld bc,&5040
            0xdd, 0x09                  // add ix,bc
    };
    memoryBlock.insert(dataIn, 9, 0);
    juce::MemoryInputStream inputStream(memoryBlock, false);

    auto errorStrings = disassembler.disassemble(inputStream, outputStream);
    REQUIRE(errorStrings.empty());

    // Checks.
    auto strings = MemoryBlockUtil::extractStrings(outputStream.getMemoryBlock());

    size_t index = 0;
    REQUIRE(strings.at(index++) == "deb: ld hl,deb");
    REQUIRE(strings.at(index++) == "    inc b");
    REQUIRE(strings.at(index++) == "    ld bc,label1");
    REQUIRE(strings.at(index++) == "    add ix,bc");
    REQUIRE(strings.at(index++) == "label1 = 0x5040");      // Label 1 is generated because referenced.
    REQUIRE(strings.size() == index);
}

TEST_CASE("Disark, forceReturnCarriageBeforeSet", "[Disark]")
{
    std::vector<juce::String> originalSourceStrings = {
            "label1 res 0,a",
            " set 0,a",
            "label2 set 1,b",
            "label3",
            "label4 set 7,d",
    };
    ExportConfiguration exportConfiguration;
    exportConfiguration.setNoLabelBeforeSetInstruction(true);
    auto outputStrings = compileAndDisark(exportConfiguration, originalSourceStrings);

    size_t index = 0;
    REQUIRE(outputStrings.at(index++) == "LABEL1 res 0,a");
    REQUIRE(outputStrings.at(index++) == "    set 0,a");
    REQUIRE(outputStrings.at(index++) == "LABEL2");
    REQUIRE(outputStrings.at(index++) == "    set 1,b");
    REQUIRE(outputStrings.at(index++) == "LABEL3");
    REQUIRE(outputStrings.at(index++) == "LABEL4");
    REQUIRE(outputStrings.at(index++) == "    set 7,d");
    REQUIRE(outputStrings.size() == index);
}

TEST_CASE("Disark, declareExternalLabels", "[Disark]")
{
    std::vector<juce::String> originalSourceStrings = {
            " jp init",
            " jp play",
            " jp stopp",
            "initDisarkGenerateExternalLabel",      // Declared first, but I don't want it to be seen as priority.
            "init",                                 // It actually works because it is renamed to the same name internally!
            "     ld hl,#4000",
            "     ld a,b",
            "     ex de,hl",
            "     ret",
            "playDisarkGenerateExternalLabel",      // Idem.
            "play",
            "     ld hl,#5000",
            "     ret",
            "stopp",
            "stoppDisarkGenerateExternalLabel",
            "     ld a,1",
            "     ret"
    };
    ExportConfiguration exportConfiguration;
    exportConfiguration.setGenerateExternalLabels(true);
    exportConfiguration.setLabelPostfix(":");           // This is SDCC original label postfix.
    auto outputStrings = compileAndDisark(exportConfiguration, originalSourceStrings);

    size_t index = 0;
    REQUIRE(outputStrings.at(index++) == "    jp INIT");
    REQUIRE(outputStrings.at(index++) == "    jp PLAY");
    REQUIRE(outputStrings.at(index++) == "    jp STOPP");
    REQUIRE(outputStrings.at(index++) == "_INIT::");
    REQUIRE(outputStrings.at(index++) == "INIT: ld hl,#4000");
    REQUIRE(outputStrings.at(index++) == "    ld a,b");
    REQUIRE(outputStrings.at(index++) == "    ex de,hl");
    REQUIRE(outputStrings.at(index++) == "    ret ");
    REQUIRE(outputStrings.at(index++) == "_PLAY::");
    REQUIRE(outputStrings.at(index++) == "PLAY: ld hl,#5000");
    REQUIRE(outputStrings.at(index++) == "    ret ");
    REQUIRE(outputStrings.at(index++) == "STOPP:");
    REQUIRE(outputStrings.at(index++) == "_STOPP:: ld a,#1");
    REQUIRE(outputStrings.at(index++) == "    ret ");
    REQUIRE(outputStrings.size() == index);
}

TEST_CASE("Disark, removeExternalLabels", "[Disark]")
{
    std::vector<juce::String> originalSourceStrings = {
            " jp init",
            " jp play",
            " jp stopp",
            "initDisarkGenerateExternalLabel",      // Declared first, but I don't want it to be seen as priority.
            "init",                                 // It actually works because it is renamed to the same name internally!
            "     ld hl,#4000",
            "     ld a,b",
            "     ex de,hl",
            "     ret",
            "playDisarkGenerateExternalLabel",      // Idem.
            "play",
            "     ld hl,#5000",
            "     ret",
            "stopp",
            "stoppDisarkGenerateExternalLabel",
            "     ld a,1",
            "     ret"
    };
    ExportConfiguration exportConfiguration;
    // External labels are not displayed by default.
    auto outputStrings = compileAndDisark(exportConfiguration, originalSourceStrings);

    size_t index = 0;
    REQUIRE(outputStrings.at(index++) == "    jp INIT");
    REQUIRE(outputStrings.at(index++) == "    jp PLAY");
    REQUIRE(outputStrings.at(index++) == "    jp STOPP");
    REQUIRE(outputStrings.at(index++) == "INIT ld hl,#4000");
    REQUIRE(outputStrings.at(index++) == "    ld a,b");
    REQUIRE(outputStrings.at(index++) == "    ex de,hl");
    REQUIRE(outputStrings.at(index++) == "    ret ");
    REQUIRE(outputStrings.at(index++) == "PLAY ld hl,#5000");
    REQUIRE(outputStrings.at(index++) == "    ret ");
    REQUIRE(outputStrings.at(index++) == "STOPP ld a,#1");
    REQUIRE(outputStrings.at(index++) == "    ret ");
    REQUIRE(outputStrings.size() == index);
}

TEST_CASE("Disark, autoDeclareUsedFarLabel", "[Disark]")
{
    std::vector<juce::String> originalSourceStrings = {
            " jp init",
            " ld hl,#4000",
            "init equ #c000",
            "     ret"
    };
    ExportConfiguration exportConfiguration;
    auto outputStrings = compileAndDisark(exportConfiguration, originalSourceStrings);

    size_t index = 0;
    REQUIRE(outputStrings.at(index++) == "    jp INIT");
    REQUIRE(outputStrings.at(index++) == "    ld hl,#4000");
    REQUIRE(outputStrings.at(index++) == "    ret ");
    REQUIRE(outputStrings.at(index++) == "INIT equ #c000");
    REQUIRE(outputStrings.size() == index);
}

TEST_CASE("Disark, overlappingRegions", "[Disark]")
{
    std::vector<juce::String> originalSourceStrings = {
            "TestSubsong0DisarkPointerRegionStart27",           // Outer Pointer Region.
            "TestSubsong0_Track_70",
            "TestSubsong0DisarkByteRegionStart28",              // Inner Byte Region, starting at the same location, but only one byte large.
            "    db #ff    ; Duration.",
            "TestSubsong0DisarkByteRegionEnd28",
            "    dw #1234",
            "TestSubsong0DisarkPointerRegionEnd27"
    };
    ExportConfiguration exportConfiguration;
    auto outputStrings = compileAndDisark(exportConfiguration, originalSourceStrings);

    size_t index = 0;
    REQUIRE(outputStrings.at(index++) == "TESTSUBSONG0_TRACK_70 db #ff");
    REQUIRE(outputStrings.at(index++) == "    dw #1234");
    REQUIRE(outputStrings.size() == index);
}





TEST_CASE("Disark, all instructions", "[Disark]")
{
    compileAndCheckSource(BinaryData::AllInstructions_asm, BinaryData::AllInstructions_asmSize);
}

TEST_CASE("Disark, compile player aky", "[Disark]")
{
    compileAndCheckSource(BinaryData::PlayerAky_asm, BinaryData::PlayerAky_asmSize);
}

TEST_CASE("Disark, compile player akg", "[Disark]")
{
    compileAndCheckSource(BinaryData::PlayerAkg_asm, BinaryData::PlayerAkg_asmSize);
}



TEST_CASE("Disark, validate Disark Music Akg Empty", "[Disark]")
{
    const juce::MemoryBlock memoryBlock(BinaryData::AkgEmpty_asm, BinaryData::AkgEmpty_asmSize);
    validateDisarkedSource(memoryBlock, false, PlayerType::Akg);
}

TEST_CASE("Disark, validate Disark Music Akg Harmless Grenade", "[Disark]")
{
    const juce::MemoryBlock memoryBlock(BinaryData::AkgHarmlessGrenade_asm, BinaryData::AkgHarmlessGrenade_asmSize);
    validateDisarkedSource(memoryBlock, false, PlayerType::Akg);
}

TEST_CASE("Disark, validate Disark Music Aky", "[Disark]")
{
    const juce::MemoryBlock memoryBlock(BinaryData::AkyHarmlessGrenade_asm, BinaryData::AkyHarmlessGrenade_asmSize);
    validateDisarkedSource(memoryBlock, false, PlayerType::Aky);
}


TEST_CASE("Disark, validate Disark Player Akg", "[Disark]")
{
    const juce::MemoryBlock playerMemoryBlockWithoutOrg(BinaryData::PlayerAkg_asm, BinaryData::PlayerAkg_asmSize);
    validateDisarkedSource(playerMemoryBlockWithoutOrg, true, PlayerType::Akg, false);
}

TEST_CASE("Disark, validate Disark Player Akg with sfx", "[Disark]")
{
    const juce::MemoryBlock playerMemoryBlockWithoutOrg(BinaryData::PlayerAkg_asm, BinaryData::PlayerAkg_asmSize);
    validateDisarkedSource(playerMemoryBlockWithoutOrg, true, PlayerType::Akg, false, true);
}


TEST_CASE("Disark, validate Disark Player Akm", "[Disark]")
{
    const juce::MemoryBlock playerMemoryBlockWithoutOrg(BinaryData::PlayerAkm_asm, BinaryData::PlayerAkm_asmSize);
    validateDisarkedSource(playerMemoryBlockWithoutOrg, true, PlayerType::Akm, false);
}

TEST_CASE("Disark, validate Disark Player Akm with sfx", "[Disark]")
{
    const juce::MemoryBlock playerMemoryBlockWithoutOrg(BinaryData::PlayerAkm_asm, BinaryData::PlayerAkm_asmSize);
    validateDisarkedSource(playerMemoryBlockWithoutOrg, true, PlayerType::Akm, false, true);
}


TEST_CASE("Disark, validate Disark Player Aky", "[Disark]")
{
    const juce::MemoryBlock playerMemoryBlockWithoutOrg(BinaryData::PlayerAky_asm, BinaryData::PlayerAky_asmSize);
    validateDisarkedSource(playerMemoryBlockWithoutOrg, true, PlayerType::Aky);
}


TEST_CASE("Disark, validate Disark Player Aky Multiple PSG", "[Disark]")
{
    const juce::MemoryBlock playerMemoryBlockWithoutOrg(BinaryData::PlayerAkyMultiPsg_asm, BinaryData::PlayerAkyMultiPsg_asmSize);
    validateDisarkedSource(playerMemoryBlockWithoutOrg, true, PlayerType::AkyMultiplePsgs, true);
}

TEST_CASE("Disark, validate Disark Player Aky Multiple PSG with sfx", "[Disark]")
{
    const juce::MemoryBlock playerMemoryBlockWithoutOrg(BinaryData::PlayerAkyMultiPsg_asm, BinaryData::PlayerAkyMultiPsg_asmSize);
    validateDisarkedSource(playerMemoryBlockWithoutOrg, true, PlayerType::AkyMultiplePsgs, true, true);
}


TEST_CASE("Disark, validate Disark Player Aky stabilized", "[Disark]")
{
    const juce::MemoryBlock playerMemoryBlockWithoutOrg(BinaryData::PlayerAkyStabilized_CPC_asm, BinaryData::PlayerAkyStabilized_CPC_asmSize);
    validateDisarkedSource(playerMemoryBlockWithoutOrg, false, PlayerType::Aky);    // Only CPC, no ROM.
}


TEST_CASE("Disark, validate Disark Player LW", "[Disark]")
{
    const juce::MemoryBlock playerMemoryBlockWithoutOrg(BinaryData::PlayerLightweight_asm, BinaryData::PlayerLightweight_asmSize);
    validateDisarkedSource(playerMemoryBlockWithoutOrg, true, PlayerType::Lightweight, false);
}

TEST_CASE("Disark, validate Disark Player LW with sfx", "[Disark]")
{
    const juce::MemoryBlock playerMemoryBlockWithoutOrg(BinaryData::PlayerLightweight_asm, BinaryData::PlayerLightweight_asmSize);
    validateDisarkedSource(playerMemoryBlockWithoutOrg, true, PlayerType::Lightweight, false, true);
}


TEST_CASE("Disark, validate Disark Player LW SharpMz 700", "[Disark]")
{
    const juce::MemoryBlock playerMemoryBlockWithoutOrg(BinaryData::PlayerLightweight_SHARPMZ700_asm, BinaryData::PlayerLightweight_SHARPMZ700_asmSize);
    validateDisarkedSource(playerMemoryBlockWithoutOrg, false, PlayerType::LightweightSharpMz700, false, true);    // Only "CPC", no ROM.
}


TEST_CASE("Disark, validate Disark empty music LW", "[Disark]")
{
    const juce::MemoryBlock sourceMemoryBlock(BinaryData::LwEmpty_asm, BinaryData::LwEmpty_asmSize);
    validateDisarkedSource(sourceMemoryBlock, true, PlayerType::Lightweight);
}


TEST_CASE("Disark, validate Disark music all effects and instruments LW", "[Disark]")
{
    const juce::MemoryBlock sourceMemoryBlock(BinaryData::LwAllEffectsAndInstruments_asm, BinaryData::LwAllEffectsAndInstruments_asmSize);
    validateDisarkedSource(sourceMemoryBlock, true, PlayerType::Lightweight);
}



TEST_CASE("Disark, validate Disark sound effects player", "[Disark]")
{
    const juce::MemoryBlock playerMemoryBlockWithoutOrg(BinaryData::PlayerSoundEffects_asm, BinaryData::PlayerSoundEffects_asmSize);
    validateDisarkedSource(playerMemoryBlockWithoutOrg, true, PlayerType::StandAloneSoundEffects);
}

TEST_CASE("Disark, validate Disark sound effects", "[Disark]")
{
    const juce::MemoryBlock sourceMemoryBlock(BinaryData::SoundEffects_asm, BinaryData::SoundEffects_asmSize);
    validateDisarkedSource(sourceMemoryBlock, false, PlayerType::StandAloneSoundEffects);
}

TEST_CASE("Disark, validate Disark AKM all sounds", "[Disark]")
{
    const juce::MemoryBlock sourceMemoryBlock(BinaryData::AkmAllSounds_asm, BinaryData::AkmAllSounds_asmSize);
    validateDisarkedSource(sourceMemoryBlock, false, PlayerType::Akm);
}

TEST_CASE("Disark, validate Disark AKM Pitch table effect", "[Disark]")
{
    const juce::MemoryBlock sourceMemoryBlock(BinaryData::AkmPitchTableAndForcePitchSpeedAndPitchAndResetChannel1_asm, BinaryData::AkmPitchTableAndForcePitchSpeedAndPitchAndResetChannel1_asmSize);
    validateDisarkedSource(sourceMemoryBlock, false, PlayerType::Akm);
}


TEST_CASE("Disark, validate Disark AKM Arpeggio table effect", "[Disark]")
{
    const juce::MemoryBlock sourceMemoryBlock(BinaryData::AkmArpeggioEffectStackedChannel1To3_asm, BinaryData::AkmArpeggioEffectStackedChannel1To3_asmSize);
    validateDisarkedSource(sourceMemoryBlock, false, PlayerType::Akm);
}

}    // namespace disark
