
#include "instr/parsers/beqz_parser.hpp"

#include <iostream>
#include <regex>
#include <sstream>

#include "exception/syntax_error.hpp"
#include "instr/functions.hpp"
#include "instr/instruction.hpp"
#include "instr/instruction_type.hpp"
#include "instr/opcodes.hpp"
#include "registers/register_bank.hpp"
#include "utils/string_utils.hpp"

// MARK: -- Parse Methods

// Parses a BEQZ instruction
std::vector<Instruction> BeqzParser::parse(const std::string& line) const {
    
    std::vector<Instruction> instructions;

    // First, trim the line and convert to lower case
    std::string trimmedLine = StringUtils::toLowerCase(StringUtils::trim(line));
    if (trimmedLine.length() == 0)
        throw SyntaxError("Invalid Syntax for BEQZ: Empty input", trimmedLine);

    // Now try to use our regex expression for the form
    //
    //      beq dest, src, label
    //
    std::regex beqz_rgx("^(beqz)\\s+(\\$\\w+),\\s*(\\w+)");
    std::smatch match;

    if (!std::regex_search(trimmedLine.cbegin(), trimmedLine.cend(), match, beqz_rgx))
        throw SyntaxError("Invalid Syntax for BEQZ: Invalid format", trimmedLine);

    // Do a quick sanity check for the size (should be exactly 4)
    if (match.size() != 4 || match[1] != "beqz")
        throw SyntaxError("Invalid Syntax for BEQZ: Line does not start with 'beqz'", trimmedLine);

    // Now, create our instructions
    sword_t regDest = RegisterBank::getRegister(match[2]);
    std::string label = match[3];

    if (regDest == -1)
        throw SyntaxError("Invalid Syntax for ADDI: Invalid register(s)", trimmedLine);

    // Otherwise, emplace back a new instruction
    Instruction instr;
    instr.setType(InstructionType::I_FORMAT);
    instr.setOpcode(static_cast<word_t>(Opcodes::OPCODE_BEQ));
    instr.setRs(0);
    instr.setRt(regDest);
    instr.setLabel(label);
    instructions.emplace_back(instr);

    return instructions;
}