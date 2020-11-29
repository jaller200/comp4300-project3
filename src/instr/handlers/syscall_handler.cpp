#include "instr/handlers/syscall_handler.hpp"

#include <cstdio>
#include <iostream>

#include "spdlog/spdlog.h"

#include "memory/memory.hpp"
#include "registers/register_bank.hpp"

// Handles the post decode
void SyscallHandler::onPostDecode(InstructionDecodeBuffer& decodeBuffer, const RegisterBank& registerBank, Memory& memory, Memory::addr_t& PC) {

    // Handle the system call here
    this->handleSystemCall(decodeBuffer, registerBank, memory);

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

void SyscallHandler::handleSystemCall(InstructionDecodeBuffer& decodeBuffer, const RegisterBank& registerBank, Memory& memory) {

    // First, get the syscall type from $v0 (2)
    word_t type;
    if (!registerBank.readRegister(2, type)) {
        spdlog::critical("SIGSYS: Bad argument for SYSCALL type");
        exit(1);
    }

    // Now, handle based on the type
    switch (type) {

        // Print string
        case 4: {

            // Address of output: $a0
            word_t addr;
            if (!registerBank.readRegister(4, addr)) {
                spdlog::critical("SIGSYS: Invalid arguments for SYSCALL 4");
                exit(1);
            }

            // Read the string
            std::string str;
            if (!memory.readString(addr, str)) {
                spdlog::critical("SIGSEGV: Unable to read string at address {}", addr);
                exit(1);
            }

            // Print the string
            std::cout << std::string(str);
            break;
        }

        // Read string
        case 8: {

            // Address of Input: $a0
            // Max Numbr of Chars: $a1
            word_t addr;
            word_t num;

            if (!registerBank.readRegister(4, addr) || !registerBank.readRegister(5, num)) {
                spdlog::critical("SIGSYS: Invalid arguments for SYSCALL 8");
                exit(1);
            }

            // Create our buffer
            char buffer[num];
            memset(buffer, 0, num);
            std::cin >> buffer;
            
            size_t len = strlen(buffer);
            buffer[(len == num) ? num-1 : len] = '\0';

            // Now write this to the location
            for (int i = 0; i < num; ++i) {
                if (!memory.writeByte(addr+i, buffer[i])) {
                    spdlog::critical("SIGSEGV: Unable to write to memory at address {}", addr+i);
                    exit(1);
                }
            }
            break;
        }

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