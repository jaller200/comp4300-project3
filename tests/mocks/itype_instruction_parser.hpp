#pragma once

#include <string>

#include "instr/instruction_parser.hpp"
#include "instr/instruction.hpp"

/**
 * A simple mock class for an instruction parser.
 */
class ITypeInstructionParser: public InstructionParser {
public:

    // MARK: -- Construction
    ITypeInstructionParser() = default;
    ~ITypeInstructionParser() = default;


    // MARK: -- Inherited Parsing Methods

    /**
     * A parser for the data.
     * 
     * For this parser, everything is set to 0 except:
     * 
     *  opcode      = 10    0xA
     * 
     * These values will help us properly test our code
     */
    Instruction parse(const std::string& line) const;
};