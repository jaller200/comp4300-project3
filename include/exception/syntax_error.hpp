#pragma once

#include <iostream>
#include <stdexcept>
#include <sstream>

#include "types.hpp"

/**
 * A basic exception for syntax errors.
 */
class SyntaxError : public std::runtime_error {
public:

    /**
     * Creates a syntax error with information about the filename
     * and line number the error occurred on.
     * @param msg The base message
     * @param filename The filename
     * @param lineNumber The line number
     */
    explicit SyntaxError(const std::string& msg, const std::string& line)
        : std::runtime_error(msg)
        , m_strLine(line)
    { }


    // MARK: -- Private Message Methods

    /**
     * Returns a const char array of the message to print.
     * @return The message to print
     */
    virtual const char * what() const noexcept {

        std::string msg(std::runtime_error::what());
        std::string error = "error: " + msg + "\n\t" + this->m_strLine + "\n";
        return error.c_str();
    }

private:

    // MARK: -- Private Variables

    /** The line things messed up on. */
    std::string m_strLine;
};