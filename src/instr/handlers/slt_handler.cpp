#include "instr/handlers/slt_handler.hpp"

#include <iostream>

#include "registers/register_bank.hpp"

// Handles the post decode
void SltHandler::onDecode(InstructionDecodeBuffer& decodeBuffer, const RegisterBank& registerBank, Memory& memory, Memory::addr_t& PC) {
}

// Handles the execution
word_t SltHandler::onExecute(const InstructionDecodeBuffer& decodeBuffer) {

    //std::cout << "SLL: Comparing Val 1 (" << decodeBuffer.wValSrc1 << ") with Val 2 (" << decodeBuffer.wValSrc2 << ")" << std::endl;
    return (static_cast<sword_t>(decodeBuffer.wValSrc1) < static_cast<sword_t>(decodeBuffer.wValSrc2)) ? 1 : 0;
}

// Handles the memory stage
word_t SltHandler::onMemory(const ExecutionBuffer& executionBuffer, const Memory& memory) {
    return executionBuffer.wOutput;
}