#include "instr/handlers/beq_handler.hpp"

#include <iostream>

#include "registers/register_bank.hpp"

// Handles the post decode
void BeqHandler::onDecode(InstructionDecodeBuffer& decodeBuffer, const RegisterBank& registerBank, Memory& memory, Memory::addr_t& PC) {
    
    // Get the destination register value
    word_t destVal;
    registerBank.readRegister(decodeBuffer.wRegDest, destVal);

    if (destVal == decodeBuffer.wValSrc1) {
        PC += static_cast<shword_t>(decodeBuffer.wImmediate);
    }

    // Now change this to a NOP (SLL)
    decodeBuffer.wFunct = 0;
    decodeBuffer.wImmediate = 0;
    decodeBuffer.wOpcode = 0;
    decodeBuffer.wRegDest = 0;
    decodeBuffer.wRegSrc1 = 0;
    decodeBuffer.wRegSrc2 = 0;
    decodeBuffer.wValSrc1 = 0;
    decodeBuffer.wValSrc2 = 0;
}

// Handles the execution
word_t BeqHandler::onExecute(const InstructionDecodeBuffer& decodeBuffer) {
    return 0;
}

// Handles the memory stage
word_t BeqHandler::onMemory(const ExecutionBuffer& executionBuffer, const Memory& memory) {
    return 0;
}