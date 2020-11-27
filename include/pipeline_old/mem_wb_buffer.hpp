#pragma once

#include "types.hpp"

/**
 * A buffer between the memory and write back stages
 * of the pipeline.
 */
struct MEMWBBuffer {

    /** The output from the ALU. */
    word_t wALUOut;

    /** The memory data register. */
    word_t wMDR;

    /** The opcode. */
    word_t wOpcode;

    /** The destination register number. */
    word_t wRd;
};