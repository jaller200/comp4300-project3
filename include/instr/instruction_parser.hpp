#pragma once

#include <string>

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
     * @param line The line to parse
     * @throw SyntaxException A syntax exception if one occurs
     * @return Whether or not the parse was successful
     */
    virtual Instruction parse(const std::string& line) const = 0;
};