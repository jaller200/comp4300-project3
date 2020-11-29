#pragma once

#include "types.hpp"

/**
 * A buffer to hold information about a decoded instruction after
 * the instruction decode stage.
 * 
 * This buffer is essentially a lightweight Instruction class, although
 * for the time being I would prefer to keep that separate from this.
 * 
 * One possible solution in the future is to just store an Instruction object
 * here, but that carries any overhead associated - especially since all future
 * buffers only contain small bits of that.
 * 
 * For now, let's just keep the information separate.
 */
struct InstructionDecodeBuffer {

    /** The funct for any R-Type instructions. */
    word_t wFunct;

    /** An immediate (if needed). Can be an address, shift amount, offset, value, etc. */
    word_t wImmediate;

    /** The opcode. */
    word_t wOpcode;

    /** The destination register number (RD for R-Type, RT for I-Type). -1 if unused */
    sword_t wRegDest;

    /** The source #1 register number (RS). -1 if unused */
    sword_t wRegSrc1;

    /** The source #2 register number (typically RT for R-Type). Can be -1 if unused */
    sword_t wRegSrc2;

    /** The value of the source RS register, if used (0 otherwise). */
    word_t wValSrc1;

    /** The value of the source RT register, if used (0 otherwise). */
    word_t wValSrc2;
};