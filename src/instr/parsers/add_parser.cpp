#include "instr/parsers/add_parser.hpp"

#include <iostream>
#include <sstream>

#include "exception/syntax_error.hpp"
#include "utils/string_utils.hpp"

// MARK: -- Parse Methods

// Parses an ADD instruction
std::vector<Instruction> AddParser::parse(const std::string& line) const {
    
    std::vector<Instruction> instructions;

    // First, trim the line and convert to lower case
    std::string trimmedLine = StringUtils::toLowerCase(StringUtils::trim(line));
    if (trimmedLine.length() == 0)
        throw new SyntaxError("Invalid Syntax for ADD: Input is empty.");

    // Create our string stream
    std::stringstream ss(trimmedLine);

    // Create our placeholders
    std::string strInstr;
    std::string strRegDest;
    std::string strRegSrc1;
    std::string strRegSrc2;

    word_t regDest;
    word_t regSrc1;
    word_t regSrc2;

    // And start getting elements
    ss >> strInstr;
    if (ss.fail() || strInstr != "add")
        throw SyntaxError("Invalid Syntax for ADD: Opcode name is incorreect: '" + trimmedLine + "'");

    ss >> strRegDest;


    return instructions;
}