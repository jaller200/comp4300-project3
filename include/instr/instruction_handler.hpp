#pragma once

#include "memory/memory.hpp"
#include "pipeline/execution_buffer.hpp"
#include "pipeline/instruction_decode_buffer.hpp"
#include "pipeline/instruction_fetch_buffer.hpp"
#include "pipeline/memory_buffer.hpp"

// MARK: -- Forward Declarations
class RegisterBank;

/**
 * A base class for all instructon handlers for the simulator.
 */
class InstructionHandler {
public:

    // MARK: -- Construction

    /**
     * Virtual destructor.
     */
    virtual ~InstructionHandler() { }


    // MARK: -- Handler Methods    

    /**
     * Handles the decoding of an instruction, as well as allows the user to manipulate
     * the current program counter, for example if this is a branch.
     */
    virtual InstructionDecodeBuffer handleInstructionDecode(const InstructionFetchBuffer& fetchBuffer, Memory::addr_t& PC, const RegisterBank& registerBank) = 0;
};