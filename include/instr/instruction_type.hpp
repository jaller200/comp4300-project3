#pragma once

/**
 * The various instruction types for MIPS.
 */
enum class InstructionType {

    // Common Formats
    R_FORMAT,       // General, most common type for arithmetic instructions
    I_FORMAT,       // Instructions that use an immediate value
    J_FORMAT,       // Jump instructions
    PSUEDO,         // Psuedo instructions
    
    // Other / Unknown Formats
    UNKNOWN         // Unknown instructon (value is not known, 0xFFFFFFFF)
};