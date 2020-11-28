#pragma once

#include <stdexcept>

/**
 * An exception thrown whenever we are running unknown instuctions.
 */
class UnknownInstructionError : public std::runtime_error {
public:

    /**
     * Creates a syntax error.
     * @param msg The base message
     */
    UnknownInstructionError(const std::string& msg)
        : std::runtime_error(msg)
    { }
};