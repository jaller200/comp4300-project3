
#include "instr/parsers/lb_parser.hpp"

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
std::vector<Instruction> LbParser::parse(const std::string& line) const {
    
    std::vector<Instruction> instructions;

    // First, trim the line and convert to lower case
    std::string trimmedLine = StringUtils::toLowerCase(StringUtils::trim(line));
    if (trimmedLine.length() == 0)
        throw SyntaxError("Invalid Syntax for LB: Empty input", trimmedLine);

    sword_t regDest = -1;
    sword_t regSrc = -1;
    sword_t imm = 0;


    // First, try to load the common "offset" version
    std::regex lb_rgx_1("^(lb)\\s+(\\$\\w+),\\s+(-?\\b(0x[0-9a-fA-F]+|0[0-7]*|[1-9][0-9]*|0b[0-1]+)\\b)\\((\\$\\w+)\\)");
    std::regex lb_rgx_2("^(lb)\\s+(\\$\\w+),\\s+(\\$\\w+)");
    std::smatch match;

    if (std::regex_search(trimmedLine.cbegin(), trimmedLine.cend(), match, lb_rgx_1)) {

        // Check our size
        if (match.size() != 6 || match[1] != "lb")
            throw SyntaxError("Invalid Syntax for LB: Line does not start with 'lb'", trimmedLine);

        regDest = RegisterBank::getRegister(match[2]);
        regSrc = RegisterBank::getRegister(match[5]);

        // Get our immediate
        try {
            imm = StringUtils::toNumber(match[3]);
        }
        catch (std::exception& e) {
            throw SyntaxError("Invalid Syntax for LI: Invalid immediate value", trimmedLine);
        }
    }
    else if (std::regex_search(trimmedLine.cbegin(), trimmedLine.cend(), match, lb_rgx_2)) {

        // Check our size
        if (match.size() != 4 || match[1] != "lb")
            throw SyntaxError("Invalid Syntax for LB: Line does not start with 'lb'", trimmedLine);

        regDest = RegisterBank::getRegister(match[2]);
        regSrc = RegisterBank::getRegister(match[3]);
        imm = 0;
    }
    else
        throw SyntaxError("Invalid Syntax for LI: Invalid format", trimmedLine);

    if (regDest == -1 || regSrc == -1)
        throw SyntaxError("Invalid Syntax for LI: Invalid register(s)", trimmedLine);

    // Get the lower 16-bits of the value
    word_t newImm = static_cast<word_t>(imm);
    hword_t val = newImm & 0xFFFF;

    // Otherwise, emplace back a new instruction
    Instruction instr;
    instr.setType(InstructionType::I_FORMAT);
    instr.setOpcode(static_cast<word_t>(Opcodes::OPCODE_LB));
    instr.setRs(regSrc);
    instr.setRt(regDest);
    instr.setImmediate(val);
    instructions.emplace_back(instr);

    return instructions;
}