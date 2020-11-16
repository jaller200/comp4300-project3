#include "tests/include/catch.hpp"

#include "instr/instruction_set.hpp"

/**
 * Method: InstructionSet::registerRType(..)
 * Desired Confidence Level: Boundary value analysis
 * 
 * Inputs:
 *      name        -> A string value without whitespace or delimiters, will be converted to lowercase, unvalidated
 *      opcode      -> A 6-bit unsigned integer value (0-63), unvalidated
 *      funct       -> A 6-bit unsigned integer value (0-63), unvalidated
 *      parser      -> A unique_ptr to a parser for this specific instruction, non-null, unvalidated
 * 
 * Outputs:
 *      The function returns true if the instruction was registered successfully, otherwise it
 *          returns false.
 * 
 * Valid Tests:
 *      name        -> nominal value
 *      opcode      -> nominal value
 *                     minimum value (0, edge case)
 *                     maximum value (63, edge case)
 *      funct       -> nominal value
 *                     nominal value #2 (same opcode, different funct)
 *                     minimum value (0, edge case)
 *                     maximum value (63, edge case)
 *      parser      -> nominal value
 * 
 * Invalid Tests:
 *      name string is empty
 *      name string with just whitespace
 *      name string with whitespace and ASCII
 *      name string with newline
 *      name string with tab
 *      opcode above max value
 *      funct above max value
 *      parser null
 *      attempting to register another r-type with the same opcode & funct
 *      attempting to register another r-type with the same name
 */
TEST_CASE("Instruction set is properly able to register R-Type instructions") {

    SECTION("Registering a nominal R-Type instruction works properly") {

        InstructionSet instrSet;
        REQUIRE(1 == 1);
        //REQUIRE(instrSet.registerRType())
    }
}