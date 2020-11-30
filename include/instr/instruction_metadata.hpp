#pragma once

#include <memory>
#include <string>

#include "instr/instruction_type.hpp"
#include "types.hpp"

// MARK: -- Forward Declarations
class InstructionHandler;
class InstructionParser;

/**
 * Metadata for instructions, including name, parsers, and the
 * instruction ID - a joining of the opcode and (optionally) function.
 */
struct InstructionMetadata {

    /** The instruction handler. */
    std::unique_ptr<InstructionHandler> ptrHandler;

    /** The instruction parser. */
    std::unique_ptr<InstructionParser> ptrParser;

    /** The instruction name. */
    std::string strName;

    /** The instruction type. */
    InstructionType type;

    /** The function (defaults to 0). */
    word_t wFunct;

    /** The opcode. */
    word_t wOpcode;
};