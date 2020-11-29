#pragma once

#include <string>
#include <vector>

#include "instr/instruction.hpp"
#include "instr/instruction_parser.hpp"
#include "types.hpp"

/**
 * A parser for the BNE instruction (opcode 5)
 */
class BneParser: public InstructionParser {
public:

    // MARK: -- Construction
    BneParser() = default;
    ~BneParser() = default;


    // MARK: -- Parse Methods

    /**
     * Parses a line with the BNE instruction (opcode 5)
     * 
     * The format for this instruction is as follows:
     * 
     *      BNE <Rdest> <Rsrc1> <label>
     * 
     * A syntax error will be thrown if any of the registers are invalid or
     * out of bounds.
     * 
     * @param line The line to parse
     * @throw SyntaxError If there is a syntax error
     * @return A vector with a single instruction (opcode 8)
     */
    std::vector<Instruction> parse(const std::string& line) const;
};