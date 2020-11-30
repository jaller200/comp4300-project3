#include "catch.hpp"

#include "registers/register_bank.hpp"

/**
 * Method: RegisterBank::getRegister(..)
 * Desired Confidence Level: Boundary value analysis
 * 
 * Inputs:
 *      str         -> A valid, non-zero-length string without whitespace starting with "$", mandatory, unvalidated
 * 
 * Outputs:
 *      The register number (0-31) or -1
 * 
 * Valid Tests:
 *      str         -> nominal number value ($5)
 *                     nominal name value ($k0)
 *                     nominal name value uppercase ($K0)
 *                     minimum number value ($0)
 *                     maximum number value ($31)
 *                     zero register value ($zero)
 *                     zero register value uppercase ($ZeRo)
 *                     ra register value ($ra, just for peace of mind)
 * 
 * Invalid Tests:
 *      str is empty
 *      str contains only whitespace / delimiters
 *      str contains whitespace with valid value
 *      str does not start with "$"
 *      string contains out of bounds register number
 *      string contains invalid name
 *      string contains floating point
 */
TEST_CASE("Converting a string to a register number works properly") {

    // MARK: -- Valid Tests

    SECTION("Converting a nominal number value to a register number works properly") {
        REQUIRE(RegisterBank::getRegister("$5") == 5);
    }

    SECTION("Converting a nominal name value to a register number works properly") {
        REQUIRE(RegisterBank::getRegister("$k0") == 26);
    }

    SECTION("Converting a nominal name value with uppercase to a register number works properly") {
        REQUIRE(RegisterBank::getRegister("$K0") == 26);
    }

    SECTION("Converting a minimum number value to a register number works properly") {
        REQUIRE(RegisterBank::getRegister("$0") == 0);
    }

    SECTION("Converting a maximum number value to a register number works properly") {
        REQUIRE(RegisterBank::getRegister("$31") == 31);
    }

    SECTION("Converting the zero register value to a register number works properly") {
        REQUIRE(RegisterBank::getRegister("$zero") == 0);
    }

    SECTION("Converting the zero register value with some uppercase to a register number works properly") {
        REQUIRE(RegisterBank::getRegister("$ZeRo") == 0);
    }

    SECTION("Converting the ra register to a register number works properly") {
        REQUIRE(RegisterBank::getRegister("$ra") == 31);
    }


    // MARK: -- Invalid Tests

    SECTION("Converting an empty string to a register number fails") {
        REQUIRE(RegisterBank::getRegister("") == -1);
    }

    SECTION("Converting a string with only whitespace to a register number fails") {
        REQUIRE(RegisterBank::getRegister("   \t\n  ") == -1);
    }

    SECTION("Converting a string with whitespace and a valid register fails") {
        REQUIRE(RegisterBank::getRegister("   \t$0  ") == -1);
    }

    SECTION("Converting a string that does not start with '$' to a register fails") {
        REQUIRE(RegisterBank::getRegister("zero") == -1);
    }

    SECTION("Converting a string that contains an out of bound register number fails") {
        REQUIRE(RegisterBank::getRegister("$32") == -1);
    }

    SECTION("Converting a string that contains an invalid name fails") {
        REQUIRE(RegisterBank::getRegister("$bobjoe") == -1);
    }

    SECTION("Converting a string that contains a floating point value fails") {
        REQUIRE(RegisterBank::getRegister("$3.14") == -1);
    }
}

/**
 * Method: RegisterBank::writeRegister(..), RegisterBank::readRegister(..)
 * Desired Confidence Level: Boundary value analysis
 * 
 * Inputs:
 *      num         -> A number between 0-31 (read), 1-31 (write), mandatory, unvalidated
 *      value       -> A 32-bit value to store register contents or
 *                      write to the register, mandatory, validated
 * 
 * Outputs:
 *      The function returns true if the value was read / written successfully, false otherwise
 * 
 * Notes:
 *      We are testing both together because they are essentially getters / setters,
 *          but with a bit of logic.
 * 
  * Valid Tests:
 *      num         -> nominal value (10)
 *                     minimum value (0)
 *                     maximum value (31)
 *      value       -> nominal value
 *                     minimum value (0), write
 *                     maximum value (2^32-1), write
 * 
 * Invalid Tests:
 *      num is immediate outside the boundary (32)
 *      num is far outside the boundary (60)
 *      
 */
TEST_CASE("Register bank can be written to / read from properly") {

    // MARK: -- Valid Tests

    SECTION("Writing and reading a nominal value works properly") {

        RegisterBank rb;
        REQUIRE(rb.writeRegister(10, 100) == true);

        word_t value;
        REQUIRE(rb.readRegister(10, value) == true);
        REQUIRE(value == 100);
    }

    SECTION("Writing and reading a minimum value works properly") {

        RegisterBank rb;
        REQUIRE(rb.writeRegister(10, 0) == true);
        
        word_t value = 100;
        REQUIRE(rb.readRegister(10, value) == true);
        REQUIRE(value == 0);
    }

    SECTION("Writing and reading a maximum value works properly") {

        RegisterBank rb;
        REQUIRE(rb.writeRegister(10, 2147483647) == true);

        word_t value = 100;
        REQUIRE(rb.readRegister(10, value) == true);
        REQUIRE(value == 2147483647);
    }

    SECTION("Writing and reading to register 0 works properly (hardcoded to zero)") {

        RegisterBank rb;
        REQUIRE(rb.writeRegister(0, 100) == true);

        word_t value;
        REQUIRE(rb.readRegister(0, value) == true);
        REQUIRE(value == 0);
    }

    
    // MARK: -- Invalid Tests

    SECTION("Writing and reading a register right outside the boundary fails") {

        RegisterBank rb;
        REQUIRE_FALSE(rb.writeRegister(32, 100));

        word_t value = 100;
        REQUIRE_FALSE(rb.readRegister(32, value));
        REQUIRE(value == 100);
    }

    SECTION("Writing and reading a register far outside the boundary fails") {

        RegisterBank rb;
        REQUIRE_FALSE(rb.writeRegister(64, 100));

        word_t value = 100;
        REQUIRE_FALSE(rb.readRegister(64, value));
        REQUIRE(value == 100);
    }
}
