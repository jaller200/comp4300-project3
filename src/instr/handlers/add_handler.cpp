#include "instr/handlers/add_handler.hpp"


// Handles the post decode
void AddHandler::onPostDecode(InstructionDecodeBuffer& decodeBuffer, const RegisterBank& registerBank, Memory::addr_t& PC) {
    // Not a branch, nothing to do
}

// Handles the execution
word_t AddHandler::onExecute(const InstructionDecodeBuffer& decodeBuffer) {
    
    // Add the words
    return (decodeBuffer.wValSrc1 + decodeBuffer.wValSrc2);
}

// Handles the memory stage
word_t AddHandler::onMemory(const ExecutionBuffer& executionBuffer, const Memory& memory) {
    
    // Nothing to do here
    return 0;
}