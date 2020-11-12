#pragma once

#include <stdexcept>

class SyntaxException : public std::exception {
protected:

    // MARK: -- Protected Variables

    /** The message string. */
    std::string m_strMessage;

public:

    // MARK: -- Construction

    /**
     * Constructor.
     * @param message The message to include
     */
    explicit SyntaxException(const char * message)
        : m_strMessage(message)
    { }

    /**
     * Constructor.
     * @param message The message to include
     */
    explicit SyntaxException(const std::string& message)
        : m_strMessage(message)
    { }

    /**
     * Destructor.
     */
    virtual ~SyntaxException() noexcept { }


    // MARK: -- Exception Methods

    /**
     * Returns the error message.
     * @return The error message
     */
    virtual const char * what() const noexcept {
        return this->m_strMessage.c_str();
    }
};