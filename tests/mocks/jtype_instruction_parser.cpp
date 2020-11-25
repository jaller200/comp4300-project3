#include "mocks/jtype_instruction_parser.hpp"

#include "instr/instruction_type.hpp"

// MARK: -- Inherited Parse Methods

// Parses a line
std::vector<Instruction> JTypeInstructionParser::parse(const std::string& line) const {

    std::vector<Instruction> instructions;

    Instruction instr;
    instr.setAddr(0x64);
    instr.setOpcode(0xA);
    instr.setType(InstructionType::J_FORMAT);
    instructions.emplace_back(instr);

    return instructions;
}