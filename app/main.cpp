#include <iostream>
#include <memory>
#include <vector>

#include "spdlog/spdlog.h"

#include "instr/functions.hpp"
#include "instr/instruction_encoder.hpp"
#include "instr/instruction_set.hpp"
#include "instr/opcodes.hpp"
#include "memory/memory.hpp"
#include "reader/file_reader.hpp"
#include "registers/register_bank.hpp"
#include "types.hpp"

#include "instr/handlers/add_handler.hpp"
#include "instr/handlers/addi_handler.hpp"
#include "instr/handlers/beq_handler.hpp"
#include "instr/handlers/bne_handler.hpp"
#include "instr/handlers/slt_handler.hpp"
#include "instr/handlers/syscall_handler.hpp"

#include "instr/parsers/add_parser.hpp"
#include "instr/parsers/addi_parser.hpp"
#include "instr/parsers/b_parser.hpp"
#include "instr/parsers/beq_parser.hpp"
#include "instr/parsers/beqz_parser.hpp"
#include "instr/parsers/bge_parser.hpp"
#include "instr/parsers/bne_parser.hpp"
#include "instr/parsers/nop_parser.hpp"
#include "instr/parsers/slt_parser.hpp"
#include "instr/parsers/subi_parser.hpp"
#include "instr/parsers/syscall_parser.hpp"

/**
 * The entry point to the program.
 * @param argc The arguments count
 * @param argv The arguments list
 */
int main(int argc, char ** argv) {

    // Create our memory
    std::unique_ptr<Memory> memory(new Memory(0x1000, 0x1000));
    
    // Create our register bank
    std::unique_ptr<RegisterBank> registerBank(new RegisterBank());

    // Create our instruction set
    std::unique_ptr<InstructionSet> instrSet(new InstructionSet());

    // R-Type
    instrSet->registerRType("add", static_cast<word_t>(Opcodes::OPCODE_R_TYPE), static_cast<word_t>(Functions::FUNCT_ADD), std::unique_ptr<AddParser>(new AddParser()), std::unique_ptr<AddHandler>(new AddHandler()));
    instrSet->registerRType("slt", static_cast<word_t>(Opcodes::OPCODE_R_TYPE), static_cast<word_t>(Functions::FUNCT_SLT), std::unique_ptr<SltParser>(new SltParser()), std::unique_ptr<SltHandler>(new SltHandler()));
    instrSet->registerRType("syscall", static_cast<word_t>(Opcodes::OPCODE_R_TYPE), static_cast<word_t>(Functions::FUNCT_SYSCALL), std::unique_ptr<SyscallParser>(new SyscallParser()), std::unique_ptr<SyscallHandler>(new SyscallHandler()));

    // I-Type
    instrSet->registerIType("addi", static_cast<word_t>(Opcodes::OPCODE_ADDI), std::unique_ptr<AddiParser>(new AddiParser()), std::unique_ptr<AddiHandler>(new AddiHandler()));
    instrSet->registerIType("beq", static_cast<word_t>(Opcodes::OPCODE_BEQ), std::unique_ptr<BeqParser>(new BeqParser()), std::unique_ptr<BeqHandler>(new BeqHandler()));
    instrSet->registerIType("bne", static_cast<word_t>(Opcodes::OPCODE_BNE), std::unique_ptr<BneParser>(new BneParser()), std::unique_ptr<BneHandler>(new BneHandler()));

    // Psuedo-Type
    instrSet->registerPsuedoType("b", std::unique_ptr<BParser>(new BParser()));
    instrSet->registerPsuedoType("beqz", std::unique_ptr<BeqzParser>(new BeqzParser()));
    instrSet->registerPsuedoType("bge", std::unique_ptr<BgeParser>(new BgeParser()));
    instrSet->registerPsuedoType("nop", std::unique_ptr<NopParser>(new NopParser()));
    instrSet->registerPsuedoType("subi", std::unique_ptr<SubiParser>(new SubiParser()));

    // Read our file
    FileReader reader;
    reader.readFile("./app/test.s", *instrSet.get(), *memory.get());

    return 0;
}