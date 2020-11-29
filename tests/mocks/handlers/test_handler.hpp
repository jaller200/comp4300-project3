#pragma once

#include "instr/instruction_handler.hpp"

#include "memory/memory.hpp"
#include "pipeline/execution_buffer.hpp"
#include "pipeline/instruction_decode_buffer.hpp"
#include "pipeline/instruction_fetch_buffer.hpp"
#include "pipeline/memory_buffer.hpp"

/**
 * A simple mock class for an instruction handler.
 */
class TestHandler: public InstructionHandler {
public:

    /**
     * Handles any post decoding of an instruction.
     * @param decodeBuffer The decode buffer
     * @param registerBank The register bank
     * @param PC The program counter
     */
    virtual void onPostDecode(InstructionDecodeBuffer& decodeBuffer, const RegisterBank& registerBank, Memory& memory, Memory::addr_t& PC) override;

    /**
     * Handles any execution necessary.
     * @param decodeBuffer The decoded information
     * @return The output value (ALU output) from the execution stage, or 0
     */
    virtual word_t onExecute(const InstructionDecodeBuffer& decodeBuffer) override;

    /**
     * Handles any reading / writing of memory.
     * @param executionBuffer The execution buffer information
     * @param memory Our memory
     * @return Any read memory, or 0
     */
    virtual word_t onMemory(const ExecutionBuffer& executionBuffer, const Memory& memory) override;
};