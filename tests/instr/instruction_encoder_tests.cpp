#include "catch.hpp"

#include "exception/illegal_encode_error.hpp"
#include "instr/instruction.hpp"
#include "instr/instruction_encoder.hpp"
#include "instr/instruction_type.hpp"

#include <exception>

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
 * 
 * Valid Outputs:
 *      All tests return valid 32-bit non-zero integers for r-type, i-type, and j-type
 *      All tests for unknown type return 0x00
 * 
 * Invalid Tests:
 *      instruction with psudeo type set
 *      instruction with unknown type set
 * 
 * Invalid Outputs:
 *      Both cases throw an IllegalEncodeError
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

    SECTION("R-type instruction with all minimum fields for just R-type is properly encoded") {

        Instruction instr;
        instr.setType(InstructionType::R_FORMAT);
        instr.setOpcode(0);
        instr.setRs(0);
        instr.setRt(0);
        instr.setRd(0);
        instr.setShamt(0);
        instr.setFunct(0);

        // Other types set to non-zero
        instr.setAddr(10);
        instr.setImmediate(10);

        Instruction::instr_t expectedOutput = 0x00000000;
        REQUIRE(InstructionEncoder::encode(instr) == expectedOutput);
    }

    SECTION("R-type instruction with all maximum fields is properly encoded") {

        Instruction instr;
        instr.setType(InstructionType::R_FORMAT);
        instr.setAddr(67108863);
        instr.setFunct(63);
        instr.setImmediate(65535);
        instr.setOpcode(63);
        instr.setRd(31);
        instr.setRs(31);
        instr.setRt(31);
        instr.setShamt(31);

        Instruction::instr_t expectedOutput = 0xFFFFFFFF;
        REQUIRE(InstructionEncoder::encode(instr) == expectedOutput);
    }

    SECTION("R-type instruction with all minimum fields is properly encoded") {

        Instruction instr;
        instr.setType(InstructionType::R_FORMAT);
        instr.setAddr(0);
        instr.setFunct(0);
        instr.setImmediate(0);
        instr.setOpcode(0);
        instr.setRd(0);
        instr.setRs(0);
        instr.setRt(0);
        instr.setShamt(0);

        Instruction::instr_t expectedOutput = 0x00000000;
        REQUIRE(InstructionEncoder::encode(instr) == expectedOutput);
    }


    // MARK: -- I-Type Instructions
    SECTION("I-type instruction with non-zero fields is properly encoded") {

        Instruction instr;
        instr.setType(InstructionType::I_FORMAT);
        instr.setOpcode(10);
        instr.setRs(1);
        instr.setRt(2);
        instr.setImmediate(100);

        Instruction::instr_t expectedOutput = 0x64104A;
        REQUIRE(InstructionEncoder::encode(instr) == expectedOutput);
    }

    SECTION("I-type instruction with all maximum fields for just I-type is properly encoded") {

        Instruction instr;
        instr.setType(InstructionType::I_FORMAT);
        instr.setOpcode(63);
        instr.setRs(31);
        instr.setRt(31);
        instr.setImmediate(65535);

        // Other types set to non-zero
        instr.setAddr(10);
        instr.setFunct(10);
        instr.setRd(10);
        instr.setShamt(10);

        Instruction::instr_t expectedOutput = 0xFFFFFFFF;
        REQUIRE(InstructionEncoder::encode(instr) == expectedOutput);
    }

    SECTION("I-type instruction with all minimum fields for just I-type is properly encoded") {

        Instruction instr;
        instr.setType(InstructionType::I_FORMAT);
        instr.setOpcode(0);
        instr.setRs(0);
        instr.setRt(0);
        instr.setImmediate(0);

        // Other types set to non-zero
        instr.setAddr(10);
        instr.setFunct(10);
        instr.setRd(10);
        instr.setShamt(10);

        Instruction::instr_t expectedOutput = 0x00000000;
        REQUIRE(InstructionEncoder::encode(instr) == expectedOutput);
    }

    SECTION("I-type instruction with all maximum fields is properly encoded") {

        Instruction instr;
        instr.setType(InstructionType::I_FORMAT);
        instr.setAddr(67108863);
        instr.setFunct(63);
        instr.setImmediate(65535);
        instr.setOpcode(63);
        instr.setRd(31);
        instr.setRs(31);
        instr.setRt(31);
        instr.setShamt(31);

        Instruction::instr_t expectedOutput = 0xFFFFFFFF;
        REQUIRE(InstructionEncoder::encode(instr) == expectedOutput);
    }

    SECTION("I-type instruction with all minimum fields is properly encoded") {

        Instruction instr;
        instr.setType(InstructionType::R_FORMAT);
        instr.setAddr(0);
        instr.setFunct(0);
        instr.setImmediate(0);
        instr.setOpcode(0);
        instr.setRd(0);
        instr.setRs(0);
        instr.setRt(0);
        instr.setShamt(0);

        Instruction::instr_t expectedOutput = 0x00000000;
        REQUIRE(InstructionEncoder::encode(instr) == expectedOutput);
    }


    // MARK: -- J-Type Instructions
    SECTION("J-type instruction with non-zero fields is properly encoded") {

        Instruction instr;
        instr.setType(InstructionType::J_FORMAT);
        instr.setOpcode(10);
        instr.setAddr(100);

        Instruction::instr_t expectedOutput = 0x190A;
        REQUIRE(InstructionEncoder::encode(instr) == expectedOutput);
    }

    SECTION("J-type instruction with all maximum fields for just J-type is properly encoded") {

        Instruction instr;
        instr.setType(InstructionType::J_FORMAT);
        instr.setOpcode(63);
        instr.setAddr(67108863);

        // Other types set to non-zero
        instr.setFunct(10);
        instr.setImmediate(10);
        instr.setRd(10);
        instr.setRs(10);
        instr.setRt(10);
        instr.setShamt(10);

        Instruction::instr_t expectedOutput = 0xFFFFFFFF;
        REQUIRE(InstructionEncoder::encode(instr) == expectedOutput);
    }

    SECTION("J-type instruction with all minimum fields for just J-type is properly encoded") {

        Instruction instr;
        instr.setType(InstructionType::J_FORMAT);
        instr.setOpcode(0);
        instr.setAddr(0);

        // Other types set to non-zero
        instr.setFunct(10);
        instr.setImmediate(10);
        instr.setRd(10);
        instr.setRs(10);
        instr.setRt(10);
        instr.setShamt(10);

        Instruction::instr_t expectedOutput = 0x00000000;
        REQUIRE(InstructionEncoder::encode(instr) == expectedOutput);
    }

    SECTION("J-type instruction with all maximum fields is properly encoded") {

        Instruction instr;
        instr.setType(InstructionType::J_FORMAT);
        instr.setAddr(67108863);
        instr.setFunct(63);
        instr.setImmediate(65535);
        instr.setOpcode(63);
        instr.setRd(31);
        instr.setRs(31);
        instr.setRt(31);
        instr.setShamt(31);

        Instruction::instr_t expectedOutput = 0xFFFFFFFF;
        REQUIRE(InstructionEncoder::encode(instr) == expectedOutput);
    }

    SECTION("J-type instruction with all minimum fields is properly encoded") {

        Instruction instr;
        instr.setType(InstructionType::J_FORMAT);
        instr.setAddr(0);
        instr.setFunct(0);
        instr.setImmediate(0);
        instr.setOpcode(0);
        instr.setRd(0);
        instr.setRs(0);
        instr.setRt(0);
        instr.setShamt(0);

        Instruction::instr_t expectedOutput = 0x00000000;
        REQUIRE(InstructionEncoder::encode(instr) == expectedOutput);
    }


    // MARK: -- Psuedo / Unknown Type
    SECTION("Psuedo instructions throw an encoding error") {

        Instruction instr;
        instr.setType(InstructionType::PSUEDO);
        instr.setOpcode(10);

        REQUIRE_THROWS_AS(InstructionEncoder::encode(instr), IllegalEncodeError);
    }

    SECTION("Unknown instructions throw an encoding error") {

        Instruction instr;
        instr.setType(InstructionType::UNKNOWN);
        instr.setOpcode(11);

        REQUIRE_THROWS_AS(InstructionEncoder::encode(instr), IllegalEncodeError);
    }
}