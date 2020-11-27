#include "instr/parsers/add_parser.hpp"

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

// Parses an ADD instruction
std::vector<Instruction> AddParser::parse(const std::string& line) const {
    
    std::vector<Instruction> instructions;

    // First, trim the line and convert to lower case
    std::string trimmedLine = StringUtils::toLowerCase(StringUtils::trim(line));
    if (trimmedLine.length() == 0)
        throw SyntaxError("Invalid Syntax for ADD: Empty input", trimmedLine);

    // Now try to use our regex expression for the form
    //
    //      add dest, src1, src2
    //
    std::regex add_rgx("^(add)\\s+(\\$\\w+),\\s*(\\$\\w+),\\s*(\\$\\w+)$");
    std::smatch match;

    if (!std::regex_search(trimmedLine.cbegin(), trimmedLine.cend(), match, add_rgx))
        throw SyntaxError("Invalid Syntax for ADD: Invalid format", trimmedLine);

    // Do a quick sanity check for the size (should be exactly 4)
    if (match.size() != 5 || match[1] != "add")
        throw SyntaxError("Invalid Syntax for ADD: Line does not start with 'add'", trimmedLine);

    // Now, create our instructions
    sword_t regDest = RegisterBank::getRegister(match[2]);
    sword_t regSrc1 = RegisterBank::getRegister(match[3]);
    sword_t regSrc2 = RegisterBank::getRegister(match[4]);

    if (regDest == -1 || regSrc1 == -1 || regSrc2 == -1)
        throw SyntaxError("Invalid Syntax for ADD: Invalid register(s)", trimmedLine);

    if (regDest == 0)
        throw SyntaxError("Invalid Syntax for ADD: Cannot write to the $zero register", trimmedLine);

    // Otherwise, emplace back a new instruction
    Instruction instr;
    instr.setType(InstructionType::R_FORMAT);
    instr.setOpcode(static_cast<word_t>(Opcodes::OPCODE_R_TYPE));
    instr.setRd(regDest);
    instr.setRs(regSrc1);
    instr.setRt(regSrc2);
    instr.setShamt(0);
    instr.setFunct(static_cast<word_t>(Functions::FUNCT_ADD));
    instructions.emplace_back(instr);

    return instructions;
}