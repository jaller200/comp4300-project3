#pragma once

#include <stdexcept>

/**
 * A basic exception for syntax errors.
 */
class SyntaxError : public std::runtime_error {
public:

    /**
     * Creates a syntax error.
     * @param msg The base message
     */
    SyntaxError(const std::string& msg)
        : std::runtime_error(msg)
        , m_strFilename("")
        , m_iLineNumber(-1)
    { }

    /**
     * Creates a syntax error with information about the filename
     * and line number the error occurred on.
     * @param msg The base message
     * @param filename The filename
     * @param lineNumber The line number
     */
    SyntaxError(const std::string& msg, const std::string& filename, int lineNumber)
        : std::runtime_error(msg)
        , m_strFilename(filename)
        , m_iLineNumber(lineNumber)
    { }

private:

    // MARK: -- Private Variables

    /** The filename that the syntax error is in. */
    std::string m_strFilename;

    /** The line number the syntax error is on. */
    int m_iLineNumber;
};