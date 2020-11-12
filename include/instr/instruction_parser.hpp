#pragma once

#include <string>

#include "types.hpp"

/**
 * A virtual base class for all instructon parsers.
 * 
 * Instructions will be registered by Opcode & Function (if defined).
 * 
 *      Opcode      : 6 bits
 *      Function    : 6 bits
 * 
 * Registration will be done with 16 bits, where the first 6 bits are the opcode
 * and the second 6 bits are the function (if necessary). This way I-Type (opcode 0)
 * instructions can be stored just as easily as R-Type and branch.
 */
class InstructionParser {
public:

    // MARK: -- Construction
    InstructionParser() = default;
    ~InstructionParser() = default;


    // MARK: -- Parsing Methods

    /**
     * A base for all implemented parses to handle parsing their own lines.
     * @param line The line to parse
     * @return Whether or not the parse was successful
     */
    virtual bool parseLine(const std::string& line) = 0;
};