#include "instr/instruction_set.hpp"

#include "spdlog/spdlog.h"
#include "utils/string_utils.hpp"

// MARK: -- Construction

// Construction
InstructionSet::InstructionSet() {
    this->m_arrOpcodeTypes.fill(InstructionType::UNKNOWN);
}


// MARK: -- Registration Methods

// Registers an I-type instruction
bool InstructionSet::registerIType(const std::string& name, word_t opcode, std::unique_ptr<InstructionParser> parser) {
    return this->registerInstruction(name, opcode, 0, InstructionType::I_FORMAT, std::move(parser));
}

// Registers an R-type instruction.
bool InstructionSet::registerRType(const std::string& name, word_t opcode, word_t funct, std::unique_ptr<InstructionParser> parser) {
    return this->registerInstruction(name, opcode, funct, InstructionType::R_FORMAT, std::move(parser));
}


// MARK: -- Getters

// Returns the type for the opcode
InstructionType InstructionSet::getType(word_t opcode) const {
    
    // Verify that we are within our bounds, and then return
    if (opcode > Instruction::LIMIT_OPCODE) return InstructionType::UNKNOWN;
    return this->m_arrOpcodeTypes[opcode];
}

// Returns the type for the name
InstructionType InstructionSet::getType(const std::string& name) const {

    // Get our name
    std::string instrName = StringUtils::trim(name);
    instrName = StringUtils::toLowerCase(instrName);

    if (instrName == "" || this->m_mapNameToMetadata.find(instrName) == this->m_mapNameToMetadata.end())
        return InstructionType::UNKNOWN;

    return this->m_mapNameToMetadata.at(instrName)->type;
}



// MARK: -- Private Methods

// Registers an instruction. Does not check for type (member functions should do this)
bool InstructionSet::registerInstruction(const std::string& name, word_t opcode, word_t funct, InstructionType type, std::unique_ptr<InstructionParser> parser) {

    // First, verify that we are within our bounds (needed before we check the opcode)
    if (opcode > Instruction::LIMIT_OPCODE || funct > Instruction::LIMIT_FUNCT) {
        spdlog::error("Unable to register instruction with opcode {} and funct {} - out of bounds.", opcode, funct);
        return false;
    }

    // Now that we know we're inside the opcode bounds, check whether we've already assigned this to another type
    if (this->m_arrOpcodeTypes[opcode] != InstructionType::UNKNOWN && this->m_arrOpcodeTypes[opcode] != type) {
        spdlog::error("Unable to register instruction with opcode {} and funct {} - opcode already assigned to another type", opcode, funct);
        return false;
    }

    // Now that we know we have a correct type, opcode, and funct, we can create the key and check
    hword_t key = opcode;
    key = (opcode & ~0xFF00) | ((funct << 8) & 0xFF00);

    // Now check to make sure we haven't already registered this combo
    if (this->m_mapIDToMetadata.find(key) != this->m_mapIDToMetadata.end()) {
        spdlog::error("Unable to register instruction with opcode {} and funct {} - opcode/funct pair already exists", opcode, funct);
        return false;
    }

    // Now, get our name
    std::string instrName = StringUtils::trim(StringUtils::toLowerCase(name));

    // Verify that we actually have a name
    if (instrName == "") {
        spdlog::error("Unable to register instruction with opcode {} and funct {} - no name provided", opcode, funct);
        return false;
    }

    // Also verify that there was no whitespace in the original name
    if (instrName != StringUtils::toLowerCase(name)) {
        spdlog::error("Unable to register instruction with opcode {} and funct {} - name must not contain any whitespace", opcode, funct);
        return false;
    }
    
    // Next verify that we have not registered a duplicate name
    if (this->m_mapNameToMetadata.find(instrName) != this->m_mapNameToMetadata.end()) {
        spdlog::error("Unable to register instruction with opcode {}, funct {}, and name {} - name already exists", opcode, funct, instrName);
        return false;
    }

    // And finally make sure our parser is not null
    if (parser == nullptr) {
        spdlog::error("Unable to register instruction with opcode {}, funct {}, and name {} - cannot register null parser", opcode, funct, instrName);
        return false;
    }

    // Now that we are here, we can register our instruction confidently
    std::shared_ptr<InstructionMetadata> metadata(new InstructionMetadata());
    metadata->ptrParser = std::move(parser);
    metadata->strName = instrName;
    metadata->type = type;
    metadata->wFunct = funct;
    metadata->wOpcode = opcode;

    // Finally, register everything
    this->m_arrOpcodeTypes[opcode] = type;
    this->m_mapIDToMetadata[key] = metadata;
    this->m_mapNameToMetadata[instrName] = metadata;
    return true;
}