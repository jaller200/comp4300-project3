#include "instr/instruction_encoder.hpp"

#include "exception/illegal_encode_error.hpp"
#include "instr/instruction_type.hpp"

Instruction InstructionEncoder::decode(Instruction::instr_t instr, InstructionType type) {

    // Create our instruction structure
    Instruction instruction;

    // Get the opcode
    instruction.setOpcode(instr & ((1 << 6) - 1));

    // Now the rest needs to be handled per-type
    switch (type) {

        // I-Type
        case InstructionType::I_FORMAT: {

            instruction.setRs((instr >> 6) & ((1 << 5) - 1));
            instruction.setRt((instr >> 11) & ((1 << 5) - 1));
            instruction.setImmediate((instr >> 16) & ((1 << 16) - 1));
            break;
        }

        // J-Type
        case InstructionType::J_FORMAT: {

            instruction.setAddr((instr >> 6) & ((1 << 26) - 1));
            break;
        }

        // R-Type
        case InstructionType::R_FORMAT: {

            instruction.setRs((instr >> 6) & ((1 << 5) - 1));
            instruction.setRt((instr >> 11) & ((1 << 5) - 1));
            instruction.setRd((instr >> 16) & ((1 << 5) - 1));
            instruction.setShamt((instr >> 21) & ((1 << 5) - 1));
            instruction.setFunct((instr >> 26) & ((1 << 6) - 1));
            break;
        }

        default: {
            throw IllegalEncodeError("Unable to properly decode PSUEDO or UNKNOWN instruction!");
        }
    }

    return instruction;
}

// Encodes an instruction
Instruction::instr_t InstructionEncoder::encode(const Instruction& instr) {

    // Our instruction
    Instruction::instr_t output = 0x00000000;

    // Handle each type separately
    switch (instr.getType()) {

        // I-Type
        case InstructionType::I_FORMAT: {

            output = (output & ~Instruction::FLAG_IMM) | ((instr.getImmediate() << 16) & Instruction::FLAG_IMM);
            output = (output & ~Instruction::FLAG_RT) | ((instr.getRt() << 11) & Instruction::FLAG_RT);
            output = (output & ~Instruction::FLAG_RS) | ((instr.getRs() << 6) & Instruction::FLAG_RS);
            output = (output & ~Instruction::FLAG_OPCODE) | (instr.getOpcode() & Instruction::FLAG_OPCODE);
            break;
        }

        // J-Type
        case InstructionType::J_FORMAT: {

            output = (output & ~Instruction::FLAG_ADDR) | ((instr.getAddr() << 6) & Instruction::FLAG_ADDR);
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
        default: {
            throw IllegalEncodeError("Unable to properly encode PSUEDO or UNKNOWN instruction!");
        }
    }

    return output;
}