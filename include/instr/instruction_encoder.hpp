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
     * Decodes an 32-bit instruction value based on the instruction type.
     * 
     * Since the only decodable types are R_FORMAT, I_FORMAT, and J_FORMAT, all
     * other types will throw an illegal encoding error.
     * 
     * @param instr The 32-bit instruction
     * @param type The instruction type to decode as
     * @throw IllegalEncodeError If we try to decode an instruction with an invalid format
     * @return The instruction structure
     */
    static Instruction decode(Instruction::instr_t instr, InstructionType type);

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