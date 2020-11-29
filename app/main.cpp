#include <iostream>
#include <memory>
#include <vector>

#include "spdlog/spdlog.h"

#include "instr/functions.hpp"
#include "instr/instruction_encoder.hpp"
#include "instr/instruction_set.hpp"
#include "instr/handlers/add_handler.hpp"
#include "instr/handlers/addi_handler.hpp"
#include "instr/parsers/add_parser.hpp"
#include "instr/parsers/addi_parser.hpp"
#include "instr/opcodes.hpp"
#include "memory/memory.hpp"
#include "reader/file_reader.hpp"
#include "registers/register_bank.hpp"
#include "types.hpp"

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

    // I-Type
    instrSet->registerIType("addi", static_cast<word_t>(Opcodes::OPCODE_ADDI), std::unique_ptr<AddiParser>(new AddiParser()), std::unique_ptr<AddiHandler>(new AddiHandler()));

    // Read our file
    FileReader reader;
    reader.readFile("./app/test.s", *instrSet.get(), *memory.get());

    return 0;
}