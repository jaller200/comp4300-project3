#include "catch.hpp"

#include "exception/illegal_encode_error.hpp"
#include "instr/instruction.hpp"
#include "instr/instruction_encoder.hpp"
#include "instr/instruction_type.hpp"

#include <exception>

/**
 * Method: InstructionEncoder::decode(..)
 * Desired Confidence Level: boundary value analysis
 * 
 * Inputs:
 *      instr       -> A 32-bit instruction value, mandatory, validated
 *      type        -> An instruction type of R_FORMAT, I_FORMAT, J_FORMAT, mandatory, unvalidated
 * 
 * Outputs:
 *      In the case of success, an instruction structure. Otherwise, an IllegalEncodeError is thrown
 * 
 * Valid Tests:
 *      instruction with nominal R-Type
 *      instruction with minimal R-Type bits (all 0s)
 *      instruction with maximum R-Type bits (all 1s)
 *      instruction with nominal I-Type
 *      instruction with minimal I-Type bits (all 0s)
 *      instruction with maximum I-Type bits (all 1s)
 *      instruction with nominal J-Type
 *      instruction with minimal J-Type bits (all 0s)
 *      instruction with maximum J-Type bits (all 1s)
 * 
 * Valid Outputs:
 *      All outputs should be valid instructions with the correct fields set
 * 
 * Invalid Tests:
 *      instruction with psuedo type
 *      instruction with unknown type
 */
TEST_CASE("Decode method properly decodes instructions") {

    // MARK: -- Valid R-Type Tests

    SECTION("Decoding a nominal R-Type instruction works properly") {
        
        Instruction::instr_t instr = 0x7A8D62CA;
        Instruction output = InstructionEncoder::decode(instr, InstructionType::R_FORMAT);

        REQUIRE(output.getOpcode() == 10);
        REQUIRE(output.getRs() == 11);
        REQUIRE(output.getRt() == 12);
        REQUIRE(output.getRd() == 13);
        REQUIRE(output.getShamt() == 20);
        REQUIRE(output.getFunct() == 30);
    }

    SECTION("Decoding a minimal R-Type instruction works properly") {
        
        Instruction::instr_t instr = 0x00000000;
        Instruction output = InstructionEncoder::decode(instr, InstructionType::R_FORMAT);

        REQUIRE(output.getOpcode() == 0);
        REQUIRE(output.getRs() == 0);
        REQUIRE(output.getRt() == 0);
        REQUIRE(output.getRd() == 0);
        REQUIRE(output.getShamt() == 0);
        REQUIRE(output.getFunct() == 0);
    }

    SECTION("Decoding a maximal R-Type instruction works properly") {
        
        Instruction::instr_t instr = 0xFFFFFFFF;
        Instruction output = InstructionEncoder::decode(instr, InstructionType::R_FORMAT);

        REQUIRE(output.getOpcode() == 63);
        REQUIRE(output.getRs() == 31);
        REQUIRE(output.getRt() == 31);
        REQUIRE(output.getRd() == 31);
        REQUIRE(output.getShamt() == 31);
        REQUIRE(output.getFunct() == 63);
    }


    // MARK: -- Valid I-Type Tests

    SECTION("Decoding a nominal I-Type instruction works properly") {
        
        // 0000000001100100 01100 01011 001010

        Instruction::instr_t instr = 0x006462CA;
        Instruction output = InstructionEncoder::decode(instr, InstructionType::I_FORMAT);

        REQUIRE(output.getOpcode() == 10);
        REQUIRE(output.getRs() == 11);
        REQUIRE(output.getRt() == 12);
        REQUIRE(output.getImmediate() == 100);
    }

    SECTION("Decoding a minimal I-Type instruction works properly") {
        
        Instruction::instr_t instr = 0x00000000;
        Instruction output = InstructionEncoder::decode(instr, InstructionType::I_FORMAT);

        REQUIRE(output.getOpcode() == 0);
        REQUIRE(output.getRs() == 0);
        REQUIRE(output.getRt() == 0);
        REQUIRE(output.getImmediate() == 0);
    }

    SECTION("Decoding a nominal I-Type instruction works properly") {
        
        Instruction::instr_t instr = 0xFFFFFFFF;
        Instruction output = InstructionEncoder::decode(instr, InstructionType::I_FORMAT);

        REQUIRE(output.getOpcode() == 63);
        REQUIRE(output.getRs() == 31);
        REQUIRE(output.getRt() == 31);
        REQUIRE(output.getImmediate() == 65535);
    }


    // MARK: -- Valid J-Type Tests

    SECTION("Decoding a nominal J-Type instruction works properly") {
        
        Instruction::instr_t instr = 0x0000FA0A;
        Instruction output = InstructionEncoder::decode(instr, InstructionType::J_FORMAT);

        REQUIRE(output.getOpcode() == 10);
        REQUIRE(output.getAddr() == 1000);
    }

    SECTION("Decoding a minimal J-Type instruction works properly") {
        
        Instruction::instr_t instr = 0x00000000;
        Instruction output = InstructionEncoder::decode(instr, InstructionType::J_FORMAT);

        REQUIRE(output.getOpcode() == 0);
        REQUIRE(output.getAddr() == 0);
    }

    SECTION("Decoding a nominal J-Type instruction works properly") {
        
        Instruction::instr_t instr = 0xFFFFFFFF;
        Instruction output = InstructionEncoder::decode(instr, InstructionType::J_FORMAT);

        REQUIRE(output.getOpcode() == 63);
        REQUIRE(output.getAddr() == 67108863);
    }


    // MARK: -- Invalid Tests
    
    SECTION("Decoding a psuedo instruction type fails") {

        Instruction::instr_t instr = 0x19D55CAF;
        REQUIRE_THROWS_AS(InstructionEncoder::decode(instr, InstructionType::PSUEDO), IllegalEncodeError);
    }

    SECTION("Decoding an unknown instruction type fails") {

        Instruction::instr_t instr = 0x19D55CAF;
        REQUIRE_THROWS_AS(InstructionEncoder::decode(instr, InstructionType::UNKNOWN), IllegalEncodeError);
    }
}

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