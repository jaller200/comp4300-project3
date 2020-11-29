#pragma once

#include <memory>

#include "instr/instruction_set.hpp"
#include "memory/memory.hpp"
#include "pipeline/execution_buffer.hpp"
#include "pipeline/instruction_decode_buffer.hpp"
#include "pipeline/instruction_fetch_buffer.hpp"
#include "pipeline/memory_buffer.hpp"
#include "registers/register_bank.hpp"

/**
 * The main simulator class. Responsible for opening, running, and
 * controlling all aspects of the simulation.
 */
class Simulator {
public:

    // MARK: -- Construction

    /**
     * Constructor.
     * @param instrSet The instruction set
     * @param memory The memory for the simulator to use
     * @param registerBank The register bank to use
     */
    Simulator(std::unique_ptr<InstructionSet> instrSet, std::unique_ptr<Memory> memory, std::unique_ptr<RegisterBank> registerBank);

    /**
     * Destructor
     */
    ~Simulator() = default;

    
    // MARK: -- Execution Methods

    /**
     * Runs the simulator.
     */
    void run();

private:

    // MARK: -- Private Dependency Variables

    /** The instruction set. */
    std::unique_ptr<InstructionSet> m_instrSet;

    /** The memory of the program. */
    std::unique_ptr<Memory> m_memory;

    /** The register bank of the program. */
    std::unique_ptr<RegisterBank> m_registerBank;


    // MARK: -- Private Handler Methods (in order of cycle)

    /**
     * Handles the instruction fetch.
     * @param PC The program counter (will be updated by 4)
     * @return A buffer with the fetched insruction.
     */
    InstructionFetchBuffer handleInstructionFetch(Memory::addr_t& PC);

    /**
     * Handles the instruction decoding.
     * @param fetchBuffer The buffer from the previous fetch
     * @param PC The program counter (will be updated if we are branching)
     * @return A buffer with the decoded instruction.
     */
    InstructionDecodeBuffer handleInstructionDecode(const InstructionFetchBuffer& fetchBuffer, Memory::addr_t& PC);

    /**
     * Handles the instruction execution.
     * @param decodeBuffer The decode buffer
     * @param oldExecutionBuffer The old execution buffer
     * @param newMemoryBuffer The new memory buffer
     * @return A buffer with any output from the execution
     */
    ExecutionBuffer handleExecution(InstructionDecodeBuffer& decodeBuffer, ExecutionBuffer& oldExecutionBuffer, MemoryBuffer& newMemoryBuffer);

    /**
     * Handles the instruction memory stage.
     * @param executionBuffer The execution buffer
     * @return A buffer with any read memory and/or data to write back
     */
    MemoryBuffer handleMemory(const ExecutionBuffer& executionBuffer);

    /**
     * Handles the instruction write back stage.
     * @param memoryBuffer The memory buffer
     */
    void handleWriteBack(const MemoryBuffer& memoryBuffer);
};