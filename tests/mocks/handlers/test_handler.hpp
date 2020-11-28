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
     * Handles an instruction decode.
     * @param fetchBuffer The fetch buffer
     * @param PC The program counter
     * @param registerBank The register bank
     * @return The decode buffer
     */
    InstructionDecodeBuffer handleInstructionDecode(const InstructionFetchBuffer& fetchBuffer, Memory::addr_t& PC, const RegisterBank& registerBank) override;
};