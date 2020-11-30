#pragma once

#include "types.hpp"

/**
 * A buffer between the Execution and Memory stages of
 * the pipeline.
 */
struct ExecutionBuffer {

    /** The function. */
    word_t wFunct;

    /** The opcode. */
    word_t wOpcode;

    /** The output of the ALU. */
    word_t wOutput;

    /** The register destination number. */
    word_t wRegDest;

    /** The value of the second register if applicable. */
    word_t wRegValue;
};