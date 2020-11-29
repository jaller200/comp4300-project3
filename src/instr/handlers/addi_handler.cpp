#include "instr/handlers/addi_handler.hpp"

#include <iostream>

// Handles the post decode
void AddiHandler::onPostDecode(InstructionDecodeBuffer& decodeBuffer, const RegisterBank& registerBank, Memory& memory, Memory::addr_t& PC) {
}

// Handles the execution
word_t AddiHandler::onExecute(const InstructionDecodeBuffer& decodeBuffer) {

    word_t val = decodeBuffer.wValSrc1 + static_cast<shword_t>(decodeBuffer.wImmediate);
    return val;
}

// Handles the memory stage
word_t AddiHandler::onMemory(const ExecutionBuffer& executionBuffer, const Memory& memory) {
    return executionBuffer.wOutput;
}