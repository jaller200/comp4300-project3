#pragma once

#include <string>
#include <vector>

#include "instr/instruction.hpp"
#include "instr/instruction_parser.hpp"
#include "types.hpp"

/**
 * A parser for the ADDI instruction (opcode 8)
 */
class SyscallParser: public InstructionParser {
public:

    // MARK: -- Construction
    SyscallParser() = default;
    ~SyscallParser() = default;


    // MARK: -- Parse Methods

    /**
     * Parses a line with the SYSCALL (system call) instruction (opcode 0, funct 12)
     * 
     * The format for this instruction is as follows:
     * 
     *      SYSCALL
     * 
     * The type of syscall is stored in register $v0 (2).
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