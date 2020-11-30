#pragma once

#include <string>
#include <vector>

#include "instr/instruction.hpp"
#include "instr/instruction_parser.hpp"
#include "types.hpp"

/**
 * A parser for the BEQ (branch on equal) instruction (opcode 4)
 */
class BeqParser: public InstructionParser {
public:

    // MARK: -- Construction
    BeqParser() = default;
    ~BeqParser() = default;


    // MARK: -- Parse Methods

    /**
     * Parses a line with the BEQ (branch on equal) instruction (opcode 4)
     * 
     * The format for this instruction is as follows:
     * 
     *      BEQ <Rdest> <Rsrc1> <label>
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