#include "instr/handlers/lb_handler.hpp"

#include <iostream>

#include "spdlog/spdlog.h"

#include "registers/register_bank.hpp"

// Handles the post decode
void LbHandler::onPostDecode(InstructionDecodeBuffer& decodeBuffer, const RegisterBank& registerBank, Memory& memory, Memory::addr_t& PC) {
}

// Handles the execution
word_t LbHandler::onExecute(const InstructionDecodeBuffer& decodeBuffer) {
    
    // Get the address by adding the value in RS to the offset
    return decodeBuffer.wValSrc1 + static_cast<shword_t>(decodeBuffer.wImmediate);
}

// Handles the memory stage
word_t LbHandler::onMemory(const ExecutionBuffer& executionBuffer, const Memory& memory) {
    
    // Here, actually load the byte at the address into the MDR
    byte_t val;
    if (!memory.readByte(executionBuffer.wOutput, val)) {
        spdlog::critical("SIGSEGV: Unable to read memory at address {}", executionBuffer.wOutput);
        exit(1);
    }

    return val;
}