#pragma once

#include "instr/instruction_parser.hpp"
#include "instr/instruction_type.hpp"
#include "types.hpp"

#include <array>
#include <memory>
#include <string>
#include <unordered_map>

/**
 * A basic class that holds an instruction set.
 * 
 * Instructions will be registered by Opcode & Function (if defined) as a key:
 * 
 *      Opcode      : 6 bits
 *      Function    : 6 bits
 * 
 * Registration will be done with 16 bits, where the first 6 bits are the opcode
 * and the second 6 bits are the function (if necessary). This way I-Type (opcode 0)
 * instructions can be stored just as easily as R-Type and branch.
 */
class InstructionSet {
public:

    // MARK: -- Construction
    InstructionSet() = default;
    ~InstructionSet() = default;


    // MARK: -- Registration Methods

    /**
     * Registers an R-Type instruction with the instruction set. 
     * 
     * If the opcode is registered as R-type, and there is a duplicate funct,
     * or if the opcode is registered as another type, this returns false.
     * 
     * In addition, the name is automatically converted to lower case. If there
     * is a duplicate name found, the function returns false.
     * 
     * @param name The name
     * @param opcode The opcode
     * @param funct The function
     * @param parser The parser for the instruction
     * @return Whether or not the registration succeeded
     */
    bool registerRType(const std::string& name, word_t opcode, word_t funct, std::unique_ptr<InstructionParser> parser);

private:

    // MARK: -- Private Variables;

    /** A map correlating an instruction psuedonym (i.e. "addi") to an opcode/funct pair. */
    std::unordered_map<std::string, hword_t> m_mapInstructions;

    /** A vector matching an instruction opcode only to a types. */
    std::array<InstructionType, Instruction::LIMIT_OPCODE+1> m_vecOpcodeType;

    /** A map correlating an instruction opcode/funct pair to a parser. */
    std::unordered_map<hword_t, std::unique_ptr<InstructionParser>> m_mapParsers;
};