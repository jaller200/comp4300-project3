#include "instr/handlers/sll_handler.hpp"

#include "registers/register_bank.hpp"

// Handles the post decode
void SllHandler::onDecode(InstructionDecodeBuffer& decodeBuffer, const RegisterBank& registerBank, Memory& memory, Memory::addr_t& PC) {
}

// Handles the execution
word_t SllHandler::onExecute(const InstructionDecodeBuffer& decodeBuffer) {    
    return (decodeBuffer.wValSrc2 << decodeBuffer.wImmediate);
}

// Handles the memory stage
word_t SllHandler::onMemory(const ExecutionBuffer& executionBuffer, const Memory& memory) {
    return executionBuffer.wOutput;
}