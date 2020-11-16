#include "tests/include/catch.hpp"

#include "instr/instruction.hpp"
#include "instr/instruction_encoder.hpp"
#include "instr/instruction_type.hpp"

/**
 * Method: InstructionEncoder::encode(..)
 * Desired Confidence Level: edge and corner values analysis
 * 
 * Inputs:
 *      instr       -> An instruction reference, validated (not null)
 * 
 * Outputs:
 *      A 32-bit instruction
 * 
 * Valid Tests:
 *      instruction with r-type set and non-zero fields
 *      instruction with r-type set to all maximum fields for just r-type, non-zero otherwise (corner case)
 *      instruction with r-type set to all minimum fields for just r-type, non-zero otherwise (corner case)
 *      instruction with r-type set to all maximum fields (edge case)
 *      instruction with r-type set to all minimum fields (edge case)
 *      instruction with i-type set and non-zero fields
 *      instruction with i-type set and maximum fields for just i-type, non-zero otherwise (corner case)
 *      instruction with i-type set and minimum fields for just i-type, non-zero otherwise (corner case)
 *      instruction with i-type set and maximum fields (edge case)
 *      instruction with i-type set and minimum fields (edge case)
 *      instruction with j-type set and non-zero fields
 *      instruction with j-type set and maximum fields for just j-type, non-zero otherwise (corner case)
 *      instruction with j-type set and minimum fields for just j-type, non-zero otherwise (corner case)
 *      instruction with j-type set and maximum fields (edge case)
 *      instruction with j-type set and minimum fields (edge case)
 *      instruction with unknown type set and non-zero fields
 *      instruction with unknown type set and maximum fields (edge case)
 *      instruction with unknown type set and minimum fields (edge case)
 * 
 * Valid Outputs:
 *      All tests return valid 32-bit non-zero integers for r-type, i-type, and j-type
 *      All tests for unknown type return 0x00
 * 
 * Invalid Tests:
 *      None
 */
TEST_CASE("Encode method properly encodes instruction structure to 32-bit value") {

    // MARK: -- R-Type Instructions
    SECTION("R-type instruction with non-zero fields is properly encoded") {

        Instruction instr;
        instr.setType(InstructionType::R_FORMAT);
        instr.setOpcode(10);
        instr.setRs(1);
        instr.setRt(2);
        instr.setRd(3);
        instr.setShamt(5);
        instr.setFunct(10);

        Instruction::instr_t expectedOutput = 0x28A3104A;
        REQUIRE(InstructionEncoder::encode(instr) == expectedOutput);
    }

    SECTION("R-type instruction with all maximum fields for just R-type is properly encoded") {

        Instruction instr;
        instr.setType(InstructionType::R_FORMAT);
        instr.setOpcode(63);
        instr.setRs(31);
        instr.setRt(31);
        instr.setRd(31);
        instr.setShamt(31);
        instr.setFunct(63);

        // Other types set to non-zero
        instr.setAddr(10);
        instr.setImmediate(10);

        Instruction::instr_t expectedOutput = 0xFFFFFFFF;
        REQUIRE(InstructionEncoder::encode(instr) == expectedOutput);
    }
}