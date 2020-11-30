#include "instr/handlers/lui_handler.hpp"

#include <iostream>

#include "registers/register_bank.hpp"

// Handles the post decode
void LuiHandler::onDecode(InstructionDecodeBuffer& decodeBuffer, const RegisterBank& registerBank, Memory& memory, Memory::addr_t& PC) {
}

// Handles the execution
word_t LuiHandler::onExecute(const InstructionDecodeBuffer& decodeBuffer) {
    
    // Shift left 16 bits and return
    return (decodeBuffer.wImmediate << 16);
}

// Handles the memory stage
word_t LuiHandler::onMemory(const ExecutionBuffer& executionBuffer, const Memory& memory) {
    
    // Just return the address
    return executionBuffer.wOutput;
}