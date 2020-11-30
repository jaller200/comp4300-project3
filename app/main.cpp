#include <chrono>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <vector>

#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"

#include "instr/functions.hpp"
#include "instr/instruction_encoder.hpp"
#include "instr/instruction_set.hpp"
#include "instr/opcodes.hpp"
#include "memory/memory.hpp"
#include "reader/file_reader.hpp"
#include "registers/register_bank.hpp"

#include "simulator.hpp"
#include "types.hpp"

#include "instr/handlers/add_handler.hpp"
#include "instr/handlers/addi_handler.hpp"
#include "instr/handlers/beq_handler.hpp"
#include "instr/handlers/bne_handler.hpp"
#include "instr/handlers/lb_handler.hpp"
#include "instr/handlers/lui_handler.hpp"
#include "instr/handlers/ori_handler.hpp"
#include "instr/handlers/sll_handler.hpp"
#include "instr/handlers/slt_handler.hpp"
#include "instr/handlers/syscall_handler.hpp"

#include "instr/parsers/add_parser.hpp"
#include "instr/parsers/addi_parser.hpp"
#include "instr/parsers/b_parser.hpp"
#include "instr/parsers/beq_parser.hpp"
#include "instr/parsers/beqz_parser.hpp"
#include "instr/parsers/bge_parser.hpp"
#include "instr/parsers/bne_parser.hpp"
#include "instr/parsers/la_parser.hpp"
#include "instr/parsers/lb_parser.hpp"
#include "instr/parsers/li_parser.hpp"
#include "instr/parsers/lui_parser.hpp"
#include "instr/parsers/nop_parser.hpp"
#include "instr/parsers/ori_parser.hpp"
#include "instr/parsers/sll_parser.hpp"
#include "instr/parsers/slt_parser.hpp"
#include "instr/parsers/subi_parser.hpp"
#include "instr/parsers/syscall_parser.hpp"


// MARK: -- Setup Methods

/**
 * Sets up the instruction set.
 * @return The instruction set
 */
std::unique_ptr<InstructionSet> setupInstructions() {

    // Create our instruction set
    std::unique_ptr<InstructionSet> instrSet(new InstructionSet());

    // R-Type
    instrSet->registerRType("add", static_cast<word_t>(Opcodes::OPCODE_R_TYPE), static_cast<word_t>(Functions::FUNCT_ADD), std::unique_ptr<AddParser>(new AddParser()), std::unique_ptr<AddHandler>(new AddHandler()));
    instrSet->registerRType("sll", static_cast<word_t>(Opcodes::OPCODE_R_TYPE), static_cast<word_t>(Functions::FUNCT_SLL), std::unique_ptr<SllParser>(new SllParser()), std::unique_ptr<SllHandler>(new SllHandler()));
    instrSet->registerRType("slt", static_cast<word_t>(Opcodes::OPCODE_R_TYPE), static_cast<word_t>(Functions::FUNCT_SLT), std::unique_ptr<SltParser>(new SltParser()), std::unique_ptr<SltHandler>(new SltHandler()));
    instrSet->registerRType("syscall", static_cast<word_t>(Opcodes::OPCODE_R_TYPE), static_cast<word_t>(Functions::FUNCT_SYSCALL), std::unique_ptr<SyscallParser>(new SyscallParser()), std::unique_ptr<SyscallHandler>(new SyscallHandler()));

    // I-Type
    instrSet->registerIType("addi", static_cast<word_t>(Opcodes::OPCODE_ADDI), std::unique_ptr<AddiParser>(new AddiParser()), std::unique_ptr<AddiHandler>(new AddiHandler()));
    instrSet->registerIType("beq", static_cast<word_t>(Opcodes::OPCODE_BEQ), std::unique_ptr<BeqParser>(new BeqParser()), std::unique_ptr<BeqHandler>(new BeqHandler()));
    instrSet->registerIType("bne", static_cast<word_t>(Opcodes::OPCODE_BNE), std::unique_ptr<BneParser>(new BneParser()), std::unique_ptr<BneHandler>(new BneHandler()));
    instrSet->registerIType("lb", static_cast<word_t>(Opcodes::OPCODE_LB), std::unique_ptr<LbParser>(new LbParser()), std::unique_ptr<LbHandler>(new LbHandler()));
    instrSet->registerIType("lui", static_cast<word_t>(Opcodes::OPCODE_LUI), std::unique_ptr<LuiParser>(new LuiParser()), std::unique_ptr<LuiHandler>(new LuiHandler()));
    instrSet->registerIType("ori", static_cast<word_t>(Opcodes::OPCODE_ORI), std::unique_ptr<OriParser>(new OriParser()), std::unique_ptr<OriHandler>(new OriHandler()));

    // Psuedo-Type
    instrSet->registerPsuedoType("b", std::unique_ptr<BParser>(new BParser()));
    instrSet->registerPsuedoType("beqz", std::unique_ptr<BeqzParser>(new BeqzParser()));
    instrSet->registerPsuedoType("bge", std::unique_ptr<BgeParser>(new BgeParser()));
    instrSet->registerPsuedoType("la", std::unique_ptr<LaParser>(new LaParser()));
    instrSet->registerPsuedoType("li", std::unique_ptr<LiParser>(new LiParser()));
    instrSet->registerPsuedoType("nop", std::unique_ptr<NopParser>(new NopParser()));
    instrSet->registerPsuedoType("subi", std::unique_ptr<SubiParser>(new SubiParser()));

    return std::move(instrSet);
}

/**
 * Sets up things such as the logger.
 */
void setupLogger() {

    // Create our console link
    auto consoleSink = std::shared_ptr<spdlog::sinks::stdout_color_sink_mt>(new spdlog::sinks::stdout_color_sink_mt());
    
    // Get the current time
    std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch()
    );

    std::string file = "logs/log-" + std::to_string(ms.count()) + ".log";
    std::shared_ptr<spdlog::sinks::basic_file_sink_mt> fileSink = nullptr;
    try {
        fileSink = std::shared_ptr<spdlog::sinks::basic_file_sink_mt>(new spdlog::sinks::basic_file_sink_mt(file));
    }
    catch (spdlog::spdlog_ex& e) {
        std::cerr << "error: unable to open log file " << file << " for logging" << std::endl;
    }

    if (fileSink != nullptr) {    
        spdlog::set_default_logger(std::shared_ptr<spdlog::logger>(new spdlog::logger("multi_sink", spdlog::sinks_init_list({ consoleSink, fileSink }))));
    }
    else {
        spdlog::set_default_logger(std::shared_ptr<spdlog::logger>(new spdlog::logger("multi_sink", spdlog::sinks_init_list({ consoleSink }))));
    }
}


// MARK: -- Entry Methods

/**
 * The entry point to the program.
 * @param argc The arguments count
 * @param argv The arguments list
 */
int main(int argc, char ** argv) {

    //
    // Usage: ./pipeSim <filename> [--debug]
    //
    if (argc < 2) {
        std::cerr << "usage: ./pipeSim <filename> [--debug]" << std::endl;
        exit(1);
    }

    // Get the filename
    std::string filename = argv[1];
    bool debug = false;

    // Check the debug flag if we have it
    if (argc >= 3) {
        std::string debugFlag = argv[2];
        debug = (debugFlag == "--debug" || debugFlag == "-d");
    }

    // Set up our logging - for some reason this works some of the time, and not other times
    // note exactly sure why
    setupLogger();
    if (debug)
        spdlog::set_level(spdlog::level::trace);

    // Get our instruction set
    std::unique_ptr<InstructionSet> instrSet = setupInstructions();

    // Create our memory
    std::unique_ptr<Memory> memory(new Memory(0x1000, 0x1000));
    
    // Create our register bank
    std::unique_ptr<RegisterBank> registerBank(new RegisterBank());

    // Read our file
    FileReader reader;
    if (!reader.readFile(filename, *instrSet.get(), *memory.get())) {
        spdlog::critical("Unable to open file {}", filename);
        exit(1);
    }

    // Now create our simulator
    Simulator simulator(std::move(instrSet), std::move(memory), std::move(registerBank));
    simulator.run();

    return 0;
}