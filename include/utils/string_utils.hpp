#pragma once

#include <string>

#include "types.hpp"

/**
 * A namespace containing a number of string utility methods.
 */
namespace StringUtils {

    // MARK: -- Case Methods

    /**
     * Converts the string to lower case.
     * @param str The string to convert
     * @return The converted string
     */
    std::string toLowerCase(std::string str);


    // MARK: -- Number Methods

    /**
     * Converts a string to a number.
     * 
     *  0x prefix   -> base 16
     *  0 prefix    -> base 8
     *  0b prefix   -> base 2
     *  other       -> base 10
     * 
     * If there is an error, an exception will be thrown.
     * 
     * @todo Turn this exception into its own error in the future
     * @param str The number string
     * @return The number, or error
     */
    sword_t toNumber(const std::string str);


    // MARK: -- Trimming Methods

    /**
     * Copies the string and trims the left whitespace off (if any).
     * @param str The string to copy and trim
     * @return The trimmed string
     */
    std::string ltrim(std::string str);

    /**
     * Copies the string and trims the right whitespace off (if any).
     * @param str The string to copy and trim
     * @return The trimmed string
     */
    std::string rtrim(std::string str);

    /**
     * Copies and trims the whitespace from the start and end of a string.
     * @param str The string to copy and trim
     * @return The trimmed string
     */
    std::string trim(std::string str);
}