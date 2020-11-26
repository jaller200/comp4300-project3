#include "catch.hpp"

#include "registers/register_bank.hpp"

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
 *      attempting to write to register 0
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

    SECTION("Writing and reading to register 1 works properly") {

        RegisterBank rb;
        REQUIRE(rb.writeRegister(1, 100) == true);

        word_t value;
        REQUIRE(rb.readRegister(1, value) == true);
        REQUIRE(value == 100);
    }

    SECTION("Writing register 0 fails, and reading register 0 succeeds") {

        RegisterBank rb;
        REQUIRE_FALSE(rb.writeRegister(0, 100));

        word_t value = 100;
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
        REQUIRE_FALSE(rb.writeRegister(32, 100));

        word_t value = 100;
        REQUIRE_FALSE(rb.readRegister(32, value));
        REQUIRE(value == 100);
    }
}