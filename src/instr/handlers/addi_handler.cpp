#include "instr/handlers/addi_handler.hpp"


// Handles the post decode
void AddiHandler::onPostDecode(InstructionDecodeBuffer& decodeBuffer, const RegisterBank& registerBank, Memory::addr_t& PC) {
    // Not a branch, nothing to do
}

// Handles the execution
word_t AddiHandler::onExecute(const InstructionDecodeBuffer& decodeBuffer) {
    
    // Add the words
    return (decodeBuffer.wValSrc1 + static_cast<shword_t>(decodeBuffer.wImmediate));
}

// Handles the memory stage
word_t AddiHandler::onMemory(const ExecutionBuffer& executionBuffer, const Memory& memory) {
    
    // Nothing to do here
    return 0;
}