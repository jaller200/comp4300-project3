#include "catch.hpp"

#include <iostream>
#include <exception>
#include <string>
#include <vector>

#include "exception/syntax_error.hpp"
#include "instr/instruction.hpp"
#include "instr/instruction_type.hpp"
#include "instr/parsers/addi_parser.hpp"

/**
 * Method: AddParser::parse(..)
 * Desired Confidence Level: Boundary value analysis
 * 
 * Inputs:
 *      line        -> A valid, non-empty line starting with "add" and containing
 *                      three more register names, mandatory, unvalidated
 * 
 * Outputs:
 *      An array of a single instruction on a success, nothing on failure
 * 
 * Valid Tests:
 *      line        -> nominal value (add $1, $2, 100)
 *                     min value (add $1, $0, 0)
 *                     max value (add $31, $31, 65535)
 *                     uppercase value (ADD $10, $11, 100)
 *                     non-numerical value (add $v1, $zero, 100)
 *                     signed decimal (add $1, $2, -4)
 *                     hexadecimal (add $1, $2, 0x100)
 *                     octal (add $1, $2, 010)
 *                     binary (add $1, $2, 0b10)
 * 
 * Invalid Tests:
 *      opcode missing
 *      one register missing
 *      all registers missing
 *      everything missing (empty line)
 *      only whitespace
 *      invalid registers
 *      out of bounds immediate
 *      zero dest register
 */
TEST_CASE("ADDI parser properly parses line") {

    // MARK: -- Valid Tests

    SECTION("Parsing a nominal line returns the proper instruction") {

        std::string input = "addi $1, $2, 100";
        AddiParser parser;
        
        std::vector<Instruction> instructions;
        REQUIRE_NOTHROW(instructions = parser.parse(input));
        REQUIRE(instructions.size() == 1);
        REQUIRE(instructions[0].getType() == InstructionType::I_FORMAT);
        REQUIRE(instructions[0].getOpcode() == 8);;
        REQUIRE(instructions[0].getRs() == 2);
        REQUIRE(instructions[0].getRt() == 1);
        REQUIRE(static_cast<shword_t>(instructions[0].getImmediate()) == 100);
    }

    SECTION("Parsing a nominal line with whitespace before and after returns the proper instruction") {

        std::string input = "   addi $1, $2, 100    ";
        AddiParser parser;
        
        std::vector<Instruction> instructions;
        REQUIRE_NOTHROW(instructions = parser.parse(input));
        REQUIRE(instructions.size() == 1);
        REQUIRE(instructions[0].getType() == InstructionType::I_FORMAT);
        REQUIRE(instructions[0].getOpcode() == 8);;
        REQUIRE(instructions[0].getRs() == 2);
        REQUIRE(instructions[0].getRt() == 1);
        REQUIRE(static_cast<shword_t>(instructions[0].getImmediate()) == 100);
    }

    SECTION("Parsing a minimal line returns the proper instruction") {

        std::string input = "addi $1, $0, -32768";
        AddiParser parser;
        
        std::vector<Instruction> instructions;
        REQUIRE_NOTHROW(instructions = parser.parse(input));
        REQUIRE(instructions.size() == 1);
        REQUIRE(instructions[0].getType() == InstructionType::I_FORMAT);
        REQUIRE(instructions[0].getOpcode() == 8);;
        REQUIRE(instructions[0].getRs() == 0);
        REQUIRE(instructions[0].getRt() == 1);
        REQUIRE(static_cast<shword_t>(instructions[0].getImmediate()) == -32768);
    }


    SECTION("Parsing a maximal line returns the proper instruction") {

        std::string input = "addi $31, $31, 32767";
        AddiParser parser;
        
        std::vector<Instruction> instructions;
        REQUIRE_NOTHROW(instructions = parser.parse(input));
        REQUIRE(instructions.size() == 1);
        REQUIRE(instructions[0].getType() == InstructionType::I_FORMAT);
        REQUIRE(instructions[0].getOpcode() == 8);;
        REQUIRE(instructions[0].getRs() == 31);
        REQUIRE(instructions[0].getRt() == 31);
        REQUIRE(static_cast<shword_t>(instructions[0].getImmediate()) == 32767);
    }

    SECTION("Parsing an uppercase line returns the proper instruction") {

        std::string input = "ADDI $1, $2, 100";
        AddiParser parser;
        
        std::vector<Instruction> instructions;
        REQUIRE_NOTHROW(instructions = parser.parse(input));
        REQUIRE(instructions.size() == 1);
        REQUIRE(instructions[0].getType() == InstructionType::I_FORMAT);
        REQUIRE(instructions[0].getOpcode() == 8);;
        REQUIRE(instructions[0].getRs() == 2);
        REQUIRE(instructions[0].getRt() == 1);
        REQUIRE(static_cast<shword_t>(instructions[0].getImmediate()) == 100);
    }

    SECTION("Parsing a non numerical line returns the proper instruction") {

        std::string input = "addi $v1, $zero, 100";
        AddiParser parser;
        
        std::vector<Instruction> instructions;
        REQUIRE_NOTHROW(instructions = parser.parse(input));
        REQUIRE(instructions.size() == 1);
        REQUIRE(instructions[0].getType() == InstructionType::I_FORMAT);
        REQUIRE(instructions[0].getOpcode() == 8);;
        REQUIRE(instructions[0].getRs() == 0);
        REQUIRE(instructions[0].getRt() == 3);
        REQUIRE(static_cast<shword_t>(instructions[0].getImmediate()) == 100);
    }

    SECTION("Parsing a signed decimal line returns the proper instruction") {

        std::string input = "addi $1, $2, -4";
        AddiParser parser;
        
        std::vector<Instruction> instructions;
        REQUIRE_NOTHROW(instructions = parser.parse(input));
        REQUIRE(instructions.size() == 1);
        REQUIRE(instructions[0].getType() == InstructionType::I_FORMAT);
        REQUIRE(instructions[0].getOpcode() == 8);;
        REQUIRE(instructions[0].getRs() == 2);
        REQUIRE(instructions[0].getRt() == 1);
        REQUIRE(static_cast<shword_t>(instructions[0].getImmediate()) == -4);
    }

    SECTION("Parsing a hex line returns the proper instruction") {

        std::string input = "addi $1, $2, 0x100";
        AddiParser parser;
        
        std::vector<Instruction> instructions;
        REQUIRE_NOTHROW(instructions = parser.parse(input));
        REQUIRE(instructions.size() == 1);
        REQUIRE(instructions[0].getType() == InstructionType::I_FORMAT);
        REQUIRE(instructions[0].getOpcode() == 8);;
        REQUIRE(instructions[0].getRs() == 2);
        REQUIRE(instructions[0].getRt() == 1);
        REQUIRE(static_cast<shword_t>(instructions[0].getImmediate()) == 256);
    }

    SECTION("Parsing an octal line returns the proper instruction") {

        std::string input = "addi $1, $2, 010";
        AddiParser parser;
        
        std::vector<Instruction> instructions;
        REQUIRE_NOTHROW(instructions = parser.parse(input));
        REQUIRE(instructions.size() == 1);
        REQUIRE(instructions[0].getType() == InstructionType::I_FORMAT);
        REQUIRE(instructions[0].getOpcode() == 8);;
        REQUIRE(instructions[0].getRs() == 2);
        REQUIRE(instructions[0].getRt() == 1);
        REQUIRE(static_cast<shword_t>(instructions[0].getImmediate()) == 8);
    }

    SECTION("Parsing a binary line returns the proper instruction") {

        std::string input = "addi $1, $2, 0b111";
        AddiParser parser;
        
        std::vector<Instruction> instructions;
        REQUIRE_NOTHROW(instructions = parser.parse(input));
        REQUIRE(instructions.size() == 1);
        REQUIRE(instructions[0].getType() == InstructionType::I_FORMAT);
        REQUIRE(instructions[0].getOpcode() == 8);;
        REQUIRE(instructions[0].getRs() == 2);
        REQUIRE(instructions[0].getRt() == 1);
        REQUIRE(static_cast<shword_t>(instructions[0].getImmediate()) == 7);
    }


    // MARK: -- Invalid Tests

    SECTION("Parsing a line with an opcode missing throws a syntax error") {

        std::string input = "$v1, $zero, 100";
        AddiParser parser;
        REQUIRE_THROWS_AS(parser.parse(input), SyntaxError);
    }

    SECTION("Parsing a line with one register missing throws a syntax error") {

        std::string input = "addi $v1, 100";
        AddiParser parser;
        REQUIRE_THROWS_AS(parser.parse(input), SyntaxError);
    }

    SECTION("Parsing a line with both registers missing throws a syntax error") {

        std::string input = "addi 100";
        AddiParser parser;
        REQUIRE_THROWS_AS(parser.parse(input), SyntaxError);
    }

    SECTION("Parsing a line with everything missing throws a syntax error") {

        std::string input = "";
        AddiParser parser;
        REQUIRE_THROWS_AS(parser.parse(input), SyntaxError);
    }

    SECTION("Parsing a line with only whitespace/delimiters throws a syntax error") {
        
        std::string input = " \n  \t";
        AddiParser parser;
        REQUIRE_THROWS_AS(parser.parse(input), SyntaxError);
    }

    SECTION("Parsing a line with invalid registers throws a syntax error") {
        
        std::string input = "addi $1, $35, 100";
        AddiParser parser;
        REQUIRE_THROWS_AS(parser.parse(input), SyntaxError);
    }

    SECTION("Parsing a line with positive out of bounds immediate throws a syntax error") {
        
        std::string input = "addi $1, $2, 32768";
        AddiParser parser;
        REQUIRE_THROWS_AS(parser.parse(input), SyntaxError);
    }

    SECTION("Parsing a line with negative out of bounds immediate throws a syntax error") {
        
        std::string input = "addi $1, $2, -32769";
        AddiParser parser;
        REQUIRE_THROWS_AS(parser.parse(input), SyntaxError);
    }

    SECTION("Parsing a line with writing to the zero register throws a syntax error") {

        std::string input = "addi $0, $1, 100";
        AddiParser parser;
        REQUIRE_THROWS_AS(parser.parse(input), SyntaxError);        
    }
}