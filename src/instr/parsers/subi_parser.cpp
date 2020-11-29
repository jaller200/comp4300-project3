
#include "instr/parsers/subi_parser.hpp"

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
std::vector<Instruction> SubiParser::parse(const std::string& line) const {
    
    std::vector<Instruction> instructions;

    // First, trim the line and convert to lower case
    std::string trimmedLine = StringUtils::toLowerCase(StringUtils::trim(line));
    if (trimmedLine.length() == 0)
        throw SyntaxError("Invalid Syntax for SUBI: Empty input", trimmedLine);

    // Now try to use our regex expression for the form
    //
    //      add dest, src1, imm
    //
    std::regex add_rgx("^(subi)\\s+(\\$\\w+),\\s*(\\$\\w+),\\s*(-?\\b(0x[0-9a-fA-F]+|0[0-7]*|[1-9][0-9]*|0b[0-1]+)\\b)");
    std::smatch match;

    if (!std::regex_search(trimmedLine.cbegin(), trimmedLine.cend(), match, add_rgx))
        throw SyntaxError("Invalid Syntax for SUBI: Invalid format", trimmedLine);

    // Do a quick sanity check for the size (should be exactly 4)
    if (match.size() != 6 || match[1] != "subi")
        throw SyntaxError("Invalid Syntax for SUBI: Line does not start with 'addi'", trimmedLine);

    // Now, create our instructions
    sword_t regDest = RegisterBank::getRegister(match[2]);
    sword_t regSrc = RegisterBank::getRegister(match[3]);
    
    // Get our immediate
    sword_t imm = 0;
    try {
        imm = StringUtils::toNumber(match[4]);
    }
    catch (std::exception& e) {
        throw SyntaxError("Invalid Syntax for SUBI: Invalid immediate value", trimmedLine);
    }

    if (regDest == -1 || regSrc == -1)
        throw SyntaxError("Invalid Syntax for SUBI: Invalid register(s)", trimmedLine);

    sword_t limit = (Instruction::LIMIT_IMM + 1) / 2;
    if (imm >= limit || imm < -limit)
        throw SyntaxError("Invalid Syntax for SUBI: Out of bounds immediate", trimmedLine);

    // Expand to ADDI with a negative immediate
    Instruction instr;
    instr.setType(InstructionType::I_FORMAT);
    instr.setOpcode(static_cast<word_t>(Opcodes::OPCODE_ADDI));
    instr.setRs(regSrc);
    instr.setRt(regDest);
    instr.setImmediate(static_cast<hword_t>(-imm));
    instructions.emplace_back(instr);

    return instructions;
}