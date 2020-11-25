#include "mocks/rtype_instruction_parser.hpp"

#include "instr/instruction_type.hpp"

// MARK: -- Inherited Parse Methods

// Parses a line
Instruction RTypeInstructionParser::parse(const std::string& line) const {

    Instruction instr;
    instr.setFunct(0xB);
    instr.setOpcode(0xA);
    instr.setType(InstructionType::R_FORMAT);
    return instr;
}