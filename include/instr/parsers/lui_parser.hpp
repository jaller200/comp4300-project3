#pragma once

#include <string>
#include <vector>

#include "instr/instruction.hpp"
#include "instr/instruction_parser.hpp"
#include "types.hpp"

/**
 * A parser for the ORI instruction (opcode 8)
 */
class LuiParser: public InstructionParser {
public:

    // MARK: -- Construction
    LuiParser() = default;
    ~LuiParser() = default;


    // MARK: -- Parse Methods

    /**
     * Parses a line with the LUI instruction (opcode 15)
     * 
     * The format for this instruction is as follows:
     * 
     *      LUI <Rdest> <immediate>
     * 
     * A syntax error will be thrown if any of the registers are invalid or
     * out of bounds.
     * 
     * @param line The line to parse
     * @throw SyntaxError If there is a syntax error
     * @return A vector with a single instruction (opcode 15)
     */
    std::vector<Instruction> parse(const std::string& line) const;
};