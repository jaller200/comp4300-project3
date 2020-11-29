#include "instr/parsers/la_parser.hpp"

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
std::vector<Instruction> LaParser::parse(const std::string& line) const {
    
    std::vector<Instruction> instructions;

    // First, trim the line and convert to lower case
    std::string trimmedLine = StringUtils::toLowerCase(StringUtils::trim(line));
    if (trimmedLine.length() == 0)
        throw SyntaxError("Invalid Syntax for LA: Empty input", trimmedLine);

    // Now try to use our regex expression for the form
    //
    //      la dest, label
    //
    std::regex b_rgx("^(la)\\s+(\\$\\w+),\\s+(\\w+)");
    std::smatch match;
    
    if (!std::regex_search(trimmedLine.cbegin(), trimmedLine.cend(), match, b_rgx))
        throw SyntaxError("Invalid Syntax for LA: Invalid format", trimmedLine);

    // Do a quick sanity check for the size (should be exactly 4)
    if (match.size() != 4 || match[1] != "la")
        throw SyntaxError("Invalid Syntax for LA: Line does not start with 'b'", trimmedLine);

    // Get our destination register
    sword_t regDest = RegisterBank::getRegister(match[2]);

    // Now, create our instructions
    std::string label = match[3];

    // LA expands into
    //
    //  lui $rt, upper 16 bits of label address
    //  ori $rt, $rt, lower 16 bits of label address
    //
    Instruction instr;
    instr.setType(InstructionType::I_FORMAT);
    instr.setOpcode(static_cast<word_t>(Opcodes::OPCODE_LUI));
    instr.setRs(0);
    instr.setRt(regDest);
    instr.setLabel(label);
    instructions.emplace_back(instr);

    Instruction instr2;
    instr2.setType(InstructionType::I_FORMAT);
    instr2.setOpcode(static_cast<word_t>(Opcodes::OPCODE_ORI));
    instr2.setRs(regDest);
    instr2.setRt(regDest);
    instr2.setLabel(label);
    instructions.emplace_back(instr2);

    return instructions;
}