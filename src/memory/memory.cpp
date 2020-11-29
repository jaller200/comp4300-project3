#include "memory/memory.hpp"

#include <iostream>

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

// Read a string from memory
bool Memory::readString(addr_t addr, ascii_t& str) {

    // Clear the string
    str.clear();

    // For a variable list string, we actually don't know the offset, so
    // we need to constantly check. For now, assume an offset of 1
    auto offset = this->addressToOffset(addr, sizeof(char_t));
    if (offset == -1) return false;

    // Now iterate through until we hit a null terminator or end of memory
    bool specialChar = false;
    while (offset < this->m_vecMemory.capacity() && this->m_vecMemory[offset] != '\0') {

        if (specialChar) {

            // List comes from here:
            // https://stackoverflow.com/questions/10220401/rules-for-c-string-literals-escape-character
            
            // Get the char
            char ch = this->m_vecMemory[offset];
            if (ch == 'a')          str.push_back('\x07');      // alert (bell)
            else if (ch == 'b')     str.push_back('\x08');      // backspace
            else if (ch == 't')     str.push_back('\x09');      // tab
            else if (ch == 'n')     str.push_back('\x0A');      // new line (or tab feed)
            else if (ch == 'v')     str.push_back('\x0B');      // vertical tab
            else if (ch == 'f')     str.push_back('\x0C');      // form feed
            else if (ch == 'r')     str.push_back('\x0D');      // carriage return
            else if (ch == 'e')     str.push_back('\x1B');      // escape (non-standard GCC extension)
            else if (ch == '"')     str.push_back('"');         // double quote
            else if (ch == '\'')    str.push_back('\'');        // single quote
            else if (ch == '?')     str.push_back('?');         // question mark
            else if (ch == '\\')    str.push_back('\\');        // backslash
            
            // NOTE: Not handling number formats yet
        }
        else {
            if (this->m_vecMemory[offset] == '\\')
                specialChar = true;
            else {
                str.push_back(this->m_vecMemory[offset]);
            }
        }

        offset++;
    }

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

// Writes a string to memory
bool Memory::writeString(addr_t addr, const ascii_t& str) {
    
    // Get the size of the string + the null terminator
    size_t size = str.length() + 1;

    // Now get the offset
    auto offset = this->addressToOffset(addr, size);
    if (offset == -1) return false;

    // Otherwise, start at the offset and write each character
    for (const char& c : str) {
        this->m_vecMemory[offset++] = c;
    }
    this->m_vecMemory[offset] = '\0';
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