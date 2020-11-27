#pragma once

#include "types.hpp"

/**
 * A buffer between the Instruction Decode / Execution
 * stages in a pipeline.
 */
struct IDEXBuffer {

    /** The source register #1's value. */
    word_t wA;

    /** An address. */
    word_t wAddress;

    /** The source register #2's value. */
    word_t wB;

    /** The function. */
    word_t wFunct;

    /** An immediate. */
    word_t wImmediate;

    /** The opcode. */
    word_t wOpcode;

    /** The destination register number. */
    word_t wRd;

    /** The source register #1 number. */
    word_t wRs;

    /** The source register #2 number. */
    word_t wRs;

    /** The shift amount. */
    word_t wShamt;
};