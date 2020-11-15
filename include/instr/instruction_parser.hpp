#pragma once

#include <string>

#include "types.hpp"

/**
 * A virtual base class for all instructon parsers.
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
     * @throw SyntaxException A syntax exception if one occurs
     * @return Whether or not the parse was successful
     */
    virtual bool parse(const std::string& line) = 0;
};