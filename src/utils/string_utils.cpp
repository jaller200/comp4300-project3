#include "utils/string_utils.hpp"

#include <algorithm>
#include <cctype>
#include <locale>

// Trims the left whitespace off a string
std::string StringUtils::ltrim(std::string str) {

    // Erase all leading whitespace
    str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
    return str;
}