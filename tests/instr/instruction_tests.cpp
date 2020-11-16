#include "catch.hpp"

#include "instr/instruction.hpp"
#include "instr/instruction_type.hpp"

/**
 * Method: Instruction::(setters)
 * Desired confidence level: boundary value analysis
 * 
 * Inputs:
 *      addr        -> A 32-bit integer within the range of 0 to 67,108,863 (2^26-1), unvalidated
 *      funct       -> A 32-bit integer within the range of 0 to 63 (2^6-1), unvalidated
 *      immediate   -> A 32-bit integer within the range of 0 to 65,535 (2^16-1), unvalidated
 *      opcode      -> A 32-bit integer within the range of 0 to 63 (2^6-1), unvalidated
 *      rd          -> A 32-bit integer within the range of 0 to 31 (2^5-1), unvalidated
 *      rs          -> A 32-bit integer within the range of 0 to 31 (2^5-1), unvalidated
 *      rt          -> A 32-bit integer within the range of 0 to 31 (2^5-1), unvalidated
 *      shamt       -> A 32-bit integer within the range of 0 to 31 (2^5-1), unvalidated
 *
 * Inputs (unnecessary to test):
 *      type        -> A simple type, validated
 * 
 * Valid Tests:
 *      All types with a nominal value (something in the range)
 *      All types with a minimum valid value (0)
 *      All types with a maximum valid value
 * 
 * Valid Outputs:
 *      All types return true and values return what they were set to
 * 
 * Invalid Tests:
 *      All types with a value one beyond their max (since values are unsigned) return false
 */
TEST_CASE("Instructions properly observe variable limits", "[instruction]") {

    // MARK: -- "addr" tests
    SECTION("Returns success and valid value when setting addr to a nominal value") {

        Instruction instr;
        REQUIRE(instr.setAddr(100) == true);
        REQUIRE(instr.getAddr() == 100);
    }

    SECTION("Returns success and valid value when setting addr to 0") {

        Instruction instr;
        REQUIRE(instr.setAddr(0) == true);
        REQUIRE(instr.getAddr() == 0);
    }

    SECTION("Returns success and valid value when setting addr to max (67,108,863)") {

        Instruction instr;  
        REQUIRE(instr.setAddr(67108863) == true);
        REQUIRE(instr.getAddr() == 67108863);
    }

    SECTION("Fails when setting address to max+1 (67,108,864)") {

        Instruction instr;
        REQUIRE(instr.setAddr(67108864) == false);
        REQUIRE(instr.getAddr() == 0);
    }


    // MARK: -- "funct" tests
    SECTION("Returns success and valid value when setting funct to a nominal value") {

        Instruction instr;
        REQUIRE(instr.setFunct(10) == true);
        REQUIRE(instr.getFunct() == 10);
    }

    SECTION("Returns success and valid value when setting funct to 0") {

        Instruction instr;
        REQUIRE(instr.setFunct(0) == true);
        REQUIRE(instr.getFunct() == 0);
    }

    SECTION("Returns success and valid value when setting funct to max (63)") {

        Instruction instr;
        REQUIRE(instr.setFunct(63) == true);
        REQUIRE(instr.getFunct() == 63);
    }

    SECTION("Fails when setting address to max+1 (67,108,864)") {

        Instruction instr;
        REQUIRE(instr.setFunct(64) == false);
        REQUIRE(instr.getFunct() == 0);
    }


    // MARK: -- "immediate" tests
    SECTION("Returns success and valid value when setting immediate to a nominal value") {

        Instruction instr;
        REQUIRE(instr.setImmediate(100) == true);
        REQUIRE(instr.getImmediate() == 100);
    }

    SECTION("Returns success and valid value when setting immediate to 0") {

        Instruction instr;
        REQUIRE(instr.setImmediate(0) == true);
        REQUIRE(instr.getImmediate() == 0);
    }

    SECTION("Returns success and valid value when setting immediate to max (65,535)") {

        Instruction instr;
        REQUIRE(instr.setImmediate(65535) == true);
        REQUIRE(instr.getImmediate() == 65535);
    }

    SECTION("Fails when setting immediate to max+1 (65,536)") {

        Instruction instr;
        REQUIRE(instr.setImmediate(65536) == false);
        REQUIRE(instr.getImmediate() == 0);
    }


    // MARK: -- "opcode" tests
    SECTION("Returns success and valid value when setting opcode to a nominal value") {

        Instruction instr;
        REQUIRE(instr.setOpcode(30) == true);
        REQUIRE(instr.getOpcode() == 30);
    }

    SECTION("Returns success and valid value when setting opcode to 0") {

        Instruction instr;
        REQUIRE(instr.setOpcode(0) == true);
        REQUIRE(instr.getOpcode() == 0);
    }

    SECTION("Returns success and valid value when setting opcode to max (63)") {

        Instruction instr;
        REQUIRE(instr.setOpcode(63) == true);
        REQUIRE(instr.getOpcode() == 63);
    }

    SECTION("Fails when setting opcode to max+1 (64)") {

        Instruction instr;
        REQUIRE(instr.setOpcode(64) == false);
        REQUIRE(instr.getOpcode() == 0);
    }


    // MARK: -- "rd" tests
    SECTION("Returns success and valid value when setting rd to a nominal value") {

        Instruction instr;
        REQUIRE(instr.setRd(10) == true);
        REQUIRE(instr.getRd() == 10);
    }

    SECTION("Returns success and valid value when setting rd to 0") {

        Instruction instr;
        REQUIRE(instr.setRd(0) == true);
        REQUIRE(instr.getRd() == 0);
    }

    SECTION("Returns success and valid value when setting rd to max (31)") {

        Instruction instr;
        REQUIRE(instr.setRd(31) == true);
        REQUIRE(instr.getRd() == 31);
    }

    SECTION("Fails when setting rd to max+1 (32)") {

        Instruction instr;
        REQUIRE(instr.setRd(32) == false);
        REQUIRE(instr.getRd() == 0);
    }


    // MARK: -- "rs" tests
    SECTION("Returns success and valid value when setting rs to a nominal value") {

        Instruction instr;
        REQUIRE(instr.setRs(10) == true);
        REQUIRE(instr.getRs() == 10);
    }

    SECTION("Returns success and valid value when setting rs to 0") {

        Instruction instr;
        REQUIRE(instr.setRs(0) == true);
        REQUIRE(instr.getRs() == 0);
    }

    SECTION("Returns success and valid value when setting rs to max (31)") {

        Instruction instr;
        REQUIRE(instr.setRs(31) == true);
        REQUIRE(instr.getRs() == 31);
    }

    SECTION("Fails when setting rs to max+1 (32)") {

        Instruction instr;
        REQUIRE(instr.setRs(32) == false);
        REQUIRE(instr.getRs() == 0);
    }


    // MARK: -- "rt" tests
    SECTION("Returns success and valid value when setting rt to a nominal value") {

        Instruction instr;
        REQUIRE(instr.setRt(10) == true);
        REQUIRE(instr.getRt() == 10);
    }

    SECTION("Returns success and valid value when setting rt to 0") {

        Instruction instr;
        REQUIRE(instr.setRt(0) == true);
        REQUIRE(instr.getRt() == 0);
    }

    SECTION("Returns success and valid value when setting rt to max (31)") {

        Instruction instr;
        REQUIRE(instr.setRt(31) == true);
        REQUIRE(instr.getRt() == 31);
    }

    SECTION("Fails when setting rt to max+1 (32)") {

        Instruction instr;
        REQUIRE(instr.setRt(32) == false);
        REQUIRE(instr.getRt() == 0);
    }


    // MARK: -- "shamt" tests
    SECTION("Returns success and valid value when setting shamt to a nominal value") {

        Instruction instr;
        REQUIRE(instr.setShamt(10) == true);
        REQUIRE(instr.getShamt() == 10);
    }

    SECTION("Returns success and valid value when setting shamt to 0") {

        Instruction instr;
        REQUIRE(instr.setShamt(0) == true);
        REQUIRE(instr.getShamt() == 0);
    }

    SECTION("Returns success and valid value when setting shamt to max (31)") {

        Instruction instr;
        REQUIRE(instr.setShamt(31) == true);
        REQUIRE(instr.getShamt() == 31);
    }

    SECTION("Fails when setting shamt to max+1 (32)") {

        Instruction instr;
        REQUIRE(instr.setShamt(32) == false);
        REQUIRE(instr.getShamt() == 0);
    }
}


/**
 * Instruction::reset()
 * 
 * Desired confidence level: working
 * Inputs:
 *      None
 * 
 * Valid Tests:
 *      Assign all variables some nominal value (1)
 * 
 * Valid Outputs:
 *      All numbers should be zero after function call
 * 
 * Invalid Tests:
 *      None
 */
TEST_CASE("Instruction reset should properly set fields to 0") {

    Instruction instr;
    instr.setAddr(1);
    instr.setFunct(1);
    instr.setImmediate(1);
    instr.setOpcode(1);
    instr.setRd(1);
    instr.setRs(1);
    instr.setRt(1);
    instr.setShamt(1);
    instr.reset();

    REQUIRE(instr.getAddr() == 0);
    REQUIRE(instr.getFunct() == 0);
    REQUIRE(instr.getImmediate() == 0);
    REQUIRE(instr.getOpcode() == 0);
    REQUIRE(instr.getRd() == 0);
    REQUIRE(instr.getRs() == 0);
    REQUIRE(instr.getRt() == 0);
    REQUIRE(instr.getShamt() == 0);
}