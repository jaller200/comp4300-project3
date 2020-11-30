#pragma once

#include "types.hpp"

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

/**
 * The memory of the simulator.
 */
class Memory {
public:

    // MARK: -- Typedefs
    using addr_t = word_t;                  // An address reference    


    // MARK: -- Public Constants
    
    /** The start of the userland memory section. */
    static constexpr addr_t MEM_USER_START = 0x1000;


    // MARK: -- Initialisation
    Memory(size_t dataSize, size_t textSize);
    ~Memory() = default;


    // MARK: -- I/O Methods

    /**
     * Reads the byte at an address.
     * @param addr The address to read from
     * @param data A placeholder to read into
     * @return Whether or not the read was successful
     */
    bool readByte(addr_t addr, byte_t& byte) const;

    /**
     * Reads a string starting at an address until it reaches a null terminator,
     * byte boundary, or runs out of memory.
     * @param addr The address to read from
     * @param str A placeholder to read characters into
     * @return Whether or not the read was successful
     */
    bool readString(addr_t addr, ascii_t& str);

    /**
     * Reads a word at an address.
     * @param addr The address to read from
     * @param data A placeholder to read into
     * @return Whether or not the read was successful
     */
    bool readWord(addr_t addr, word_t& word) const;

    /**
     * Writes a byte to an address.
     * @param addr The address to write to
     * @param data The data to write
     * @return Whether or not the write was successful
     */
    bool writeByte(addr_t addr, byte_t byte);

    /**
     * Writes a string to an address.
     * @param addr The address to write to
     * @param str The string to write
     * @return Whether or not the write was successful
     */
    bool writeString(addr_t addr, const ascii_t& str);

    /**
     * Writes a word to an address.
     * @param addr The address to write to
     * @param data The data to write
     * @return Whether or not the write was successful
     */
    bool writeWord(addr_t addr, word_t word);


    // MARK: -- Size Methods

    /**
     * Returns the data segment size in bytes.
     * @return The data segment size
     */
    size_t getDataSize() const;

    /**
     * Returns the text segment size in bytes.
     * @return The text segment size
     */
    size_t getTextSize() const;

    /**
     * Returns the total memory size in bytes.
     * @return The total memory size
     */
    size_t getTotalSize() const;

private:

    // MARK: -- Private Variables

    // Memory
    std::vector<byte_t> m_vecMemory;       // The main memory

    // Segment Sizes
    size_t m_szDataSegment;                 // The data segment size (in bytes)
    size_t m_szTextSegment;                 // The text segment size (in bytes)

    
    // MARK: -- Private Methods

    /**
     * Returns the logical offset into our memory from a virtual
     * address.
     * @param addr The address to convert
     * @param expSize The expected size in bytes (defaults to 1)
     * @return The offset into the array, or -1 for an invalid address or 
     *          address that exceeds expected size
     */
    std::vector<byte_t>::size_type addressToOffset(addr_t addr, size_t expSize = 1) const;
};