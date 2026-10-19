#include "../../catch.hpp"

#include "../../../source/export/sourceGenerator/SourceGenerator.h"
#include "../../../source/utils/MemoryBlockUtil.h"

namespace arkostracker 
{

TEST_CASE("SourceGenerator, simple Z80", "[SourceGenerator]")
{
    // Given.
    const auto configuration = SourceGeneratorConfiguration::buildZ80();

    juce::MemoryOutputStream outputStream;
    SourceGenerator sourceGenerator(configuration, outputStream);

    // When.
    sourceGenerator.declareAddressChange(0x1234)
        .declareLabel("MyLabel1", true, "My comment.")
        .declareByte(1)
        .declareByte(0, "This is a comment")
        .declareByte(255)
        .declareLabel("MyLabel2")
        .declareByte(12)
        .addEmptyLine()
        .declareByte(25)
        .declareEndOfFile();

    const auto generatedText = MemoryBlockUtil::extractStrings(outputStream.getMemoryBlock());

    REQUIRE((generatedText == std::vector {
        juce::String("    org 4660"),
        juce::String("MyLabel1    ; My comment."),
        juce::String("    db 1"),
        juce::String("    db 0    ; This is a comment"),
        juce::String("    db 255"),
        juce::String("MyLabel2"),
        juce::String("    db 12"),
        juce::String(""),
        juce::String("    db 25"),
    }));
}

TEST_CASE("SourceGenerator, more Z80", "[SourceGenerator]")
{
    // Given.
    const SourceGeneratorConfiguration configuration("org {x}", "'{x}*", true, "db {x}",
                                                     "dw {x}", "da {x}--", "db \"{x}\"",
                                                     "equ {x}", ".{x}:", true,
                                                     "asm", "bin", 4);

    juce::MemoryOutputStream outputStream;
    SourceGenerator sourceGenerator(configuration, outputStream);

    // When.
    sourceGenerator.declareAddressChange(65535)
        .declareByte("1+2+3")
        .declareAddressChange(0)
        .declareLabel("TheLabel1")
        .declareByte("1+2+3+4", "Complicated stuff")
        .declareWord(16384)
        .declareWord(65535, "Youpi")
        .declareWord("blob + 12", "Wow!")
        .declareConstant("SuperConstant", "42")
        .declareConstant("SuperConstant2", "42", "hello")
        .declareAddress(124)
        .declareAddress(65535, "This is cool")
        .declareAddress("blob + 12", "Wow!")
        .declareEndOfFile();

    const auto generatedText = MemoryBlockUtil::extractStrings(outputStream.getMemoryBlock());

    REQUIRE((generatedText == std::vector {
        juce::String("    org 65535"),
        juce::String("    db 1+2+3"),
        juce::String("    org 0"),
        juce::String(".TheLabel1:"),
        juce::String("    db 1+2+3+4    'Complicated stuff*"),
        juce::String("    dw 16384"),
        juce::String("    dw 65535    'Youpi*"),
        juce::String("    dw blob + 12    'Wow!*"),
        juce::String("SuperConstant equ 42"),
        juce::String("SuperConstant2 equ 42    'hello*"),
        juce::String("    da 124--"),
        juce::String("    da 65535--    'This is cool*"),
        juce::String("    da blob + 12--    'Wow!*"),
    }));
}

TEST_CASE("SourceGenerator, multiline mnemonics", "[SourceGenerator]")
{
    // Given.
    const SourceGeneratorConfiguration configuration("org {x}", "-- {x} --", true, "db {x}",
                                                     "beforeDw\r\nword {x}\r\nafterDw", "prepareAdr\nadr {x}\npostAdr",
                                                     "db \"{x}\"", "equ {x}",
                                                     ".{x}:", true,
                                                     "asm", "bin", 4);

    juce::MemoryOutputStream outputStream;
    SourceGenerator sourceGenerator(configuration, outputStream);

    // When.
    sourceGenerator
            .declareAddress(124)
            .declareWord(789, "This is a comment")
            .declareComment("Another comment.")
        .declareEndOfFile();

    const auto generatedText = MemoryBlockUtil::extractStrings(outputStream.getMemoryBlock());

    REQUIRE((generatedText == std::vector {
        juce::String("    prepareAdr"),
        juce::String("    adr 124"),
        juce::String("    postAdr"),

        juce::String("    beforeDw    -- This is a comment --"),
        juce::String("    word 789"),
        juce::String("    afterDw"),

        juce::String("-- Another comment. --"),
    }));
}

TEST_CASE("SourceGenerator, advanced mnemonics, little endian", "[SourceGenerator]")
{
    // Given.
    const SourceGeneratorConfiguration configuration = { "org {x}", "; {x}", true,
                                                   "db {x}", "dw {x}", "da {x}",
                                                   "db \"{x}\"", "equ {x}", "{x}", true,
                                                   "asm", "bin", 8 };

    juce::MemoryOutputStream outputStream;
    SourceGenerator sourceGenerator(configuration, outputStream);

    // When.
    const auto relExp1 = SourceGenerator::buildRelativeExpression("label1", "rel1");
    const auto relExp2 = SourceGenerator::buildRelativeExpression("label2", "");
    sourceGenerator
            .declareAddress(relExp1)
            .declareAddress(relExp2, "Yep.")
            .declareFourBytes(0x11ff3344)
            .declareAddressOrRelativeAddress("label", "rel")
            .declareAddressOrRelativeAddress("label", "")
            .declareEndOfFile();

    const auto generatedText = MemoryBlockUtil::extractStrings(outputStream.getMemoryBlock());

    REQUIRE((generatedText == std::vector {
            juce::String("        da label1 - rel1"),
            juce::String("        da label2    ; Yep."),
            juce::String("        db 68"),
            juce::String("        db 51"),
            juce::String("        db 255"),
            juce::String("        db 17"),
            juce::String("        da label - rel"),
            juce::String("        da label"),
    }));
}

TEST_CASE("SourceGenerator, big endian", "[SourceGenerator]")
{
    // Given.
    const SourceGeneratorConfiguration configuration = { "org {x}", "; {x}", true,
                                                   "db {x}", "dw {x}", "dw {x}",
                                                   "db \"{x}\"", "equ {x}", "{x}", false,
                                                   "asm", "bin", 8 };

    juce::MemoryOutputStream outputStream;
    SourceGenerator sourceGenerator(configuration, outputStream);

    // When.
    sourceGenerator
            .declareFourBytes(0x11ff3344)
            .declareEndOfFile();

    const auto generatedText = MemoryBlockUtil::extractStrings(outputStream.getMemoryBlock());

    REQUIRE((generatedText == std::vector {
            juce::String("        db 17"),
            juce::String("        db 255"),
            juce::String("        db 51"),
            juce::String("        db 68"),
    }));
}

TEST_CASE("SourceGenerator, no comments", "[SourceGenerator]")
{
    // Given.
    const SourceGeneratorConfiguration configuration("org {x}", "-- {x} --", false, "db {x}",
                                                     "beforeDw\r\nword {x}\r\nafterDw", "prepareAdr\nadr {x}\npostAdr",
                                                     "db \"{x}\"", "equ {x}", ".{x}:", true,
                                                     "asm", "bin", 4);

    juce::MemoryOutputStream outputStream;
    SourceGenerator sourceGenerator(configuration, outputStream);

    // When.
    sourceGenerator
            .declareAddress(124)
            .addEmptyLine()
            .declareByte(10, "This is a comment")
            .declareComment("Comment.")
            .addEmptyLine()
            .declareWord(789, "This is a comment")
            .declareComment("Another comment.")
            .declareConstant("YOUPI", "12", "Comment")
            .declareConstant("THE_VARIABLE", "1")
            .declareEndOfFile();

    const auto generatedText = MemoryBlockUtil::extractStrings(outputStream.getMemoryBlock());

    REQUIRE((generatedText == std::vector {
            juce::String("    prepareAdr"),
            juce::String("    adr 124"),
            juce::String("    postAdr"),
            juce::String(),
            juce::String("    db 10"),
            juce::String(),
            juce::String("    beforeDw"),
            juce::String("    word 789"),
            juce::String("    afterDw"),
            juce::String("YOUPI equ 12"),
            juce::String("THE_VARIABLE equ 1"),
    }));
}

TEST_CASE("SourceGenerator, Disark", "[SourceGenerator]")
{
    // Given.
    const auto configuration = SourceGeneratorConfiguration::buildZ80();

    juce::MemoryOutputStream outputStream;
    SourceGenerator sourceGenerator(configuration, outputStream);

    // When.
    sourceGenerator
            .declareExternalLabel("MyLabel1_")
            .declareEndOfFile();

    const auto generatedText = MemoryBlockUtil::extractStrings(outputStream.getMemoryBlock());

    REQUIRE((generatedText == std::vector {
            juce::String("MyLabel1_DisarkGenerateExternalLabel"),
    }));
}

}   // namespace arkostracker
