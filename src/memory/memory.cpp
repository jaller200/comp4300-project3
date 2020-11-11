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

// Write a byte to memory
bool Memory::writeByte(addr_t addr, byte_t data) {

    auto offset = this->addressToOffset(addr);
    if (offset == -1) return false;

    this->m_vecMemory[offset] = data;
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