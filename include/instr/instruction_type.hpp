#pragma once

/**
 * The various instruction types for MIPS.
 */
enum class InstructionType {

    // Common Formats
    R_FORMAT,       // General, most common type for arithmetic instructions
    I_FORMAT,       // Instructions that use an immediate value
    J_FORMAT,       // Jump instructions
    
    // Other / Unknown Formats
    NOP,            // NOP instruction (0x00000000)
    UNKNOWN,        // Unknown instructon (0xFFFFFFFF)
};