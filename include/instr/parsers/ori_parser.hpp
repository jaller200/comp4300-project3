#pragma once

#include <string>
#include <vector>

#include "instr/instruction.hpp"
#include "instr/instruction_parser.hpp"
#include "types.hpp"

/**
 * A parser for the ORI (bitwise or immediate) instruction (opcode 13)
 */
class OriParser: public InstructionParser {
public:

    // MARK: -- Construction
    OriParser() = default;
    ~OriParser() = default;


    // MARK: -- Parse Methods

    /**
     * Parses a line with the ORI (bitwise or immediate) instruction (opcode 13)
     * 
     * The format for this instruction is as follows:
     * 
     *      ORI <Rdest> <Rsrc1> <immediate>
     * 
     * A syntax error will be thrown if any of the registers are invalid or
     * out of bounds.
     * 
     * @param line The line to parse
     * @throw SyntaxError If there is a syntax error
     * @return A vector with the instructions
     */
    std::vector<Instruction> parse(const std::string& line) const;
};