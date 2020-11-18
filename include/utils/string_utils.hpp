#pragma once

#include <string>

/**
 * A namespace containing a number of string utility methods.
 */
namespace StringUtils {

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