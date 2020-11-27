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

    /** An immediate (if needed). Can be an address, offset, value, etc. */
    word_t wImmediate;

    /** The opcode. */
    word_t wOpcode;

    /** The destination register number. */
    word_t wRegDest;

    /** The source RS register number. */
    word_t wRegSrc1;

    /** The source RT register number. */
    word_t wRegSrc2;

    /** The value of the source RS register. */
    word_t wValSrc1;

    /** The value of the source RT register. */
    word_t wValSrc2;
};