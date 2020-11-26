#pragma once

#include <string>
#include <vector>

#include "instr/instruction.hpp"
#include "instr/instruction_parser.hpp"
#include "types.hpp"

class AddParser: public InstructionParser {
public:

    // MARK: -- Construction
    AddParser() = default;
    ~AddParser() = default;


    // MARK: -- Parse Methods

    /**
     * Parses a line with the ADD instruction (opcode 0, funct 32)
     * 
     * The format for this instruction is as follows:
     * 
     *      ADD <Rdest> <Rsrc1> <Rsrc2>
     * 
     * A syntax error will be thrown if any of the registers are invalid or
     * out of bounds.
     * 
     * @param line The line to parse
     * @throw SyntaxError If there is a syntax error
     * @return A vector with a single instruction (opcode 0, funct 32)
     */
    std::vector<Instruction> parse(const std::string& line) const;
}