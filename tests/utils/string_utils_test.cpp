#include "catch.hpp"

#include "utils/string_utils.hpp"

/**
 * Method: StringUtils::ltrim(..)
 * Desired Confidence Level: Basic validation
 * 
 * Inputs:
 *      str     -> Any valid string, validated
 * 
 * Outputs:
 *      A string with no whitespace (tabs, tabs, etc.) at
 *      the start.
 * 
 * Valid Tests:
 *      str     -> a basic string with whitespace at the start
 *                 a basic string with whitespace both at the start and inside
 *                 a basic string with whitespace at the start and new line at the end
 *                 a basic string with tabs at the start
 *                 a basic string with a mixture of all possible whitespace types
 *                 a basic string with no whitespace at the front
 * 
 * Invalid Tests:
 *      None
 */
TEST_CASE("Left trimming a string works properly") {

    SECTION("Left trimming a nominal string with whitespace at the start removes the starting whitespace") {
        std::string result = StringUtils::ltrim("   test");
        std::string expected = "test";
        REQUIRE(result == expected);
    }

    SECTION("Left trimming a string with whitespace at the start and inside only removes the starting whitespace") {
        std::string result = StringUtils::ltrim("   this is a test");
        std::string expected = "this is a test";
        REQUIRE(result == expected);
    }

    SECTION("Left trimmin a string with whitespace at the start and a new line at the end only removes the starting whitespace") {
        std::string result = StringUtils::ltrim("   this is a test\n");
        std::string expected = "this is a test\n";
        REQUIRE(result == expected);
    }

    SECTION("Left trimming a string with tabs at the start removes the tabs") {
        std::string result = StringUtils::ltrim("\t\t\tthis is a test");
        std::string expected = "this is a test";
        REQUIRE(result == expected);
    }

    SECTION("Left trimming a string with all possible whitespace before removes the whitespace") {
        std::string result = StringUtils::ltrim(" \f\n\r\t\vthis is a test");
        std::string expected = "this is a test";
        REQUIRE(result == expected);
    }

    SECTION("Left trimming a string with no whitespace at the start just returns the string") {
        std::string result = StringUtils::ltrim("this is a test");
        std::string expected = "this is a test";
        REQUIRE(result == expected);
    }
}

/**
 * Method: StringUtils::rtrim(..)
 * Desired Confidence Level: Basic validation
 * 
 * Inputs:
 *      str     -> Any valid string, validated
 * 
 * Outputs:
 *      A string with no whitespace (tabs, tabs, etc.) at
 *      the end.
 * 
 * Valid Tests:
 *      str     -> a basic string with whitespace at the end
 *                 a basic string with whitespace both at the end and inside
 *                 a basic string with whitepace at the start and the end
 *                 a basic string with tabs at the end
 *                 a basic string with a mixture of all possible whitespace types at the end
 *                 a basic string with no whitespace at the end
 * 
 * Invalid Tests:
 *      None
 */
TEST_CASE("Right trimming a string works properly") {

    SECTION("Right trimming a nominal string with whitespace at the end removes the ending whitespace") {
        std::string result = StringUtils::rtrim("test   ");
        std::string expected = "test";
        REQUIRE(result == expected);
    }

    SECTION("Right trimming a string with whitespace at the end and inside removes only the ending whitespace") {
        std::string result = StringUtils::rtrim("this is a test   ");
        std::string expected = "this is a test";
        REQUIRE(result == expected);
    }

    SECTION("Right trimming a string with whitespace at the start and end only removes the ending whitespace") {
        std::string result = StringUtils::rtrim("  this is a test  ");
        std::string expected = "  this is a test";
        REQUIRE(result == expected);
    }

    SECTION("Right trimming a string with tabs at the end removes the tabs") {
        std::string result = StringUtils::rtrim("this is a test\t\t");
        std::string expected = "this is a test";
        REQUIRE(result == expected);
    }

    SECTION("Right trimming a string with all possible whitespace at the end removes it") {
        std::string result = StringUtils::rtrim("this is a test \f\n\r\t\v");
        std::string expected = "this is a test";
        REQUIRE(result == expected);
    }

    SECTION("Right trimming a string with no whitespace at the end just returns the string") {
        std::string result = StringUtils::rtrim("this is a test");
        std::string expected = "this is a test";
        REQUIRE(result == expected);
    }
}

/**
 * Method: StringUtils::trim(..)
 * Desired Confidence Level: Basic validation
 * 
 * Inputs:
 *      str     -> Any valid string, validated
 * 
 * Outputs:
 *      A string with no whitespace (tabs, tabs, etc.) at
 *      the start or end.
 * 
 * Valid Tests:
 *      str     -> a basic string with whitespace at the start
 *                 a basic string with whitespace at the end
 *                 a basic string with whitespace both at the start and inside
 *                 a basic string with whitespace both at the end and inside
 *                 a basic string with whitepace at the start and the end
 *                 a basic string with a mixture of all possible whitespace types at the start and end
 *                 a basic string with no whitespace at the start or end
 * 
 * Invalid Tests:
 *      None
 */
TEST_CASE("Trimming a string works properly") {

    SECTION("Trimming a nominal string with whitespace at the start removes the starting whitespace") {
        std::string result = StringUtils::trim("  test");
        std::string expected = "test";
        REQUIRE(result == expected);
    }

    SECTION("Trimming a nominal string with whitespace at the end removes the ending whitespace") {
        std::string result = StringUtils::trim("test  ");
        std::string expected = "test";
        REQUIRE(result == expected);
    }

    SECTION("Trimming a string with whitespace at the start and inside removes the starting whitespace") {
        std::string result = StringUtils::trim("  this is a test");
        std::string expected = "this is a test";
        REQUIRE(result == expected);
    }

    SECTION("Trimming a string with whitespace at the end and inside removes the ending whitespace") {
        std::string result = StringUtils::trim("this is a test  ");
        std::string expected = "this is a test";
        REQUIRE(result == expected);
    }

    SECTION("Trimming a string with whitespace at both the start and end removes the starting and ending whitespace") {
        std::string result = StringUtils::trim("  this is a test  ");
        std::string expected = "this is a test";
        REQUIRE(result == expected);
    }

    SECTION("Trimming a string with all possible whitespace at the start and end removes the whitespace") {
        std::string result = StringUtils::trim(" \f\n\r\t\vthis is a test \f\n\r\t\v");
        std::string expected = "this is a test";
        REQUIRE(result == expected);
    }

    SECTION("Trimming a string with no whitespace at the start or end just returns the string") {
        std::string result = StringUtils::trim("this is a test");
        std::string expected = "this is a test";
        REQUIRE(result == expected);
    }
}