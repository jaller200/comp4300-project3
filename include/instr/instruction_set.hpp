#pragma once

#include "instr/instruction_metadata.hpp"
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

    // MARK: -- Public Types

    /** Instruction Opcode/Funct Keys (lower 8 bits = opcode, upper 8 bits = funct) */
    using instr_id_t = hword_t;



    // MARK: -- Construction
    InstructionSet();
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


    // MARK: -- Getter Methods

    /**
     * Returns the instruction type for an opcode
     * @param opcode The opcode
     * @return The instruction type, or UNKNOWN
     */
    InstructionType getType(word_t opcode) const;

    /**
     * Returns the instruction type for an instruction name. Converts the
     * name to lower case first.
     * @param name The name
     * @return The instruction type, or UNKNOWN
     */
    InstructionType getType(const std::string& name) const;

private:

    // MARK: -- Private Variables;

    /** An array marking the registered type of the opcode. */
    std::array<InstructionType, Instruction::LIMIT_OPCODE+1> m_arrOpcodeTypes;

    /** A map of instruction names to instruction metadata. */
    std::unordered_map<std::string, std::shared_ptr<InstructionMetadata>> m_mapNameToMetadata;

    /** A map of instruction IDs (opcode/funct) to instruction metadata. */
    std::unordered_map<instr_id_t, std::shared_ptr<InstructionMetadata>> m_mapIDToMetadata;


    // MARK: -- Private Methods

    /**
     * A private method to handle instruction registration.
     * @param name The name to register with
     * @param opcode The opcode to register with
     * @param funct The funct to register with
     * @param type The type to register with
     * @param parser The parser to register with
     * @return True if successfully registered, false if the name, opcode, funct, or metadata are invalid or null
     */
    bool registerInstruction(const std::string& name, word_t opcode, word_t funct, InstructionType type, std::unique_ptr<InstructionParser> parser);
};