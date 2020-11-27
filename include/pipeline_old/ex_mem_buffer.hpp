#pragma once

#include "types.hpp"

/**
 * A buffer between the Execution and Memory stages of
 * the pipeline.
 */
struct EXMEMBuffer {

    /** The output of the ALU. */
    word_t wALUOut;

    /** The value of the RT register (if needed). */
    word_t wB;

    /** The memory data register. */
    word_t wMDR;

    /** The opcode. */
    word_t wOpcode;

    /** The destination register number. */
    word_t wRd;
};