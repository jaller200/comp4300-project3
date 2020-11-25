#include "instr/instruction_set.hpp"

// MARK: -- Construction

// Construction
InstructionSet::InstructionSet() {
    this->m_arrOpcodeType.fill(InstructionType::UNKNOWN);
}


// MARK: -- Registration Methods

// Registers an R-type instruction.
bool InstructionSet::registerRType(const std::string& name, word_t opcode, word_t funct, std::unique_ptr<InstructionParser> parser) {
    
    // First make sure we have a name
    return true;
}


// MARK: -- Getters

// Returns the type for the opcode
InstructionType InstructionSet::getType(word_t opcode) const {
    
    // Verify that we are within our bounds, and then return
    if (opcode > Instruction::LIMIT_OPCODE) return InstructionType::UNKNOWN;
    return this->m_arrOpcodeType[opcode];
}