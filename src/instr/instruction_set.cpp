#include "instr/instruction_set.hpp"

// MARK: -- Registration Methods

// Registers an R-type instruction.
bool InstructionSet::registerRType(const std::string& name, word_t opcode, word_t funct, std::unique_ptr<InstructionParser> parser) {
    return false;
}