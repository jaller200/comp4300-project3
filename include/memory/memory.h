#pragma once

#include "types.h"

#include <cstddef>
#include <cstdint>
#include <vector>

/**
 * The memory of the simulator.
 */
class Memory {
public:

    // Typedefs
    using addr_t = word_t;                  // An address reference    

private:

    // MARK: -- Private Constants
    
    /** The start of the userland memory section. */
    static constexpr addr_t MEM_USER_START = 0x1000;


    // MARK: -- Private Variables

    // Memory
    std::vector<uint8_t> m_vecMemory;       // The main memory

    // Segment Sizes
    size_t m_szDataSegment;                 // The data segment size (in bytes)
    size_t m_szTextSegment;                 // The text segment size (in bytes)

    
    // MARK: -- Private Methods

    /**
     * Returns the logical offset into our memory from a virtual
     * address.
     * @param addr The address to convert
     * @return The offset into the array, or -1 for an invalid address
     */
    std::vector<uint8_t>::size_type addressToOffset(addr_t addr) const;

public:

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
    bool readByte(addr_t addr, byte_t& data) const;

    /**
     * Writes a byte to an address.
     * @param addr The address to write to
     * @param data The data to write
     * @return Whether or not the write was successful
     */
    bool writeByte(addr_t addr, byte_t data);
};