#pragma once

#include <string>
#include <vector>

#include "instr/instruction.hpp"
#include "types.hpp"

/**
 * A virtual base class for all instructon parsers.
 */
class InstructionParser {
public:

    // MARK: -- Construction

    /**
     * Virtual destructor.
     */
    virtual ~InstructionParser() { }


    // MARK: -- Parsing Methods

    /**
     * A base for all implemented parses to handle parsing their own lines.
     * 
     * This function takes in a line and returns an array of ordered instructions to be
     * written to memory.
     * 
     * @param line The line to parse
     * @throw SyntaxException A syntax exception if one occurs
     * @return A list of all instructions output, an empty list if there was an unknown error
     */
    virtual std::vector<Instruction> parse(const std::string& line) const = 0;
};