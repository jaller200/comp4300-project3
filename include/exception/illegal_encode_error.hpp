#pragma once

#include <stdexcept>

/**
 * A basic exception for illegal instruction encodings, which are
 * limited to the following (currently):
 * 
 *  - Encoding a PSUEDO instruction type (these are just instruction placeholders)
 *  - Encoding an UNKNOWN instruction type (no idea what to do)
 */
class IllegalEncodeError : public std::runtime_error {
public:

    /**
     * Creates a syntax error.
     * @param msg The base message
     */
    IllegalEncodeError(const std::string& msg)
        : std::runtime_error(msg)
    { }
};