
#include "instr/parsers/li_parser.hpp"

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
std::vector<Instruction> LiParser::parse(const std::string& line) const {
    
    std::vector<Instruction> instructions;

    // First, trim the line and convert to lower case
    std::string trimmedLine = StringUtils::toLowerCase(StringUtils::trim(line));
    if (trimmedLine.length() == 0)
        throw SyntaxError("Invalid Syntax for LI: Empty input", trimmedLine);

    // Now try to use our regex expression for the form
    //
    //      add dest, src1, imm
    //
    std::regex add_rgx("^(li)\\s+(\\$\\w+),\\s*(-?\\b(0x[0-9a-fA-F]+|0[0-7]*|[1-9][0-9]*|0b[0-1]+)\\b)");
    std::smatch match;

    if (!std::regex_search(trimmedLine.cbegin(), trimmedLine.cend(), match, add_rgx))
        throw SyntaxError("Invalid Syntax for LI: Invalid format", trimmedLine);

    // Do a quick sanity check for the size (should be exactly 4)
    if (match.size() != 5 || match[1] != "li")
        throw SyntaxError("Invalid Syntax for LI: Line does not start with 'li'", trimmedLine);

    sword_t regDest = RegisterBank::getRegister(match[2]);

    // Get our immediate
    sword_t imm = 0;
    try {
        imm = StringUtils::toNumber(match[3]);
    }
    catch (std::exception& e) {
        throw SyntaxError("Invalid Syntax for LI: Invalid immediate value", trimmedLine);
    }

    if (regDest == -1)
        throw SyntaxError("Invalid Syntax for LI: Invalid register(s)", trimmedLine);

    // Get the lower 16-bits of the value
    word_t newImm = static_cast<word_t>(imm);
    hword_t val = newImm & 0xFFFF;

    // Otherwise, emplace back a new instruction
    Instruction instr;
    instr.setType(InstructionType::I_FORMAT);
    instr.setOpcode(static_cast<word_t>(Opcodes::OPCODE_ORI));
    instr.setRs(0);
    instr.setRt(regDest);
    instr.setImmediate(val);
    instructions.emplace_back(instr);

    return instructions;
}