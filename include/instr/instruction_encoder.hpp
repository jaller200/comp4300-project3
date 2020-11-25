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
     * If the type is PSUEDO or UNKNOWN, an IllegalEncodeError will be thrown due to the
     * impossible nature of practically handling the encodings.
     * 
     * @param instr The instruction to encode
     * @throw IllegalEncodeError If we try to encode an illegal encoding (UNKNOWN or PSUEDO)
     * @return The 32-bit instruction.
     */
    static Instruction::instr_t encode(const Instruction& instr);
};