#include "../../../catch.hpp"

#include "../../../../source/business/sourceProfile/SourceProfile.h"
#include "../../../../source/business/sourceProfile/SourceProfileValidator.h"

namespace arkostracker 
{

TEST_CASE("SourceProfileValidator, nominal", "[SourceProfileValidatorTest]")
{
    // Given.
    const SourceGeneratorConfiguration configuration(
            "org {x}", "; {x}", true, "db {x}", "dw {x}",
            "dw {x}", "ds {x}", "equ {x}",
            "{x}", true, "asm", "bin", 4
    );
    const SourceProfile sourceProfile(configuration, "hello", false);

    // When.
    const auto errors = SourceProfileValidator::validate(sourceProfile);

    // Then.
    REQUIRE(errors.empty());
}

TEST_CASE("SourceProfileValidator, empty extensions", "[SourceProfileValidatorTest]")
{
    // Given.
    const SourceGeneratorConfiguration configuration(
            "org {x}", "; {x}", true, "db {x}", "dw {x}",
            "dw {x}", "ds {x}", "equ {x}",
            "{x}", true, "", "  ", 4
    );
    const SourceProfile sourceProfile(configuration, "hello", false);

    // When.
    const auto errors = SourceProfileValidator::validate(sourceProfile);

    // Then.
    REQUIRE((errors.size() == 2));
    REQUIRE((errors.at(0) == std::make_pair(SourceProfileValidator::Location::asmExtension, SourceProfileValidator::Error::empty)));
    REQUIRE((errors.at(1) == std::make_pair(SourceProfileValidator::Location::binExtension, SourceProfileValidator::Error::empty)));
}

TEST_CASE("SourceProfileValidator, empty and dot extension", "[SourceProfileValidatorTest]")
{
    // Given.
    const SourceGeneratorConfiguration configuration(
            "org {x}", "; {x}", true, "db {x}", "dw {x}",
            "dw {x}", "ds {x}", "equ {x}",
            "{x}", true, "  ", ".bin", 4
    );
    const SourceProfile sourceProfile(configuration, "hello", false);

    // When.
    const auto errors = SourceProfileValidator::validate(sourceProfile);

    // Then.
    REQUIRE((errors.size() == 2));
    REQUIRE((errors.at(0) == std::make_pair(SourceProfileValidator::Location::asmExtension, SourceProfileValidator::Error::empty)));
    REQUIRE((errors.at(1) == std::make_pair(SourceProfileValidator::Location::binExtension, SourceProfileValidator::Error::mustNotStartWithDot)));
}

TEST_CASE("SourceProfileValidator, tabulation size too small", "[SourceProfileValidatorTest]")
{
    // Given.
    const SourceGeneratorConfiguration configuration(
            "org {x}", "; {x}", true, "db {x}", "dw {x}",
            "dw {x}", "ds {x}",
            "equ {x}", "{x}", true, "asm", "bin", 0
    );
    const SourceProfile sourceProfile(configuration, "hello", false);

    // When.
    const auto errors = SourceProfileValidator::validate(sourceProfile);

    // Then.
    REQUIRE((errors.size() == 1));
    REQUIRE((errors.at(0) == std::make_pair(SourceProfileValidator::Location::tabulationSize, SourceProfileValidator::Error::invalidValue)));
}

TEST_CASE("SourceProfileValidator, tabulation size too high, plus extension dot", "[SourceProfileValidatorTest]")
{
    // Given.
    const SourceGeneratorConfiguration configuration(
            "org {x}", "; {x}", true, "db {x}", "dw {x}",
            "dw {x}", "ds {x}", "equ {x}",
            "{x}", true, ".asm", "bin", 17
    );
    const SourceProfile sourceProfile(configuration, "hello", false);

    // When.
    const auto errors = SourceProfileValidator::validate(sourceProfile);

    // Then.
    REQUIRE((errors.size() == 2));
    REQUIRE((errors.at(0) == std::make_pair(SourceProfileValidator::Location::asmExtension, SourceProfileValidator::Error::mustNotStartWithDot)));
    REQUIRE((errors.at(1) == std::make_pair(SourceProfileValidator::Location::tabulationSize, SourceProfileValidator::Error::invalidValue)));
}

TEST_CASE("SourceProfileValidator, missing all placeholders", "[SourceProfileValidatorTest]")
{
    // Given.
    const SourceGeneratorConfiguration configuration(
            "org ", "; ", true, "db ", "dw ",
            "dw ", "ds ", "equ {}", "", true, "asm", "bin", 8
    );
    const SourceProfile sourceProfile(configuration, "hello", false);

    // When.
    const auto errors = SourceProfileValidator::validate(sourceProfile);

    // Then.
    size_t index = 0;
    REQUIRE((errors.at(index++) == std::make_pair(SourceProfileValidator::Location::changeAddressLocationDeclaration, SourceProfileValidator::Error::missingPlaceholder)));
    REQUIRE((errors.at(index++) == std::make_pair(SourceProfileValidator::Location::byteDeclaration, SourceProfileValidator::Error::missingPlaceholder)));
    REQUIRE((errors.at(index++) == std::make_pair(SourceProfileValidator::Location::wordDeclaration, SourceProfileValidator::Error::missingPlaceholder)));
    REQUIRE((errors.at(index++) == std::make_pair(SourceProfileValidator::Location::addressDeclaration, SourceProfileValidator::Error::missingPlaceholder)));
    REQUIRE((errors.at(index++) == std::make_pair(SourceProfileValidator::Location::stringDeclaration, SourceProfileValidator::Error::missingPlaceholder)));
    REQUIRE((errors.at(index++) == std::make_pair(SourceProfileValidator::Location::constantDeclaration, SourceProfileValidator::Error::missingPlaceholder)));
    REQUIRE((errors.at(index++) == std::make_pair(SourceProfileValidator::Location::labelDeclaration, SourceProfileValidator::Error::missingPlaceholder)));
    REQUIRE((errors.at(index++) == std::make_pair(SourceProfileValidator::Location::commentDeclaration, SourceProfileValidator::Error::missingPlaceholder)));
    REQUIRE((errors.size() == index));
}

TEST_CASE("SourceProfileValidator, too many placeholders everywhere", "[SourceProfileValidatorTest]")
{
    // Given.
    const SourceGeneratorConfiguration configuration(
            "{x} org {x} ", "; {x} {x} {x} ", true, "{x} {x} db ", "{x} {x} dw {x} ",
            "dw {x}{x}{x}", "ds {x}{x}", "equ {x} {x}", "{x} {x}{x} {x} ", true, "asm", "bin", 8
    );
    const SourceProfile sourceProfile(configuration, "hello", false);

    // When.
    const auto errors = SourceProfileValidator::validate(sourceProfile);

    // Then.
    size_t index = 0;
    REQUIRE((errors.at(index++) == std::make_pair(SourceProfileValidator::Location::changeAddressLocationDeclaration, SourceProfileValidator::Error::tooManyPlaceholders)));
    REQUIRE((errors.at(index++) == std::make_pair(SourceProfileValidator::Location::byteDeclaration, SourceProfileValidator::Error::tooManyPlaceholders)));
    REQUIRE((errors.at(index++) == std::make_pair(SourceProfileValidator::Location::wordDeclaration, SourceProfileValidator::Error::tooManyPlaceholders)));
    REQUIRE((errors.at(index++) == std::make_pair(SourceProfileValidator::Location::addressDeclaration, SourceProfileValidator::Error::tooManyPlaceholders)));
    REQUIRE((errors.at(index++) == std::make_pair(SourceProfileValidator::Location::stringDeclaration, SourceProfileValidator::Error::tooManyPlaceholders)));
    REQUIRE((errors.at(index++) == std::make_pair(SourceProfileValidator::Location::constantDeclaration, SourceProfileValidator::Error::tooManyPlaceholders)));
    REQUIRE((errors.at(index++) == std::make_pair(SourceProfileValidator::Location::labelDeclaration, SourceProfileValidator::Error::tooManyPlaceholders)));
    REQUIRE((errors.at(index++) == std::make_pair(SourceProfileValidator::Location::commentDeclaration, SourceProfileValidator::Error::tooManyPlaceholders)));
    REQUIRE((errors.size() == index));
}

TEST_CASE("SourceProfileValidator, various errors", "[SourceProfileValidatorTest]")
{
    // Given.
    const SourceGeneratorConfiguration configuration(
            "{x} org {x} ", "; {x}", true, "{x} db ", "dw {x}",
            "dw {y}", "ds {x} aaa {x}",
            "equ", ":", true, ".asm", "bin", 50
    );
    const SourceProfile sourceProfile(configuration, "hello", false);

    // When.
    const auto errors = SourceProfileValidator::validate(sourceProfile);

    // Then.
    size_t index = 0;
    REQUIRE((errors.at(index++) == std::make_pair(SourceProfileValidator::Location::asmExtension, SourceProfileValidator::Error::mustNotStartWithDot)));

    REQUIRE((errors.at(index++) == std::make_pair(SourceProfileValidator::Location::tabulationSize, SourceProfileValidator::Error::invalidValue)));

    REQUIRE((errors.at(index++) == std::make_pair(SourceProfileValidator::Location::changeAddressLocationDeclaration, SourceProfileValidator::Error::tooManyPlaceholders)));
    REQUIRE((errors.at(index++) == std::make_pair(SourceProfileValidator::Location::addressDeclaration, SourceProfileValidator::Error::missingPlaceholder)));
    REQUIRE((errors.at(index++) == std::make_pair(SourceProfileValidator::Location::stringDeclaration, SourceProfileValidator::Error::tooManyPlaceholders)));
    REQUIRE((errors.at(index++) == std::make_pair(SourceProfileValidator::Location::constantDeclaration, SourceProfileValidator::Error::missingPlaceholder)));
    REQUIRE((errors.at(index++) == std::make_pair(SourceProfileValidator::Location::labelDeclaration, SourceProfileValidator::Error::missingPlaceholder)));
    REQUIRE((errors.size() == index));
}

}   // namespace arkostracker
