#pragma once

#include "pipeline/execution_buffer.hpp"
#include "pipeline/instruction_decode_buffer.hpp"
#include "pipeline/instruction_fetch_buffer.hpp"
#include "pipeline/memory_buffer.hpp"

// Forward Declarations


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
}