#include "mocks/parsers/psuedo_type_instruction_parser.hpp"

#include "instr/instruction_type.hpp"

// MARK: -- Inherited Parse Methods

// Parses a line
std::vector<Instruction> PsuedoTypeInstructionParser::parse(const std::string& line) const {

    std::vector<Instruction> instructions;

    Instruction instr;
    instr.setImmediate(0x64);
    instr.setOpcode(0xA);
    instr.setType(InstructionType::I_FORMAT);
    instructions.emplace_back(instr);

    Instruction instr2;
    instr2.setFunct(0xB);
    instr2.setOpcode(0xA);
    instr2.setType(InstructionType::R_FORMAT);
    instructions.emplace_back(instr2);

    return instructions;
}