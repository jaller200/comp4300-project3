#include "mocks/itype_instruction_parser.hpp"

#include "instr/instruction_type.hpp"

// MARK: -- Inherited Parse Methods

// Parses a line
Instruction ITypeInstructionParser::parse(const std::string& line) const {

    Instruction instr;
    instr.setOpcode(0xA);
    instr.setType(InstructionType::I_FORMAT);
    return instr;
}