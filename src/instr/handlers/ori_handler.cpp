#include "instr/handlers/ori_handler.hpp"

#include "registers/register_bank.hpp"

// Handles the post decode
void OriHandler::onDecode(InstructionDecodeBuffer& decodeBuffer, const RegisterBank& registerBank, Memory& memory, Memory::addr_t& PC) {
}

// Handles the execution
word_t OriHandler::onExecute(const InstructionDecodeBuffer& decodeBuffer) {    
    return (decodeBuffer.wValSrc1 | decodeBuffer.wImmediate);
}

// Handles the memory stage
word_t OriHandler::onMemory(const ExecutionBuffer& executionBuffer, const Memory& memory) {
    return executionBuffer.wOutput;
}