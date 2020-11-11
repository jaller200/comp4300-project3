#include <iostream>
#include <memory>

#include "memory/memory.h"
#include "types.h"

/**
 * The entry point to the program.
 * @param argc The arguments count
 * @param argv The arguments list
 */
int main(int argc, char ** argv) {

    // Testing the memory...
    std::unique_ptr<Memory> memory(new Memory(0x1000, 0x1000));

    // Get the memory
    byte_t data;
    memory->readByte(0x1000, data);
    std::cout << "Byte (before): " << (int) data << std::endl;

    memory->writeByte(0x1000, 1);
    memory->readByte(0x1000, data);
    std::cout << "Byte (after): " << (int) data << std::endl;

    return 0;
}