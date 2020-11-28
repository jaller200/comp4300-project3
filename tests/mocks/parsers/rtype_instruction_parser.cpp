#include "mocks/parsers/rtype_instruction_parser.hpp"

#include "instr/instruction_type.hpp"

// MARK: -- Inherited Parse Methods

// Parses a line
std::vector<Instruction> RTypeInstructionParser::parse(const std::string& line) const {

    std::vector<Instruction> instructions;

    Instruction instr;
    instr.setFunct(0xB);
    instr.setOpcode(0xA);
    instr.setType(InstructionType::R_FORMAT);
    instructions.emplace_back(instr);

    return instructions;
}