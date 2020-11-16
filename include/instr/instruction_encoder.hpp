#pragma once

#include "instr/instruction.hpp"
#include "types.hpp"

/**
 * A class with a single static method that encodes an Instruction
 * structure into a 32-bit value.
 */
class InstructionEncoder {
public:

    /**
     * Encodes an instruction structure into a 32-bit instruction value.
     * 
     * Note that this method uses the Instruction::getType() field in order to determine
     * how to encode the instruction.
     * 
     * If the type is InstructionType::UNKNOWN, a value of 0x00000000 (NOP) is returned.
     * 
     * @param instr The instruction to encode
     * @return The 32-bit instruction.
     */
    static Instruction::instr_t encode(const Instruction& instr);
};