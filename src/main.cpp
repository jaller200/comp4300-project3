#include <iostream>
#include <memory>

#include "memory/memory.hpp"
#include "types.hpp"

/**
 * The entry point to the program.
 * @param argc The arguments count
 * @param argv The arguments list
 */
int main(int argc, char ** argv) {

    // Testing the memory...
    std::unique_ptr<Memory> memory(new Memory(0x1000, 0x1000));

    // Get the memory
    word_t word;
    memory->readWord(0x1000, word);
    std::cout << "Word (before): " << std::hex << "0x" << (int) word << std::dec << std::endl;

    byte_t byte;
    memory->readByte(0x1000, byte);
    std::cout << "Byte (before): " << std::hex << "0x" << (int) byte << std::dec << std::endl;

    memory->writeWord(0x1000, 0x12345678);
    memory->readWord(0x1000, word);
    std::cout << "Word (after): " << std::hex << "0x" << (int) word << std::dec << std::endl;

    memory->readByte(0x1000, byte);
    std::cout << "Byte (after): " << std::hex << "0x" << (int) byte << std::dec << std::endl;

    return 0;
}