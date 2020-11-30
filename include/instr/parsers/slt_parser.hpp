#pragma once

#include <string>
#include <vector>

#include "instr/instruction.hpp"
#include "instr/instruction_parser.hpp"
#include "types.hpp"

/**
 * A parser for the SLT (set on less than) instruction (opcode 0, funct 42)
 */
class SltParser: public InstructionParser {
public:

    // MARK: -- Construction
    SltParser() = default;
    ~SltParser() = default;


    // MARK: -- Parse Methods

    /**
     * Parses a line with the SLT (set on less than) instruction (opcode 0, funct 42)
     * 
     * The format for this instruction is as follows:
     * 
     *      SLT <Rdest> <Rsrc1> <Rsrc2>
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