#include "reader/file_reader.hpp"

#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>

#include "spdlog/spdlog.h"

#include "instr/instruction.hpp"
#include "instr/instruction_encoder.hpp"
#include "instr/instruction_parser.hpp"
#include "instr/instruction_set.hpp"
#include "instr/opcodes.hpp"
#include "memory/memory.hpp"
#include "utils/string_utils.hpp"

#include "types.hpp"

// MARK: -- Reader Methods

// Read a file into memory
bool FileReader::readFile(const std::string& filename, const InstructionSet& instrSet, Memory& memory) const {

    // First, try to open our files
    std::ifstream fileStream;
    fileStream.open(filename, std::ios_base::in);
    if (!fileStream.is_open()) {
        spdlog::error("Unable to open input file '{}' - make sure the file exists and is readable.", filename);
        return false;
    }

    // Now, create a map of our symbols
    std::unordered_map<std::string, Memory::addr_t> symbols;

    // Also, create a map of our instructions
    std::vector<Instruction> instructions;

    // Start at the beginning of the file
    fileStream.clear();
    fileStream.seekg(0);

    // Get our current section
    std::string section = "none";

    // Set our current addresses
    Memory::addr_t currText = Memory::MEM_USER_START;
    Memory::addr_t currData = Memory::MEM_USER_START + memory.getTextSize();

    // Now parse each line
    std::string line;
    while (std::getline(fileStream, line)) {
        
        // Trim our line
        line = StringUtils::toLowerCase(StringUtils::trim(line));
        if (line.length() == 0) continue;

        // First, ignore all comments
        if (line.at(0) == '#') continue;

        // Get the first word of the line
        std::string first = line.substr(0, line.find_first_of(" \t"));

        // See if we're in a new section
        if (first == ".text") {
            section = "text"; 
            continue;
        }
        else if (first == ".data") {
            section = "data"; 
            continue;
        }

        // If we're here, and we're not in a section, this means we have code that is
        // neither a comment, a blank line, or in a section
        if (section == "none") continue;

        // Now check if we have a label
        if (first.back() == ':') {

            // We have a label — get the current address
            std::string name = first.substr(0, first.length()-1);
            Memory::addr_t addr = (section == "text") ? currText : currData;

            // Make sure this is not a duplicate symbol
            if (symbols.find(name) != symbols.end()) {
                spdlog::critical("Attempting to register a duplicate symbol '{}'", name);
                return false;
            }

            symbols[name] = addr;
            if (section == "text") continue;
        }

        // Now that we are here, handle things a bit differently
        if (section == "text") {

            // "first" holds our name
            InstructionParser * parser = instrSet.getInstructionParser(first);
            if (parser == nullptr) {
                spdlog::critical("Unable to get a parser for instruction name '{}'", first);
                return false;
            }

            // Parse the instruction
            std::vector<Instruction> instrs = parser->parse(line);
            instructions.insert(instructions.end(), instrs.begin(), instrs.end());

            // Add 4*size to the curr text
            currText += 4 * instrs.size();
        }
        else if (section == "data") {

            // Get the data type
            std::string second = StringUtils::trim(line.substr(first.length()));
            std::string type = second.substr(0, line.find_first_of(" \t")+1);

            // All types are built-in — they can't be defined by the user.
            if (type == ".ascii") {

                // Read the ASCII lines
                std::string str = StringUtils::trim(second.substr(type.length()));
                if (str.front() != '"' || str.find_first_of('"', 1) == std::string::npos) {
                    spdlog::critical("Unable to parse ASCII string. Missing quotes.");
                    return false;
                }

                // Now get the string and write it to memory
                str = str.substr(1, str.length()-2);
                memory.writeString(currData, str);
                
                // Update with the length of the string + 1 for the null terminator
                currData += str.length() + 1;
            }
            else if (type == ".byte") {

                // Get the byte
                try {
                    std::string str = StringUtils::trim(second.substr(type.length()));
                    str = str.substr(0, line.find_first_of(" \t")+1);

                    // Convert to the number
                    word_t num = StringUtils::toNumber(str);
                    if (num > 255) {
                        spdlog::critical("Byte is too large (over 255)");
                        return false;
                    }

                    // Otherwise, write the byte
                    memory.writeByte(currData, static_cast<byte_t>(num));
                    currData += 1;
                }
                catch (std::exception& e) {
                    spdlog::critical("Unable to convert byte data to number.");
                    return false;
                }
            }
            else if (type == ".space") {

                // Get the byte
                try {
                    std::string str = StringUtils::trim(second.substr(type.length()));
                    str = str.substr(0, line.find_first_of(" \t")+1);

                    // Convert to the number
                    word_t num = StringUtils::toNumber(str);

                    // Otherwise, write the bytes
                    for (int i = 0; i < num; ++i) {
                        memory.writeByte(currData, 0);
                        currData += 1;
                    }
                }
                catch (std::exception& e) {
                    spdlog::critical("Unable to convert space data to number.");
                    return false;
                }
            }
            else if (type == ".word") {

                // Get the byte
                try {
                    std::string str = StringUtils::trim(second.substr(type.length()));
                    str = str.substr(0, line.find_first_of(" \t")+1);

                    // Convert to the number
                    word_t num = StringUtils::toNumber(str);

                    // Otherwise, write the word
                    memory.writeWord(currData, num);
                    currData += 4;
                }
                catch (std::exception& e) {
                    spdlog::critical("Unable to convert word data to number.");
                    return false;
                }
            }
            else {
                spdlog::critical("Unable to parse unknown data type {}", type);
                return false;
            }
        }
    }

    // Once we are here, we can write to memory
    currText = Memory::MEM_USER_START;
    for (Instruction& instr : instructions) {

        // If we have a label set, then we need to get an address
        if (instr.getLabel() != "") {

            // Get the address for the label
            auto search = symbols.find(instr.getLabel());
            if (search == symbols.end()) {
                spdlog::critical("Unable to find address for symbol '{}'", instr.getLabel());
                return false;
            }

            // Handle the address depending on the type
            Memory::addr_t addr = search->second;
            if (instr.getType() == InstructionType::I_FORMAT) {

                if (instr.getOpcode() == static_cast<word_t>(Opcodes::OPCODE_LUI)) {

                    // Get the upper 16-bits
                    word_t val = (addr >> 16);
                    instr.setImmediate(static_cast<hword_t>(val));
                }
                else if (instr.getOpcode() == static_cast<word_t>(Opcodes::OPCODE_ORI)) {

                    // Get the lower 16-bits
                    word_t val = (addr & 0xFFFF);
                    instr.setImmediate(static_cast<hword_t>(val));
                }
                else {

                    // Get the signed difference 
                    shword_t diff = static_cast<shword_t>(addr - (currText + 4));

                    // Set the immediate to this signed difference
                    instr.setImmediate(static_cast<hword_t>(diff));
                }
            }
            else if (instr.getType() == InstructionType::J_FORMAT) {
                // TODO: Handle this
            }
        }

        // Now go ahead and encode our instruction
        Instruction::instr_t encodedInstr = InstructionEncoder::encode(instr);
        
        // And write the data
        memory.writeWord(currText, encodedInstr);
        currText += 4;
    }

    return true;
}