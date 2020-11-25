#pragma once

#include <string>
#include <vector>

#include "instr/instruction_parser.hpp"
#include "instr/instruction.hpp"

/**
 * A simple mock class for an instruction parser.
 */
class RTypeInstructionParser: public InstructionParser {
public:

    // MARK: -- Construction
    RTypeInstructionParser() = default;
    ~RTypeInstructionParser() = default;


    // MARK: -- Inherited Parsing Methods

    /**
     * A parser for the data.
     * 
     * For this parser, everything is set to 0 except:
     * 
     *  opcode      = 10    0xA
     *  function    = 11    0xB
     * 
     * These values will help us properly test our code
     */
    std::vector<Instruction> parse(const std::string& line) const;
};