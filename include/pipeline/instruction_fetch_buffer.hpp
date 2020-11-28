#pragma once

#include "types.hpp"

/**
 * A buffer to hold information from the instruction fetch stage.
 */
struct InstructionFetchBuffer { 

    /** The read instruction. */
    word_t wInstruction;
};