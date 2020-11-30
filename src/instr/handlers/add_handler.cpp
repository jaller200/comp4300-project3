#include "instr/handlers/add_handler.hpp"


// Handles the post decode
void AddHandler::onDecode(InstructionDecodeBuffer& decodeBuffer, const RegisterBank& registerBank, Memory& memory, Memory::addr_t& PC) {
}

// Handles the execution
word_t AddHandler::onExecute(const InstructionDecodeBuffer& decodeBuffer) {
    
    // Add the words
    return (decodeBuffer.wValSrc1 + decodeBuffer.wValSrc2);
}

// Handles the memory stage
word_t AddHandler::onMemory(const ExecutionBuffer& executionBuffer, const Memory& memory) {
    return executionBuffer.wOutput;
}