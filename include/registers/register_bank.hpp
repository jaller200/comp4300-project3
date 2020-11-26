#pragma once

#include <array>

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

    /** The register bank. */
    std::array<word_t, NUM_REGISTERS> m_arrRegisters;
};