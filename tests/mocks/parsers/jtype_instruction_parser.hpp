#pragma once

#include <string>
#include <vector>

#include "instr/instruction_parser.hpp"
#include "instr/instruction.hpp"

/**
 * A simple mock class for an instruction parser.
 */
class JTypeInstructionParser: public InstructionParser {
public:

    // MARK: -- Construction
    JTypeInstructionParser() = default;
    ~JTypeInstructionParser() = default;


    // MARK: -- Inherited Parsing Methods

    /**
     * A parser for the data.
     * 
     * For this parser, everything is set to 0 except:
     * 
     *  opcode      = 10    0xA
     *  address     = 100   0x64
     * 
     * These values will help us properly test our code
     */
    std::vector<Instruction> parse(const std::string& line) const;
};