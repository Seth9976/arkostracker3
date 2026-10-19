#include "../catch.hpp"

#include "../../source/utils/Base64Util.h"

namespace arkostracker 
{

/**
 * Tests the Base 64 Util class.
 * An old class with many warnings, silenced a bit abruptly.
 */

/**
 * Tests the Encode method.
 * @param source the source.
 * @param expected the expected Base64 data.
 * @return true if everything went fine.
 */
bool testEncodeToBase64(std::vector<unsigned char>& source, const std::vector<unsigned char>& expected)
{
    // Source to InputStream.
    juce::MemoryBlock sourceMemoryBlock;
    for (auto c : source) {
        sourceMemoryBlock.append(&c, 1U);
    }
    juce::MemoryInputStream inputStream(sourceMemoryBlock, true);

    juce::MemoryOutputStream outputStream;
    auto success = Base64Util::encodeToBase64(inputStream, outputStream);
    if (!success) {
        return false;
    }

    // Compares the OutputStream to the Expected.
    auto outputMemoryBlock = outputStream.getMemoryBlock();
    // The size should be as expected.
    if (outputMemoryBlock.getSize() != expected.size()) {
        success = false;
    } else {
        auto i = 0;
        for (const auto c : expected) {
            if (c != outputMemoryBlock[i]) {     // NOLINT(clion-misra-cpp2008-5-0-4, *-signed-char-misuse)
                DBG("Testing offset: " + juce::String(i));
                success = false;
                break;
            }
            ++i;
        }
    }

    return success;
}

/**
 * Tests the Decode method.*
 * @param source the Base64 data source.
 * @param expected the expected output data.
 * @return true if everything went fine.
 */
bool testDecodeFromBase64(std::vector<unsigned char>& source, const std::vector<unsigned char>& expected)
{
    // Source to InputStream.
    juce::MemoryBlock sourceMemoryBlock;
    for (auto c : source) {
        sourceMemoryBlock.append(&c, 1U);
    }
    juce::MemoryInputStream inputStream(sourceMemoryBlock, true);

    juce::MemoryOutputStream outputStream;
    auto success = Base64Util::decodeFromBase64(inputStream, outputStream);
    if (!success) {
        return false;
    }

    // Compares the OutputStream to the Expected.
    auto outputMemoryBlock = outputStream.getMemoryBlock();
    // The size should be as expected.
    if (outputMemoryBlock.getSize() != expected.size()) {
        success = false;
    } else {
        auto i = 0;
        for (const auto c : expected) {
            if (c != outputMemoryBlock[i]) {    // NOLINT(clion-misra-cpp2008-5-0-4, *-signed-char-misuse)
                DBG("Testing offset: " + juce::String(i));
                success = false;
                break;
            }
            ++i;
        }
    }

    return success;
}

/**
 * Converts the base64 String given into a vector, and compares it with the expected text.
 * @param base64 the Base64 text.
 * @param expected the expected decrypted text.
 * @param expectSuccess true if we suppose this will work. Useful to test error cases.
 */
void callBase64TextToVectorAndCompare(const juce::String& base64, const juce::String& expected, const bool expectSuccess)
{
    bool success;    // NOLINT(*-init-variables)

    auto vectorResult = Base64Util::decodeBase64StringToVector(base64, success);
    // Tolerate a different size of the result only if we knew it was going to fail.
    if (vectorResult.size() != static_cast<size_t>(expected.length())) {
        REQUIRE(!expectSuccess);
    }
    // If the conversion failed, nothing more to do.
    if (!expectSuccess) {
        return;
    }

    REQUIRE((success == expectSuccess));

    // Compares each character.
    auto i = 0;
    for (const auto resultChar : vectorResult) {
        REQUIRE((resultChar == expected[i]));    // NOLINT(clion-misra-cpp2008-5-0-4, *-signed-char-misuse)
        ++i;
    }
}


// =========================================================================

TEST_CASE("Base64Util, encode, errors", "[Base64Util]")
{
    std::vector<unsigned char> source = { 'M', 'a', 'n' };      // NOLINT(clion-misra-cpp2008-5-0-4)
    std::vector<unsigned char> expected = { 'T', 'W', 'F', 'u', 'a' };      // One added character.      // NOLINT(clion-misra-cpp2008-5-0-4)
    REQUIRE(!testEncodeToBase64(source, expected));

    source = { 'M', 'a', 'n' };      // NOLINT(clion-misra-cpp2008-5-0-4)
    expected = { 'T', 'W', 'F' };                                           // One missing character.      // NOLINT(clion-misra-cpp2008-5-0-4)
    REQUIRE(!testEncodeToBase64(source, expected));
}

TEST_CASE("Base64Util, encode, no padding", "[Base64Util]")
{
    std::vector<unsigned char> source;
    std::vector<unsigned char> expected;

    source = { };
    expected = { };
    REQUIRE(testEncodeToBase64(source, expected));

    source = { 'M', 'a', 'n' };      // NOLINT(clion-misra-cpp2008-5-0-4)
    expected = { 'T', 'W', 'F', 'u' };      // NOLINT(clion-misra-cpp2008-5-0-4)
    REQUIRE(testEncodeToBase64(source, expected));

    source = { 'a', 'n', 'y', ' ', 'c', 'a', 'r', 'n', 'a', 'l', ' ', 'p', 'l', 'e', 'a', 's', 'u', 'r' };      // NOLINT(clion-misra-cpp2008-5-0-4)
    expected = { 'Y', 'W', '5', '5', 'I', 'G', 'N', 'h', 'c', 'm', '5', 'h', 'b', 'C', 'B', 'w', 'b', 'G', 'V', 'h', 'c', '3', 'V', 'y' };      // NOLINT(clion-misra-cpp2008-5-0-4)
    REQUIRE(testEncodeToBase64(source, expected));
}

TEST_CASE("Base64Util, encode, padding", "[Base64Util]")
{
    // Padding 1.
    std::vector<unsigned char> source;
    std::vector<unsigned char> expected;

    source = { 's', 'u', 'r', 'e', '.' };      // NOLINT(clion-misra-cpp2008-5-0-4)
    expected = { 'c', '3', 'V', 'y', 'Z', 'S', '4', '=' };      // NOLINT(clion-misra-cpp2008-5-0-4)
    REQUIRE(testEncodeToBase64(source, expected));

    source = { 'l', 'e', 'a', 's', 'u', 'r', 'e', '.' };      // NOLINT(clion-misra-cpp2008-5-0-4)
    expected = { 'b', 'G', 'V', 'h', 'c', '3', 'V', 'y', 'Z', 'S', '4', '=' };      // NOLINT(clion-misra-cpp2008-5-0-4)
    REQUIRE(testEncodeToBase64(source, expected));

    source = { 'a', 'n', 'y', ' ', 'c', 'a', 'r', 'n', 'a', 'l', ' ', 'p', 'l', 'e', 'a', 's', 'u', 'r', 'e', '.' };      // NOLINT(clion-misra-cpp2008-5-0-4)
    expected = { 'Y', 'W', '5', '5', 'I', 'G', 'N', 'h', 'c', 'm', '5', 'h', 'b', 'C', 'B', 'w', 'b', 'G', 'V', 'h', 'c', '3', 'V', 'y', 'Z', 'S', '4', '=' };      // NOLINT(clion-misra-cpp2008-5-0-4)
    REQUIRE(testEncodeToBase64(source, expected));
}

TEST_CASE("Base64Util, encode, padding2", "[Base64Util]")
{
    // Padding 2.
    std::vector<unsigned char> source;
    std::vector<unsigned char> expected;

    source = { 'e', 'a', 's', 'u', 'r', 'e', '.' };      // NOLINT(clion-misra-cpp2008-5-0-4)
    expected = { 'Z', 'W', 'F', 'z', 'd', 'X', 'J', 'l', 'L', 'g', '=', '=' };      // NOLINT(clion-misra-cpp2008-5-0-4)
    REQUIRE(testEncodeToBase64(source, expected));

    source = { 'a', 'n', 'y', ' ', 'c', 'a', 'r', 'n', 'a', 'l', ' ', 'p', 'l', 'e', 'a', 's' };      // NOLINT(clion-misra-cpp2008-5-0-4)
    expected = { 'Y', 'W', '5', '5', 'I', 'G', 'N', 'h', 'c', 'm', '5', 'h', 'b', 'C', 'B', 'w', 'b', 'G', 'V', 'h', 'c', 'w', '=', '=' };      // NOLINT(clion-misra-cpp2008-5-0-4)
    REQUIRE(testEncodeToBase64(source, expected));

    source = { 'a', 'n', 'y', ' ', 'c', 'a', 'r', 'n', 'a', 'l', ' ', 'p', 'l', 'e', 'a', 's', 'u', 'r', 'e' };      // NOLINT(clion-misra-cpp2008-5-0-4)
    expected = { 'Y', 'W', '5', '5', 'I', 'G', 'N', 'h', 'c', 'm', '5', 'h', 'b', 'C', 'B', 'w', 'b', 'G', 'V', 'h', 'c', '3', 'V', 'y', 'Z', 'Q', '=', '=' };      // NOLINT(clion-misra-cpp2008-5-0-4)
    REQUIRE(testEncodeToBase64(source, expected));
}

// ==================================================================================

TEST_CASE("Base64Util, encode string, simple", "[Base64Util]")
{
    const juce::String source = "any carnal pleas";
    const juce::String expected = "YW55IGNhcm5hbCBwbGVhcw==";

    auto success = false;
    const auto result = Base64Util::encodeToBase64(source, success);
    REQUIRE(success);
    REQUIRE((result == expected));
}

TEST_CASE("Base64Util, encode string with return carriage", "[Base64Util]")
{
    const juce::String source = "Hello!\n"
                                "This a multi-line String.\n"
                                "Yes !\n"
                                "\n"
                                "Great.";
    const juce::String expected = "SGVsbG8hClRoaXMgYSBtdWx0aS1saW5lIFN0cmluZy4KWWVzICEKCkdyZWF0Lg==";

    auto success = false;
    const auto result = Base64Util::encodeToBase64(source, success);
    REQUIRE(success);
    REQUIRE((result == expected));
}


// ==================================================================================

TEST_CASE("Base64Util, decode, errors", "[Base64Util]")
{
    std::vector<unsigned char> source = { 'T', 'W', 'F', 'u', 'a' };        // One added character.      // NOLINT(clion-misra-cpp2008-5-0-4)
    std::vector<unsigned char> expected = { 'M', 'a', 'n' };      // NOLINT(clion-misra-cpp2008-5-0-4)
    REQUIRE(!testDecodeFromBase64(source, expected));

    expected = { 'M', 'a', 'n' };      // NOLINT(clion-misra-cpp2008-5-0-4)
    source = { 'T', 'W', 'F' };                                         // One missing character.      // NOLINT(clion-misra-cpp2008-5-0-4)
    REQUIRE(!testDecodeFromBase64(source, expected));
}

TEST_CASE("Base64Util, decode, no padding", "[Base64Util]")
{
    std::vector<unsigned char> source;
    std::vector<unsigned char> expected;

    source = {};
    expected = {};
    REQUIRE(testDecodeFromBase64(source, expected));

    source = { 'T', 'W', 'F', 'u' };      // NOLINT(clion-misra-cpp2008-5-0-4)
    expected = { 'M', 'a', 'n' };      // NOLINT(clion-misra-cpp2008-5-0-4)
    REQUIRE(testDecodeFromBase64(source, expected));

    source = { 'Y', 'W', '5', '5', 'I', 'G', 'N', 'h', 'c', 'm', '5', 'h', 'b', 'C', 'B', 'w', 'b', 'G', 'V', 'h', 'c', '3', 'V', 'y' };      // NOLINT(clion-misra-cpp2008-5-0-4)
    expected = { 'a', 'n', 'y', ' ', 'c', 'a', 'r', 'n', 'a', 'l', ' ', 'p', 'l', 'e', 'a', 's', 'u', 'r' };      // NOLINT(clion-misra-cpp2008-5-0-4)
    REQUIRE(testDecodeFromBase64(source, expected));
}

TEST_CASE("Base64Util, decode, no padding1", "[Base64Util]")
{
    // Padding 1.
    std::vector<unsigned char> source;
    std::vector<unsigned char> expected;

    source = { 'c', '3', 'V', 'y', 'Z', 'S', '4', '=' };      // NOLINT(clion-misra-cpp2008-5-0-4)
    expected = { 's', 'u', 'r', 'e', '.' };      // NOLINT(clion-misra-cpp2008-5-0-4)
    REQUIRE(testDecodeFromBase64(source, expected));

    source = { 'b', 'G', 'V', 'h', 'c', '3', 'V', 'y', 'Z', 'S', '4', '=' };      // NOLINT(clion-misra-cpp2008-5-0-4)
    expected = { 'l', 'e', 'a', 's', 'u', 'r', 'e', '.' };      // NOLINT(clion-misra-cpp2008-5-0-4)
    REQUIRE(testDecodeFromBase64(source, expected));

    source = { 'Y', 'W', '5', '5', 'I', 'G', 'N', 'h', 'c', 'm', '5', 'h', 'b', 'C', 'B', 'w', 'b', 'G', 'V', 'h', 'c', '3', 'V', 'y', 'Z', 'S', '4', '=' };      // NOLINT(clion-misra-cpp2008-5-0-4)
    expected = { 'a', 'n', 'y', ' ', 'c', 'a', 'r', 'n', 'a', 'l', ' ', 'p', 'l', 'e', 'a', 's', 'u', 'r', 'e', '.' };      // NOLINT(clion-misra-cpp2008-5-0-4)
    REQUIRE(testDecodeFromBase64(source, expected));
}

TEST_CASE("Base64Util, decode, no padding 2", "[Base64Util]")
{
    // Padding 2.
    std::vector<unsigned char> source;
    std::vector<unsigned char> expected;

    source = { 'Z', 'W', 'F', 'z', 'd', 'X', 'J', 'l', 'L', 'g', '=', '=' };      // NOLINT(clion-misra-cpp2008-5-0-4)
    expected = { 'e', 'a', 's', 'u', 'r', 'e', '.' };      // NOLINT(clion-misra-cpp2008-5-0-4)
    REQUIRE(testDecodeFromBase64(source, expected));

    source = { 'Y', 'W', '5', '5', 'I', 'G', 'N', 'h', 'c', 'm', '5', 'h', 'b', 'C', 'B', 'w', 'b', 'G', 'V', 'h', 'c', 'w', '=', '=' };      // NOLINT(clion-misra-cpp2008-5-0-4)
    expected = { 'a', 'n', 'y', ' ', 'c', 'a', 'r', 'n', 'a', 'l', ' ', 'p', 'l', 'e', 'a', 's' };      // NOLINT(clion-misra-cpp2008-5-0-4)
    REQUIRE(testDecodeFromBase64(source, expected));

    source = { 'Y', 'W', '5', '5', 'I', 'G', 'N', 'h', 'c', 'm', '5', 'h', 'b', 'C', 'B', 'w', 'b', 'G', 'V', 'h', 'c', '3', 'V', 'y', 'Z', 'Q', '=', '=' };      // NOLINT(clion-misra-cpp2008-5-0-4)
    expected = { 'a', 'n', 'y', ' ', 'c', 'a', 'r', 'n', 'a', 'l', ' ', 'p', 'l', 'e', 'a', 's', 'u', 'r', 'e' };      // NOLINT(clion-misra-cpp2008-5-0-4)
    REQUIRE(testDecodeFromBase64(source, expected));
}


// ==================================================================================

TEST_CASE("Base64Util, base64TextToVector", "[Base64Util]")
{
    callBase64TextToVectorAndCompare(
            "VGhlIHF1aWNrIGJyb3duIGZveCBqdW1wcyBvdmVyIDEzIGxhenkgZG9ncy4=",
            "The quick brown fox jumps over 13 lazy dogs.",
            true);

    callBase64TextToVectorAndCompare(
            "Qm9uam91cg==",
            "Bonjour",
            true);

    callBase64TextToVectorAndCompare(
            "Qm9uam91ciBsZXMgYW1pcy4u",
            "Bonjour les amis..",
            true);

    // Error case.
    callBase64TextToVectorAndCompare(
            "Qm9uam91cg==",
            "Bonjour ",
            false);
    callBase64TextToVectorAndCompare(
            "VGXhlIHF1aWNrIGJyb3duIGZveCBqdW1wcyBvdmVyIDEzIGxhenkgZG9ncy4=",
            "The quick brown fox jumps over 13 lazy dogs.",
            false);
    callBase64TextToVectorAndCompare(
            "VGhlIHF1aWNrIGJyb3duIGZveCBqdW1wcyBvdmVyIDEzIGxhenkgZG9ncy3=",
            "The quick brown fox jumps over 13 lazy dogs.",
            false);
}


}   // namespace arkostracker

