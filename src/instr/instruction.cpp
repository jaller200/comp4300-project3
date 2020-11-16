#include "instr/instruction.hpp"

// MARK: -- Construction
Instruction::Instruction()
: m_wAddr(0)
, m_wFunct(0)
, m_wImmediate(0)
, m_wOpcode(0)
, m_wRegRd(0)
, m_wRegRs(0)
, m_wRegRt(0)
, m_wShamt(0)
, m_type(InstructionType::UNKNOWN)
{ }


// MARK: -- Instruction Methods

// Resets the instruction
void Instruction::reset() {
    this->m_wAddr = 0;
    this->m_wFunct = 0;
    this->m_wImmediate = 0;
    this->m_wOpcode = 0;
    this->m_wRegRd = 0;
    this->m_wRegRs = 0;
    this->m_wRegRt = 0;
    this->m_wShamt = 0;
    this->m_type = InstructionType::UNKNOWN;
}


// MARK: -- Getters / Setters

// Returns the address
word_t Instruction::getAddr() const {
    return this->m_wAddr;
}

// Returns the function type
word_t Instruction::getFunct() const {
    return this->m_wFunct;
}

// Returns the signed immediate value
word_t Instruction::getImmediate() const {
    return this->m_wImmediate;
}

// Returns the opcode
word_t Instruction::getOpcode() const {
    return this->m_wOpcode;
}

// Returns the destination register
word_t Instruction::getRd() const {
    return this->m_wRegRd;
}

// Returns the first source register
word_t Instruction::getRs() const {
    return this->m_wRegRs;
}

// Returns the second source register
word_t Instruction::getRt() const {
    return this->m_wRegRt;
}

// Returns the shift amount
word_t Instruction::getShamt() const {
    return this->m_wShamt;
}

// Returns the instruction type
InstructionType Instruction::getType() const {
    return this->m_type;
}

// Sets the address
bool Instruction::setAddr(word_t addr) {

    if (addr > LIMIT_ADDR) return false;
    this->m_wAddr = addr;
    return true;
}

// Sets the function type
bool Instruction::setFunct(word_t funct) {

    if (funct > LIMIT_FUNCT) return false;
    this->m_wFunct = funct;
    return true;
}

// Sets the immediate value
bool Instruction::setImmediate(word_t immediate) {

    if (immediate > LIMIT_IMM) return false;
    this->m_wImmediate = immediate;
    return true;
}

// Sets the opcode
bool Instruction::setOpcode(word_t opcode) {

    if (opcode > LIMIT_OPCODE) return false;
    this->m_wOpcode = opcode;
    return true;
}

// Sets the destination register
bool Instruction::setRd(word_t rd) {

    if (rd > LIMIT_RD) return false;
    this->m_wRegRd = rd;
    return true;
}

// Sets the first source register
bool Instruction::setRs(word_t rs) {
    
    if (rs > LIMIT_RS) return false;
    this->m_wRegRs = rs;
    return true;
}

// Sets the second source register
bool Instruction::setRt(word_t rt) {

    if (rt > LIMIT_RT) return false;
    this->m_wRegRt = rt;
    return true;
}

// Sets the shift amount
bool Instruction::setShamt(word_t shamt) {

    if (shamt > LIMIT_SHAMT) return false;
    this->m_wShamt = shamt;
    return true;
}

// Sets the instruction type
void Instruction::setType(InstructionType type) {
    this->m_type = type;
}