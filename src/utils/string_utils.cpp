#include "utils/string_utils.hpp"

#include <iostream>
#include <algorithm>
#include <cctype>
#include <locale>

// MARK: -- Upper / Lower Case Methods

// Converts a string to lower case
std::string StringUtils::toLowerCase(std::string str) {

    // Convert the string
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}


// MARK: -- Number Methods

// Converts a string to a number
sword_t StringUtils::toNumber(const std::string str) {

    sword_t val;
    if (str.rfind("0x", 0) == 0) {
        val = std::stoi(str, nullptr, 16);
    }
    else if (str.rfind("0b", 0) == 0) {
        val = std::stoi(str.substr(2), nullptr, 2);
    }
    else if (str.rfind("0", 0) == 0) {
        val = std::stoi(str, nullptr, 8);
    }
    else {
        val = std::stoi(str);
    }

    return val;
}


// MARK: -- Trimming Methods

// Trims the left whitespace off a string
std::string StringUtils::ltrim(std::string str) {

    // Erase all leading whitespace
    str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
    return str;
}

// Trims the right whitespace off a string
std::string StringUtils::rtrim(std::string str) {
    
    // Erase all ending whitespace
    str.erase(std::find_if(str.rbegin(), str.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), str.end());
    return str;
}

// Trims the whitespace from the start and end (yes I know it copies the string twice — I'm just lazy rn and don't want to 
// test non-copying string trims).
std::string StringUtils::trim(std::string str) {
    return ltrim(rtrim(str));
}