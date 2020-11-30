#pragma once

#include <string>
#include <vector>

#include "instr/instruction.hpp"
#include "instr/instruction_parser.hpp"
#include "types.hpp"

/**
 * A parser for the SLL (shift left logical) instruction (opcode 0, funct 0)
 */
class SllParser: public InstructionParser {
public:

    // MARK: -- Construction
    SllParser() = default;
    ~SllParser() = default;


    // MARK: -- Parse Methods

    /**
     * Parses a line with the SLL (shift left logical) instruction (opcode 0, funct 0)
     * 
     * The format for this instruction is as follows:
     * 
     *      SLL <Rdest> <Rsrc1> <shift amount>
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