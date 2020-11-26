#include "registers/register_bank.hpp"

#include <string>
#include <unordered_map>

#include "utils/string_utils.hpp"

// MARK: -- Static Variables

// A mapping of register names to values
static std::unordered_map<std::string, word_t> sm_mapNameToRegister = {
    { "$zero", 0 },
    { "$at", 1 },
    { "$v0", 2 }, { "$v1", 3 },
    { "$a0", 4 }, { "$a1", 5 }, { "$a2", 6 }, { "$a3", 7 },
    { "$t0", 8 }, { "$t1", 9 }, { "$t2", 10 }, { "$t3", 11 }, { "$t4", 12 }, { "$t5", 13 }, { "$t6", 14 }, { "$t7", 15 },
    { "$s0", 16 }, { "$s1", 17 }, { "$s2", 18 }, { "$s3", 19 }, { "$s4", 20 }, { "$s5", 21 }, { "$s6", 22 }, { "$s7", 23 },
    { "$t8", 24 }, { "$t9", 25 },
    { "$k0", 26 }, { "$k1", 27 },
    { "$gp", 28 },
    { "$sp", 29 },
    { "$fp", 30 },
    { "$ra", 31 }
};


// MARK: -- Registration

// Constructor
RegisterBank::RegisterBank() {
    this->m_arrRegisters.fill(0);
}


// MARK: -- Static Conversion Methods

// Converts a register string to a register name
sword_t RegisterBank::getRegister(const std::string& str) {

    // Trim the string and convert to lower case. All registers must have at least 2 characters
    // Also make sure we don't have whitespace before a valid stirng
    std::string registerName = StringUtils::trim(str);
    if (registerName != str) return -1;

    registerName = StringUtils::toLowerCase(registerName);
    if (registerName.length() < 2) return -1;

    // Check if we're actually a register
    if (registerName.at(0) != '$') return -1;

    // Now, check if the substring is a numerical value. If so, just return that.
    std::string strNumber = registerName.substr(1);
    if (std::find_if(strNumber.begin(), strNumber.end(), [](unsigned char c) { return !std::isdigit(c); }) == strNumber.end()) {

        // We have a numerical value, try to convert
        word_t val = std::stoi(strNumber);
        return (val >= NUM_REGISTERS) ? -1 : val;
    }

    // If we are here, this is not a numerical value, so look for the name
    auto val = sm_mapNameToRegister.find(registerName);
    return (val == sm_mapNameToRegister.end()) ? -1 : val->second;
}


// MARK: -- Register I/O Methods

// Reads a register
bool RegisterBank::readRegister(word_t num, word_t& value) const {
    
    if (num >= NUM_REGISTERS) return false;
    value = this->m_arrRegisters[num];
    return true;
}

// Writes a register
bool RegisterBank::writeRegister(word_t num, word_t value) {

    if (num < 1 || num >= NUM_REGISTERS) return false;
    this->m_arrRegisters[num] = value;
    return true;
}