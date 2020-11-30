#pragma once

#include <string>
#include <vector>

#include "instr/instruction.hpp"
#include "instr/instruction_parser.hpp"
#include "types.hpp"

/**
 * A parser for the LB (load byte) instruction (opcode 16)
 */
class LbParser: public InstructionParser {
public:

    // MARK: -- Construction
    LbParser() = default;
    ~LbParser() = default;


    // MARK: -- Parse Methods

    /**
     * Parses a line with the LB (load byte) instruction (opcode 16)
     * 
     * The format for this instruction is as follows:
     * 
     *      LB <Rdest> <offset>(<Rsrc>)
     * 
     * OR
     * 
     *      LB <Rdest>, <Rsrc>
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