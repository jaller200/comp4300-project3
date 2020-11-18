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
}