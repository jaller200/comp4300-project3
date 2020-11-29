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
        newBufferEX = this->handleExecution(newBufferID, oldBufferEX, newBufferMEM);

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

// Handles the instruction decode
InstructionDecodeBuffer Simulator::handleInstructionDecode(const InstructionFetchBuffer& fetchBuffer, Memory::addr_t& PC) {

    // First, get our instruction type
    word_t opcode = fetchBuffer.wInstruction & ((1 << 6) - 1);
    InstructionType instrType = this->m_instrSet->getType(opcode);
    if (instrType == InstructionType::UNKNOWN) {
        spdlog::critical("SIGILL: Attempting to decode an invalid or illegal instruction!");
        exit(1);
    }

    // Decode the instruction
    Instruction instr = InstructionEncoder::decode(fetchBuffer.wInstruction, instrType);

    // Create the instruction buffer
    InstructionDecodeBuffer buffer;
    buffer.wOpcode = opcode;

    // Now read more depending on the type
    if (instrType == InstructionType::I_FORMAT) {

        // Get our immedate value, source register (and read it), and our destination register
        buffer.wImmediate = instr.getImmediate();
        buffer.wRegDest = instr.getRt();
        buffer.wRegSrc1 = instr.getRs();
        buffer.wRegSrc2 = -1;
        this->m_registerBank->readRegister(buffer.wRegSrc1, buffer.wValSrc1);
    }
    else if (instrType == InstructionType::J_FORMAT) {

        // Just get our address (immediate) value
        buffer.wImmediate = instr.getAddr();
        buffer.wRegDest = -1;
        buffer.wRegSrc1 = -1;
        buffer.wRegSrc2 = -1;
    }
    else if (instrType == InstructionType::R_FORMAT) {

        // Get both source registers and read them, the destination register, and the shamt (immediate)
        // as well as the funct
        buffer.wFunct = instr.getFunct();
        buffer.wImmediate = instr.getShamt();
        buffer.wRegDest = instr.getRd();
        buffer.wRegSrc1 = instr.getRs();
        buffer.wRegSrc2 = instr.getRt();
        this->m_registerBank->readRegister(buffer.wRegSrc1, buffer.wValSrc1);
        this->m_registerBank->readRegister(buffer.wRegSrc2, buffer.wValSrc2);
    }

    // Finally handle any post decoding (mainly for branches)
    InstructionHandler * handler = this->m_instrSet->getInstructionHandler(buffer.wOpcode, buffer.wFunct);
    if (handler == nullptr) {
        spdlog::critical("SIGILL: Attempting to decode an invalid or illegal instruction");
        exit(1);
    }

    // Handle any post decoding and return the buffer (generally handles branches / syscalls)
    handler->onPostDecode(buffer, *this->m_registerBank.get(), PC);
    return buffer;
}

// Handles the instruction execution
ExecutionBuffer Simulator::handleExecution(InstructionDecodeBuffer& decodeBuffer, ExecutionBuffer& oldExecutionBuffer, MemoryBuffer& newMemoryBuffer) {

    // If this cycle's decode buffer uses a register written to by last cycle's execution,
    // forward the output into the decoded buffer
    if (oldExecutionBuffer.wRegDest == decodeBuffer.wRegSrc1)
        decodeBuffer.wValSrc1 = oldExecutionBuffer.wOutput;

    if (oldExecutionBuffer.wRegDest == decodeBuffer.wRegSrc2)
        decodeBuffer.wValSrc2 = oldExecutionBuffer.wOutput;

    // If this cycle's decode buffer uses a register written to by last cycle's memory read,
    // forward the output into the decoded buffer
    if (newMemoryBuffer.wRegDest == decodeBuffer.wRegSrc1)
        decodeBuffer.wValSrc1 = newMemoryBuffer.wOutput;

    if (newMemoryBuffer.wRegDest == decodeBuffer.wRegSrc2)
        decodeBuffer.wValSrc2 = newMemoryBuffer.wOutput;

    // Create our new buffer
    ExecutionBuffer buffer;

    // Next, get our instruction handler
    InstructionHandler * handler = this->m_instrSet->getInstructionHandler(decodeBuffer.wOpcode, decodeBuffer.wFunct);
    if (handler == nullptr) {
        spdlog::critical("SIGILL: Attempting to execute an invalid or illegal instruction");
        exit(1);
    }

    // Handle our execution
    buffer.wOutput = handler->onExecute(decodeBuffer);

    // Set any remaining flags
    buffer.wFunct = decodeBuffer.wFunct;
    buffer.wOpcode = decodeBuffer.wOpcode;
    buffer.wRegDest = decodeBuffer.wRegDest;
    buffer.wRegValue = decodeBuffer.wValSrc2;
    return buffer;
}

// Handle the instruction memory stage
MemoryBuffer Simulator::handleMemory(const ExecutionBuffer& executionBuffer) {

    // Get our handler
    InstructionHandler * handler = this->m_instrSet->getInstructionHandler(executionBuffer.wOpcode, executionBuffer.wFunct);
    if (handler == nullptr) {
        spdlog::critical("SIGILL: Attempting to handle memory from an invalid or illegal instruction");
        exit(1);
    }

    // Create our buffer
    MemoryBuffer buffer;

    // Memory read instructions will put memory output here, other instructions
    // may just forward ALU output here
    buffer.wOutput = handler->onMemory(executionBuffer, *this->m_memory.get());
    
    // Set any addition information
    buffer.wFunct = executionBuffer.wFunct;
    buffer.wOpcode = executionBuffer.wOpcode;
    buffer.wRegDest = executionBuffer.wRegDest;
    return buffer;
}

// Handle the instruction write back stage
void Simulator::handleWriteBack(const MemoryBuffer& memoryBuffer) {

    // Write back everything
    if (memoryBuffer.wRegDest != -1)
        this->m_registerBank->writeRegister(memoryBuffer.wRegDest, memoryBuffer.wOutput);
}