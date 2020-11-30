#include "mocks/parsers/itype_instruction_parser.hpp"

#include "instr/instruction_type.hpp"

// MARK: -- Inherited Parse Methods

// Parses a line
std::vector<Instruction> ITypeInstructionParser::parse(const std::string& line) const {

    std::vector<Instruction> instructions;

    Instruction instr;
    instr.setImmediate(0x64);
    instr.setOpcode(0xA);
    instr.setType(InstructionType::I_FORMAT);
    instructions.emplace_back(instr);

    return instructions;
}