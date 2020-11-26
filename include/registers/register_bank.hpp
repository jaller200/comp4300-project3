#pragma once

#include <array>
#include <string>
#include <unordered_map>

#include "types.hpp"

/**
 * A register bank mapping numbers to types.
 */
class RegisterBank {
public:

    // MARK: -- Public Constants

    /** The number of registers. */
    static constexpr word_t NUM_REGISTERS = 32;


    // MARK: -- Construction
    RegisterBank();
    ~RegisterBank() = default;


    // MARK: -- Static Conversion Methods

    /**
     * Converts a string such a "$0" or "$zero" to a register value.
     * 
     * All registers MUST beging with "$". If the string does not, this will
     * return -1.
     * 
     * In addition, if the name is not found, or the number is out of bounds,
     * this will also return -1.
     * 
     * @param str The string to convert
     * @return The register (0-31) on success, -1 otherwise
     */
    static sword_t getRegister(const std::string& str);


    // MARK: -- Register I/O Methods

    /**
     * Reads a register (0-31) from the register bank.
     * 
     * Note that while we are unable to write to register $0 (hardwired), we
     * are quite free to read it.
     * 
     * @param num The register number
     * @return True if the value was read properly, false otherwise
     */
    bool readRegister(word_t num, word_t& value) const;

    /**
     * Writes a register (1-31) to the register bank.
     * 
     * Note that we CANNOT write to register 0 as it is always
     * hardwired to stay 0.
     * 
     * @param num The register number
     * @return True if the value was written properly, false otherwise
     */
    bool writeRegister(word_t num, word_t value);

private:

    // MARK: -- Private Variables

    /** The register bank. */
    std::array<word_t, NUM_REGISTERS> m_arrRegisters;
};