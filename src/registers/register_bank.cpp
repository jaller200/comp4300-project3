#include "registers/register_bank.hpp"

// MARK: -- Registration

// Constructor
RegisterBank::RegisterBank() {
    this->m_arrRegisters.fill(0);
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