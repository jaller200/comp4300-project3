#pragma once

#include <string>
#include <vector>

#include "instr/instruction.hpp"
#include "instr/instruction_parser.hpp"
#include "types.hpp"

/**
 * A parser for the ADDI (add immediate) instruction (opcode 8)
 */
class AddiParser: public InstructionParser {
public:

    // MARK: -- Construction
    AddiParser() = default;
    ~AddiParser() = default;


    // MARK: -- Parse Methods

    /**
     * Parses a line with the ADDI (add immediate) instruction (opcode 8)
     * 
     * The format for this instruction is as follows:
     * 
     *      ADII <Rdest> <Rsrc1> <immediate>
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