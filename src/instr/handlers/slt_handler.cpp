#include "instr/handlers/slt_handler.hpp"

#include <iostream>

#include "registers/register_bank.hpp"

// Handles the post decode
void SltHandler::onPostDecode(InstructionDecodeBuffer& decodeBuffer, const RegisterBank& registerBank, Memory& memory, Memory::addr_t& PC) {
}

// Handles the execution
word_t SltHandler::onExecute(const InstructionDecodeBuffer& decodeBuffer) {
    return (decodeBuffer.wValSrc1 < decodeBuffer.wValSrc2) ? 1 : 0;
}

// Handles the memory stage
word_t SltHandler::onMemory(const ExecutionBuffer& executionBuffer, const Memory& memory) {
    return executionBuffer.wOutput;
}