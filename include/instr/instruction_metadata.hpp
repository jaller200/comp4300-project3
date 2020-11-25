#pragma once

#include <string>

/**
 * Metadata for instructions, including name, parsers, and the
 * instruction ID - a joining of the opcode and (optionally) function.
 */
struct InstructionMetadata {

    /** The instruction name. */
    std::string strName;
};