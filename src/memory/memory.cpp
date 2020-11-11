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
bool Memory::readByte(addr_t addr, byte_t& byte) const {

    auto offset = this->addressToOffset(addr, sizeof(byte_t));
    if (offset == -1) return false;

    byte = this->m_vecMemory[offset];
    return true;
}

// Read a word from memory
bool Memory::readWord(addr_t addr, word_t& word) const {

    // Now get the offset
    auto offset = this->addressToOffset(addr, sizeof(word_t));
    if (offset == -1) return false;

    // Get the starting address
    word = this->m_vecMemory[offset+0]
            | (this->m_vecMemory[offset+1] << 8)
            | (this->m_vecMemory[offset+2] << 16)
            | (this->m_vecMemory[offset+3] << 24);

    return true;
}

// Write a byte to memory
bool Memory::writeByte(addr_t addr, byte_t byte) {

    auto offset = this->addressToOffset(addr, sizeof(byte_t));
    if (offset == -1) return false;

    this->m_vecMemory[offset] = byte;
    return true;
}

// Write a word to memory
bool Memory::writeWord(addr_t addr, word_t word) {

    // Now get the offset
    auto offset = this->addressToOffset(addr, sizeof(word_t));
    if (offset == -1) return false;

    this->m_vecMemory[offset+0] = word & 0xFF;
    this->m_vecMemory[offset+1] = (word >> 8) & 0xFF;
    this->m_vecMemory[offset+2] = (word >> 16) & 0xFF;
    this->m_vecMemory[offset+3] = (word >> 24) & 0xFF;
    return true;
}


// MARK: -- Size Methods

// Returns the data segment size
size_t Memory::getDataSize() const {
    return this->m_szDataSegment;
}

// Returns the text segment size
size_t Memory::getTextSize() const {
    return this->m_szTextSegment;
}

// Returns the total memory size
size_t Memory::getTotalSize() const {
    return this->m_szDataSegment + this->m_szTextSegment;
}


// MARK: -- Private Methods

// Converts an address to an offset
std::vector<uint8_t>::size_type Memory::addressToOffset(addr_t addr, size_t expSize) const {

    addr_t memoryStart = MEM_USER_START;
    addr_t memoryEnd = MEM_USER_START + this->getTotalSize();

    if (addr < memoryStart || addr > memoryEnd - expSize)
        return -1;

    return addr - memoryStart;
}