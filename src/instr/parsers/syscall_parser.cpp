#include "instr/parsers/syscall_parser.hpp"

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

// Parses a SYSCALL instruction
std::vector<Instruction> SyscallParser::parse(const std::string& line) const {
    
    std::vector<Instruction> instructions;

    // First, trim the line and convert to lower case
    std::string trimmedLine = StringUtils::toLowerCase(StringUtils::trim(line));
    if (trimmedLine.length() == 0)
        throw SyntaxError("Invalid Syntax for SYSCALL: Empty input", trimmedLine);

    // Now try to use our regex expression for the form
    //
    //      add dest, src1, src2
    //
    std::regex syscall_rgx("^(syscall)");
    std::smatch match;

    if (!std::regex_search(trimmedLine.cbegin(), trimmedLine.cend(), match, syscall_rgx))
        throw SyntaxError("Invalid Syntax for SYSCALL: Invalid format", trimmedLine);

    // Do a quick sanity check for the size (should be exactly 4)
    if (match.size() != 2 || match[1] != "syscall")
        throw SyntaxError("Invalid Syntax for SYSCALL: Line does not start with 'syscall'", trimmedLine);

    // Write the system call
    Instruction instr;
    instr.setType(InstructionType::R_FORMAT);
    instr.setOpcode(static_cast<word_t>(Opcodes::OPCODE_R_TYPE));
    instr.setRd(0);
    instr.setRs(0);
    instr.setRt(0);
    instr.setShamt(0);
    instr.setFunct(static_cast<word_t>(Functions::FUNCT_SYSCALL));
    instructions.emplace_back(instr);

    return instructions;
}