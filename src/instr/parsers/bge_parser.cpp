
#include "instr/parsers/bge_parser.hpp"

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
std::vector<Instruction> BgeParser::parse(const std::string& line) const {
    
    std::vector<Instruction> instructions;

    // First, trim the line and convert to lower case
    std::string trimmedLine = StringUtils::toLowerCase(StringUtils::trim(line));
    if (trimmedLine.length() == 0)
        throw SyntaxError("Invalid Syntax for BGE: Empty input", trimmedLine);

    // Now try to use our regex expression for the form
    //
    //      beq dest, src, label
    //
    std::regex beqz_rgx("^(bge)\\s+(\\$\\w+),\\s*(\\$\\w+),\\s*(\\w+)");
    std::smatch match;

    if (!std::regex_search(trimmedLine.cbegin(), trimmedLine.cend(), match, beqz_rgx))
        throw SyntaxError("Invalid Syntax for BGE: Invalid format", trimmedLine);

    // Do a quick sanity check for the size (should be exactly 4)
    if (match.size() != 5 || match[1] != "bge")
        throw SyntaxError("Invalid Syntax for BGE: Line does not start with 'beqz'", trimmedLine);

    // Now, create our instructions
    sword_t regDest = RegisterBank::getRegister(match[2]);
    sword_t regSrc = RegisterBank::getRegister(match[3]);
    std::string label = match[4];

    if (regDest == -1 || regSrc == -1)
        throw SyntaxError("Invalid Syntax for BGE: Invalid register(s)", trimmedLine);

    // BGE expands into two instructions:
    //
    //  slt $at, $rs, $rt
    //  beq $at, $zero, label
    //
    Instruction instr1;
    instr1.setType(InstructionType::R_FORMAT);
    instr1.setOpcode(static_cast<word_t>(Opcodes::OPCODE_R_TYPE));
    instr1.setRd(1);
    instr1.setRs(regDest);
    instr1.setRt(regSrc);
    instr1.setShamt(0);
    instr1.setFunct(static_cast<word_t>(Functions::FUNCT_SLT));
    instructions.emplace_back(instr1);

    // Otherwise, emplace back a new instruction
    Instruction instr2;
    instr2.setType(InstructionType::I_FORMAT);
    instr2.setOpcode(static_cast<word_t>(Opcodes::OPCODE_BEQ));
    instr2.setRs(0);
    instr2.setRt(1);
    instr2.setLabel(label);
    instructions.emplace_back(instr2);

    return instructions;
}