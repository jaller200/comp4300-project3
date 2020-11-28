#include "simulator.hpp"

#include <exception>

#include "spdlog/spdlog.h"

#include "instr/instruction_encoder.hpp"

// MARK: -- Construction

// Constructs the simulator
Simulator::Simulator(std::unique_ptr<InstructionSet> instrSet, std::unique_ptr<Memory> memory, std::unique_ptr<RegisterBank> registerBank)
: m_instrSet(std::move(instrSet))
, m_memory(std::move(memory))
, m_registerBank(std::move(registerBank))
{ 
    if (this->m_instrSet == nullptr)
        throw std::invalid_argument("Cannot pass a null instruction set to the simulator");

    if (this->m_memory == nullptr)
        throw std::invalid_argument("Cannot pass a null memory to the simulator");

    if (this->m_registerBank == nullptr)
        throw std::invalid_argument("Cannot pass a null register bank to the simulator");
}


// MARK: -- Execution Methods

// Runs the simulator
void Simulator::run() { 

    // First, create our buffers
    InstructionFetchBuffer oldBufferIF;
    InstructionFetchBuffer newBufferIF;

    InstructionDecodeBuffer oldBufferID;
    InstructionDecodeBuffer newBufferID;

    ExecutionBuffer oldBufferEX;
    ExecutionBuffer newBufferEX;
    
    MemoryBuffer oldBufferMEM;
    MemoryBuffer newBufferMEM;

    // Now, set PC to the start of our text section
    Memory::addr_t PC = Memory::MEM_USER_START;

    // Initialise our stats as well
    word_t clockCycles = 0;
    word_t instrCountTotal = 0;
    word_t instrCountNOP = 0;

    // Finally, we can begin.
    bool running = true;            // This will keep track of whether we are still running
    while (running) {
    
        // First, backup the old buffer and fetch the new instruction
        oldBufferIF = newBufferIF;
        newBufferIF = this->handleInstructionFetch(PC);

        // Now, decode our instruction
        oldBufferID = newBufferID;
        newBufferID = this->handleInstructionDecode(newBufferIF, PC);

        // Next, execute the instruction
        oldBufferEX = newBufferEX;
        newBufferEX = this->handleExecution(newBufferID);

        // After this, handle any memory
        oldBufferMEM = newBufferMEM;
        newBufferMEM = this->handleMemory(newBufferEX);

        // Finally, handle the write back stage
        this->handleWriteBack(newBufferMEM);
    }

    // Now print our stats
    spdlog::info("Total Clock Cycles: {}", clockCycles);
    spdlog::info("Total NOP Count: {}", instrCountNOP);
    spdlog::info("Total Instruction Count: {}", instrCountTotal);
}


// MARK: -- Private Handler Methods

// Handles the instruction execution
ExecutionBuffer Simulator::handleExecution(const InstructionDecodeBuffer& decodeBuffer) {

    // First, detect any data hazards

    // Next, TODO: Call children methods
    ExecutionBuffer buffer;

    buffer.wRegDest = decodeBuffer.wRegDest;
    buffer.wRegValue = decodeBuffer.wValSrc2;
    return buffer;
}

// Handles the instruction decode
InstructionDecodeBuffer Simulator::handleInstructionDecode(const InstructionFetchBuffer& fetchBuffer, Memory::addr_t& PC) {

    // First, get our instruction type
    word_t opcode = fetchBuffer.wInstruction & ((1 << 6) - 1);
    InstructionType instrType = this->m_instrSet->getType(opcode);

    if (instrType == InstructionType::UNKNOWN) {
        spdlog::critical("SIGILL: Attempting to decode an invalid or illegal instruction!");
        exit(1);
    }

    InstructionDecodeBuffer buffer;
    return buffer;

    // TODO: Decode further via handler.

    // Now decode our instruction
    /*Instruction instr = InstructionEncoder::decode(fetchBuffer.wInstruction, instrType);

    // Finally, create our buffer
    InstructionDecodeBuffer buffer;
    buffer.wOpcode = opcode;

    switch (instr.getType()) {

        // I-Format
        case InstructionType::I_FORMAT: {

            // Populate the buffer
            buffer.wFunct = 0;
            buffer.wImmediate = instr.getImmediate();
            buffer.wRegDest = instr.getRt();
            buffer.wRegSrc1 = instr.getRs();
            buffer.wRegSrc2 = 0;
            buffer.wValSrc2 = 0;

            // Try to read our value
            if (!this->m_registerBank->readRegister(buffer.wRegSrc1, buffer.wValSrc1)) {
                spdlog::critical("SIGILL: Attempting to decode an I-Type instruction with an invalid register source: '" + std::to_string(buffer.wRegSrc1) + "'");
                exit(1);
            }
            break;
        }

        // J-Format
        case InstructionType::J_FORMAT: {

            // Populate the buffer
            buffer.wFunct = 0;
            buffer.wImmediate = instr.getAddr();
            buffer.wRegDest = 0;
            buffer.wRegSrc1 = 0;
            buffer.wRegSrc2 = 0;
            buffer.wValSrc1 = 0;
            buffer.wValSrc2 = 0;
            break;
        }

        // R-Format
        case InstructionType::R_FORMAT: {

            // Populate the buffer
            buffer.wFunct = instr.getFunct();
            buffer.wImmediate = instr.getShamt();
            buffer.wRegDest = instr.getRd();
            buffer.wRegSrc1 = instr.getRs();
            buffer.wRegSrc2 = instr.getRt();
            
            // Try to read our values
            if (!this->m_registerBank->readRegister(buffer.wRegSrc1, buffer.wValSrc1)) {
                spdlog::critical("SIGILL: Attempting to decode an R-Type instruction with an invalid register source #1: '" + std::to_string(buffer.wRegSrc1) + "'");
                exit(1);
            }
            
            if (!this->m_registerBank->readRegister(buffer.wRegSrc2, buffer.wValSrc2)) {
                spdlog::critical("SIGILL: Attempting to decode an R-Type instruction with an invalid register source #2: '" + std::to_string(buffer.wRegSrc2) + "'");
                exit(1);
            }
            break;
        }

        // We should never get here
        default: {
            spdlog::critical("SIGILL: Attempting to decode a malformed instruction");
            exit(1);
        }
    }

    // Now that we are here, we have our buffer populated
    return buffer;*/
}

// Handles the instruction fetch
InstructionFetchBuffer Simulator::handleInstructionFetch(Memory::addr_t& PC) {

    // First, check if we are within our memory bounds
    if (PC - Memory::MEM_USER_START >= this->m_memory->getTextSize()) {
        spdlog::critical("SIGSEGV: Attempting to read instruction outside of text segment!");
        exit(1);
    }

    // Also make sure our address is divisible by 4
    if (PC % 4 != 0) {
        spdlog::critical("SIGILL: Program attempting to read memory not along word boundary!");
        exit(1);
    }

    // Get our instruction
    InstructionFetchBuffer buffer;
    this->m_memory->readWord(PC, buffer.wInstruction);

    // Update PC and return
    PC += 4;
    return buffer;
}

// Handle the instruction memory stage
MemoryBuffer Simulator::handleMemory(const ExecutionBuffer& executionBuffer) {

    // TODO: Call children methods for any memory access
    MemoryBuffer buffer;

    // If we are an R-Type, we have no memory stage
    if (this->m_instrSet->getType(executionBuffer.wOpcode) == InstructionType::R_FORMAT)
        buffer.wOutput = executionBuffer.wOutput;

    // Copy opcode and the register destination
    buffer.wOpcode = executionBuffer.wOpcode;
    buffer.wRegDest = executionBuffer.wRegDest;
    return buffer;
}

// Handle the instruction write back stage
void Simulator::handleWriteBack(const MemoryBuffer& memoryBuffer) {

    // TODO: Call children methods
}