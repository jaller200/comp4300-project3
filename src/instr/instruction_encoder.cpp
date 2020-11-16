#include "instr/instruction_encoder.hpp"

#include "instr/instruction_type.hpp"

// Encodes an instruction
Instruction::instr_t InstructionEncoder::encode(const Instruction& instr) {

    // Our instruction
    Instruction::instr_t output = 0x00000000;

    // Handle each type separately
    switch (instr.getType()) {

        case InstructionType::I_FORMAT: {

            output = (output & ~Instruction::FLAG_IMM) | ((instr.getImmediate() << 16) & Instruction::FLAG_IMM);
            output = (output & ~Instruction::FLAG_RT) | ((instr.getRt() << 11) & Instruction::FLAG_RT);
            output = (output & ~Instruction::FLAG_RS) | ((instr.getRs() << 6) & Instruction::FLAG_RS);
            output = (output & ~Instruction::FLAG_OPCODE) | (instr.getOpcode() & Instruction::FLAG_OPCODE);
            break;
        }

        // R-Type
        case InstructionType::R_FORMAT: {
            
            output = (output & ~Instruction::FLAG_FUNCT) | ((instr.getFunct() << 26) & Instruction::FLAG_FUNCT);
            output = (output & ~Instruction::FLAG_SHAMT) | ((instr.getShamt() << 21) & Instruction::FLAG_SHAMT);
            output = (output & ~Instruction::FLAG_RD) | ((instr.getRd() << 16) & Instruction::FLAG_RD);
            output = (output & ~Instruction::FLAG_RT) | ((instr.getRt() << 11) & Instruction::FLAG_RT);
            output = (output & ~Instruction::FLAG_RS) | ((instr.getRs() << 6) & Instruction::FLAG_RS);
            output = (output & ~Instruction::FLAG_OPCODE) | (instr.getOpcode() & Instruction::FLAG_OPCODE);
            break;
        }

        // Other
        default:
            break;
    }

    return output;
}