#include "tests/include/catch.hpp"

#include "instr/instruction.hpp"
#include "instr/instruction_type.hpp"

#include <iostream>

TEST_CASE("Instructions can be created and edited properly", "[instruction]") {

    Instruction instr;

    // MARK: -- Getters / Settesr
    /**
     * Desired Confidence: Working Getters / Setters
     * 
     * Valid Tests:
     *      Set then get each setter / getter
     *      After all getters / setters have been run, reset should clear everything
     * 
     * Valid Outputs:
     *      Getter should return the value passed to setter
     *      Everything should be 0 / unknown after reset()
     * 
     * Invalid Tests:
     *      None
     */
    SECTION("Instruction getters and setters should work properly") {

        instr.setFunct(1);
        REQUIRE(instr.getFunct() == 1);

        instr.setImmediate(2);
        REQUIRE(instr.getImmediate() == 2);

        instr.setOpcode(3);
        REQUIRE(instr.getOpcode() == 3);

        instr.setRd(4);
        REQUIRE(instr.getRd() == 4);

        instr.setRs(5);
        REQUIRE(instr.getRs() == 5);

        instr.setRt(6);
        REQUIRE(instr.getRt() == 6);

        instr.setShamt(7);
        REQUIRE(instr.getShamt() == 7);
        
        instr.setType(InstructionType::I_FORMAT);
        REQUIRE(instr.getType() == InstructionType::I_FORMAT);

        SECTION("After testing getters / setters, reset should properly reset everything") {

            instr.reset();
            REQUIRE(instr.getFunct() == 0);
            REQUIRE(instr.getImmediate() == 0);
            REQUIRE(instr.getOpcode() == 0);
            REQUIRE(instr.getRd() == 0);
            REQUIRE(instr.getRs() == 0);
            REQUIRE(instr.getRt() == 0);
            REQUIRE(instr.getShamt() == 0);
            REQUIRE(instr.getType() == InstructionType::UNKNOWN);
        }
    }

    // MARK: -- Instruction Creation
    /**
     * Desired Confidence Level: Boundary value analysis
     * 
     * Inputs:
     *      parameters  => nominal values
     *      type        => R_FORMAT, I_FORMAT, J_FORMAT
     * 
     * Valid Tests:
     *      Each parameter set by itself, getInstruction() called for each
     *          type.
     * 
     * Valid Outputs:
     *      Instruction types with the single instruction parameter, controlling
     *          for type.
     * 
     * Invalid Tests
     *      None (no parameters passed, domain is enforced at compile-time)
     */
    SECTION("Setting funct works properly for all three types") {

        instr.setFunct(1);

        instr.setType(InstructionType::R_FORMAT);
        auto rType = instr.getInstruction();
        REQUIRE(rType == 0x4000000);
    }
}