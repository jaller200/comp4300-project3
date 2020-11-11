#include "memory/memory.h"

// MARK: -- Construction

// Constructor
Memory::Memory(size_t dataSize, size_t textSize)
: m_szDataSegment(dataSize)
, m_szTextSegment(textSize)
{ 
    // Initialise our vector
    size_t totalSize = this->m_szDataSegment + this->m_szTextSegment;
    this->m_vecMemory.reserve(totalSize);
}


// MARK: -- I/O Methods

// Read a byte from memory
bool Memory::readByte(addr_t addr, byte_t& data) const {

    auto offset = this->addressToOffset(addr);
    if (offset == -1) return false;

    data = this->m_vecMemory[offset];
    return true;
}

// Read a word from memory
bool Memory::readWord(addr_t addr, word_t& data) const {

    addr_t textEnd = MEM_USER_START + this->m_szTextSegment;
    addr_t dataEnd = MEM_USER_START + this->m_szTextSegment + this->m_szDataSegment;

    // Make sure we're within bounds
    if (addr < MEM_USER_START || addr >= dataEnd) return false;

    // Make sure we're not writing along the boundary of text and data
    if (addr < textEnd && addr+4 >= textEnd) return false;

    // Now get the offset
    auto offset = this->addressToOffset(addr);
    if (offset == -1) return false;

    // Get the starting address
    data = this->m_vecMemory[offset+0]
            | (this->m_vecMemory[offset+1] << 8)
            | (this->m_vecMemory[offset+2] << 16)
            | (this->m_vecMemory[offset+3] << 24);

    return true;
}

// Write a byte to memory
bool Memory::writeByte(addr_t addr, byte_t data) {

    auto offset = this->addressToOffset(addr);
    if (offset == -1) return false;

    this->m_vecMemory[offset] = data;
    return true;
}

// Write a word to memory
bool Memory::writeWord(addr_t addr, word_t data) {

    addr_t textEnd = MEM_USER_START + this->m_szTextSegment;
    addr_t dataEnd = MEM_USER_START + this->m_szTextSegment + this->m_szDataSegment;

    // Make sure we're within bounds
    if (addr < MEM_USER_START || addr >= dataEnd) return false;

    // Make sure we're not writing along the boundary of text and data
    if (addr < textEnd && addr+4 >= textEnd) return false;

    // Now get the offset
    auto offset = this->addressToOffset(addr);
    if (offset == -1) return false;

    this->m_vecMemory[offset+0] = data & 0xFF;
    this->m_vecMemory[offset+1] = (data >> 8) & 0xFF;
    this->m_vecMemory[offset+2] = (data >> 16) & 0xFF;
    this->m_vecMemory[offset+3] = (data >> 24) & 0xFF;
    return true;
}


// MARK: -- Private Methods

// Converts an address to an offset
std::vector<uint8_t>::size_type Memory::addressToOffset(addr_t addr) const {

    addr_t memoryStart = MEM_USER_START;
    addr_t memoryEnd = MEM_USER_START + this->m_szDataSegment + this->m_szTextSegment;

    if (addr < memoryStart || addr >= memoryEnd)
        return -1;

    return addr - memoryStart;
}