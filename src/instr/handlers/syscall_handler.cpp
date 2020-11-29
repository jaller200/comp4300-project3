#include "instr/handlers/syscall_handler.hpp"

#include "spdlog/spdlog.h"

#include "registers/register_bank.hpp"

// Handles the post decode
void SyscallHandler::onPostDecode(InstructionDecodeBuffer& decodeBuffer, const RegisterBank& registerBank, Memory::addr_t& PC) {

    // Handle the system call here
    this->handleSystemCall(decodeBuffer, registerBank);

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
word_t SyscallHandler::onExecute(const InstructionDecodeBuffer& decodeBuffer) {
    return 0;
}

// Handles the memory stage
word_t SyscallHandler::onMemory(const ExecutionBuffer& executionBuffer, const Memory& memory) {
    return 0;
}


// MARK: -- Private Syscall Methods

void SyscallHandler::handleSystemCall(InstructionDecodeBuffer& decodeBuffer, const RegisterBank& registerBank) {

    // First, get the syscall type from $v0 (2)
    word_t type;
    if (!registerBank.readRegister(2, type)) {
        spdlog::critical("SIGSYS: Bad argument for SYSCALL type");
        exit(1);
    }

    // Now, handle based on the type
    switch (type) {

        // Exit
        case 10: {
            decodeBuffer.bExit = true;
            break;
        }

        default: {
            spdlog::critical("SIGSYS: Bad SYSCALL type: {}", type);
            exit(1);
        }
    }
}