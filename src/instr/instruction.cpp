#include "instr/instruction.hpp"

// MARK: -- Construction
Instruction::Instruction()
: m_funct(0)
, m_immediate(0)
, m_regRd(0)
, m_regRs(0)
, m_regRt(0)
, m_shamt(0)
, m_type(InstructionType::UNKNOWN)
{ }


// MARK: -- Instruction Methods

// Resets the instruction
void Instruction::reset() {
    this->m_funct = 0;
    this->m_immediate = 0;
    this->m_regRd = 0;
    this->m_regRs = 0;
    this->m_regRt = 0;
    this->m_shamt = 0;
    this->m_type = InstructionType::UNKNOWN;
}


// MARK: -- Getters / Setters

// Returns the function type
Instruction::funct_t Instruction::getFunct() const {
    return this->m_funct;
}

// Returns the signed immediate value
Instruction::imm_t Instruction::getImmediate() const {
    return this->m_immediate;
}

// Returns the destination register
Instruction::reg_t Instruction::getRd() const {
    return this->m_regRd;
}

// Returns the first source register
Instruction::reg_t Instruction::getRs() const {
    return this->m_regRs;
}

// Returns the second source register
Instruction::reg_t Instruction::getRt() const {
    return this->m_regRt;
}

// Returns the shift amount
Instruction::shamt_t Instruction::getShamt() const {
    return this->m_shamt;
}

// Returns the instruction type
InstructionType Instruction::getType() const {
    return this->m_type;
}

// Sets the function type
void Instruction::setFunct(Instruction::funct_t funct) {
    this->m_funct = funct;
}

// Sets the immediate value
void Instruction::setImmediate(Instruction::imm_t immediate) {
    this->m_immediate = immediate;
}

// Sets the destination register
void Instruction::setRd(Instruction::reg_t rd) {
    this->m_regRd = rd;
}

// Sets the first source register
void Instruction::setRs(Instruction::reg_t rs) {
    this->m_regRs = rs;
}

// Sets the second source register
void Instruction::setRt(Instruction::reg_t rt) {
    this->m_regRt = rt;
}

// Sets the shift amount
void Instruction::setShamt(Instruction::shamt_t shamt) {
    this->m_shamt = shamt;
}

// Sets the instruction type
void Instruction::setType(InstructionType type) {
    this->m_type = type;
}