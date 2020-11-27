#pragma once

#include "types.hpp"

/**
 * A buffer between the Instruction Fetch / Instruction Decode
 * stages in a pipeline.
 */
struct IFIDBuffer {

    /** The instruction register. */
    word_t wIR;
};