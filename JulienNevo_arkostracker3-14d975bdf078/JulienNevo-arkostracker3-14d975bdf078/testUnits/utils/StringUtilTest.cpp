#include "../catch.hpp"

#include "../../source/utils/StringUtil.h"

namespace arkostracker 
{

/** Tests the StringUtil class. */

TEST_CASE("extractExtension", "[StringUtil]")
{
    REQUIRE((StringUtil::extractExtension("aks", false) == "aks"));
    REQUIRE((StringUtil::extractExtension("aks", true) == ".aks"));
    REQUIRE((StringUtil::extractExtension(".aki", false) == "aki"));
    REQUIRE((StringUtil::extractExtension(".aki", true) == ".aki"));
    REQUIRE((StringUtil::extractExtension("*.abcd", false) == "abcd"));
    REQUIRE((StringUtil::extractExtension("*.abcd", true) == ".abcd"));
    REQUIRE((StringUtil::extractExtension("bob.zxer", false) == "zxer"));
    REQUIRE((StringUtil::extractExtension("bob.zxer", true) == ".zxer"));
}

TEST_CASE("stringToBool", "[StringUtil]")
{
    REQUIRE(StringUtil::stringToBool("true"));
    REQUIRE(StringUtil::stringToBool("TRUE"));
    REQUIRE(StringUtil::stringToBool("True"));
    REQUIRE(StringUtil::stringToBool("TrUE"));
    REQUIRE(StringUtil::stringToBool("  True"));
    REQUIRE(StringUtil::stringToBool("  True   "));

    REQUIRE(!StringUtil::stringToBool("tru"));
    REQUIRE(!StringUtil::stringToBool("false"));
    REQUIRE(!StringUtil::stringToBool("False"));
    REQUIRE(!StringUtil::stringToBool("Fals"));
    REQUIRE(!StringUtil::stringToBool("FalsE"));
    REQUIRE(!StringUtil::stringToBool("FALSE"));
}

TEST_CASE("stringToInt", "[StringUtil]")
{
    auto success = true;
    REQUIRE(StringUtil::stringToInt("1" , success) == 1);
    REQUIRE(success);
    REQUIRE(StringUtil::stringToInt("123" , success) == 123);
    REQUIRE(success);
    REQUIRE(StringUtil::stringToInt(" 12345   " , success) == 12345);
    REQUIRE(success);
    REQUIRE(StringUtil::stringToInt("-9" , success) == -9);
    REQUIRE(success);
    REQUIRE(StringUtil::stringToInt("-91087" , success) == -91087);
    REQUIRE(success);

    REQUIRE(StringUtil::stringToInt("" , success) == 0);
    REQUIRE_FALSE(success);
    REQUIRE(StringUtil::stringToInt("   " , success) == 0);
    REQUIRE_FALSE(success);
    REQUIRE(StringUtil::stringToInt("1b" , success) == 0);
    REQUIRE_FALSE(success);
    REQUIRE(StringUtil::stringToInt("----9" , success) == 0);
    REQUIRE_FALSE(success);
    REQUIRE(StringUtil::stringToInt("1-" , success) == 0);
    REQUIRE_FALSE(success);
}

TEST_CASE("boolToString", "[StringUtil]")
{
    REQUIRE((juce::String("false") == StringUtil::boolToString(false)));
    REQUIRE((juce::String("true") == StringUtil::boolToString(true)));
}

TEST_CASE("boolToYesOrNo", "[StringUtil]")
{
    REQUIRE((juce::String("Yes") == StringUtil::boolToYesOrNo(true)));
    REQUIRE((juce::String("No") == StringUtil::boolToYesOrNo(false)));
}

TEST_CASE("split", "[StringUtil]")
{
    REQUIRE((StringUtil::split("abc,def,ghh,z", ",") == std::vector<juce::String> {"abc", "def", "ghh", "z"}));
    REQUIRE((StringUtil::split("a,def", ",") == std::vector<juce::String> {"a", "def"}));
    REQUIRE((StringUtil::split("a,def,", ",") == std::vector<juce::String> {"a", "def"}));
    REQUIRE((StringUtil::split("zef", ",") == std::vector<juce::String> {"zef"}));
    REQUIRE((StringUtil::split("zef,", ",") == std::vector<juce::String> {"zef"}));
    REQUIRE(StringUtil::split("", ",").empty());
    REQUIRE(StringUtil::split(",", ",").empty());
    REQUIRE((StringUtil::split("a  bc  d    eee      ffff  ", " ") == std::vector<juce::String> {"a", "bc", "d", "eee", "ffff"}));

    REQUIRE((StringUtil::split("abc:::://::::def:::://::::ghh:::://::::z", ":::://::::") == std::vector<juce::String> {"abc", "def", "ghh", "z"}));
}

TEST_CASE("stringToNoteNumber", "[StringUtil]")
{
    REQUIRE((StringUtil::stringToNoteNumber("C#0") == 1));
    REQUIRE((StringUtil::stringToNoteNumber("C-1") == (12 * 1)));
    REQUIRE((StringUtil::stringToNoteNumber("C#1") == (12 * 1) + 1));
    REQUIRE((StringUtil::stringToNoteNumber("f-4") == (12 * 4) + 5));
    REQUIRE((StringUtil::stringToNoteNumber("B-9") == (12 * 9) + 11));
    REQUIRE((StringUtil::stringToNoteNumber("C-a") == (12 * 10)));
    REQUIRE((StringUtil::stringToNoteNumber("C-A") == (12 * 10)));
    REQUIRE((StringUtil::stringToNoteNumber("C-B") == (12 * 11)));

    REQUIRE((StringUtil::stringToNoteNumber("") == -1));
    REQUIRE((StringUtil::stringToNoteNumber("F") == -1));
    REQUIRE((StringUtil::stringToNoteNumber("C-") == -1));
    REQUIRE((StringUtil::stringToNoteNumber("C-x") == -1));
    REQUIRE((StringUtil::stringToNoteNumber("C-11") == -1));
}

}   // namespace arkostracker

