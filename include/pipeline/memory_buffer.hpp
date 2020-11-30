#pragma once

#include "types.hpp"

/**
 * A buffer between the memory and write back stages
 * of the pipeline.
 */
struct MemoryBuffer {

    /** The function. */
    word_t wFunct;

    /** The opcode. */
    word_t wOpcode;

    /** The output of the ALU or memory if applicable. */
    word_t wOutput;

    /** The destination register number. */
    word_t wRegDest;
};