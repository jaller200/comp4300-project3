#pragma once

#include <string>

// Forward Declarations
class InstructionSet;
class Memory;

/**
 * A class to read our input files.
 * 
 * Note that under better circumstances, we would not tightly couple
 * this with the memory, but due to a time shortage, we will take this route
 * for now.
 */
class FileReader {
public:

    // MARK: -- Construction
    FileReader() = default;
    ~FileReader() = default;

    
    // MARK: -- Read Methods
    
    /**
     * Reads a file into memory.
     * @param filename The filename
     * @param instrSet The instruction set
     * @param memory The memory
     * @return Whether or not the file was read successfully
     */
    bool readFile(const std::string& filename, const InstructionSet& instrSet, const Memory& memory) const;
};