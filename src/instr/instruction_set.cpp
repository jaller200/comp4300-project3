#include "instr/instruction_set.hpp"

#include <algorithm>

// MARK: -- Registration Methods

// Registers an R-type instruction.
bool InstructionSet::registerRType(const std::string& name, word_t opcode, word_t funct, std::unique_ptr<InstructionParser> parser) {
    
    // First make sure we have a name
    //std::string nameStr = 
    return true;
}