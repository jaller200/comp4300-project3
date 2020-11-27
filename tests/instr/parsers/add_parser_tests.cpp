#include "catch.hpp"

#include <string>
#include <vector>

#include "exception/syntax_error.hpp"
#include "instr/instruction.hpp"
#include "instr/instruction_type.hpp"
#include "instr/parsers/add_parser.hpp"

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
 *      line        -> nominal value (add $1, $2, $3)
 *                     min value (add $1, $0, $0)
 *                     max value (add $31, $31, $31)
 *                     uppercase value (ADD $10, $11, $12)
 *                     non-numerical value (add $v1, $zero, $v0)
 * 
 * Invalid Tests:
 *      opcode missing
 *      one register missing
 *      two registers missing
 *      all registers missing
 *      everything missing (empty line)
 *      only whitespace
 *      invalid registers
 *      zero dest register
 */
TEST_CASE("ADD parser properly parses line") {

    // MARK: -- Valid Tests

    SECTION("Parsing a nominal line returns the proper instruction") {

        std::string input = "add $1, $2, $3";
        AddParser parser;
        
        std::vector<Instruction> instructions;
        REQUIRE_NOTHROW(instructions = parser.parse(input));
        REQUIRE(instructions.size() == 1);
        REQUIRE(instructions[0].getType() == InstructionType::R_FORMAT);
        REQUIRE(instructions[0].getOpcode() == 0);
        REQUIRE(instructions[0].getRd() == 1);
        REQUIRE(instructions[0].getRs() == 2);
        REQUIRE(instructions[0].getRt() == 3);
        REQUIRE(instructions[0].getShamt() == 0);
        REQUIRE(instructions[0].getFunct() == 32);
    }

    SECTION("Parsing a nominal line with whitespace before and after returns the proper instruction") {
        
        std::string input = "   add $1, $2, $3   ";
        AddParser parser;
        
        std::vector<Instruction> instructions;
        REQUIRE_NOTHROW(instructions = parser.parse(input));
        REQUIRE(instructions.size() == 1);
        REQUIRE(instructions[0].getType() == InstructionType::R_FORMAT);
        REQUIRE(instructions[0].getOpcode() == 0);
        REQUIRE(instructions[0].getRd() == 1);
        REQUIRE(instructions[0].getRs() == 2);
        REQUIRE(instructions[0].getRt() == 3);
        REQUIRE(instructions[0].getShamt() == 0);
        REQUIRE(instructions[0].getFunct() == 32);
    }

    SECTION("Parsing a minimum value line returns the proper instruction") {

        std::string input = "add $1, $0, $0";
        AddParser parser;
        
        std::vector<Instruction> instructions;
        REQUIRE_NOTHROW(instructions = parser.parse(input));
        REQUIRE(instructions.size() == 1);
        REQUIRE(instructions[0].getType() == InstructionType::R_FORMAT);
        REQUIRE(instructions[0].getOpcode() == 0);
        REQUIRE(instructions[0].getRd() == 1);
        REQUIRE(instructions[0].getRs() == 0);
        REQUIRE(instructions[0].getRt() == 0);
        REQUIRE(instructions[0].getShamt() == 0);
        REQUIRE(instructions[0].getFunct() == 32);
    }

    SECTION("Parsing a maximum value line returns the proper instruction") {

        std::string input = "add $31, $31, $31";
        AddParser parser;
        
        std::vector<Instruction> instructions;
        REQUIRE_NOTHROW(instructions = parser.parse(input));
        REQUIRE(instructions.size() == 1);
        REQUIRE(instructions[0].getType() == InstructionType::R_FORMAT);
        REQUIRE(instructions[0].getOpcode() == 0);
        REQUIRE(instructions[0].getRd() == 31);
        REQUIRE(instructions[0].getRs() == 31);
        REQUIRE(instructions[0].getRt() == 31);
        REQUIRE(instructions[0].getShamt() == 0);
        REQUIRE(instructions[0].getFunct() == 32);
    }

    SECTION("Parsing an uppercase line returns the proper instruction") {

        std::string input = "ADD $1, $2, $3";
        AddParser parser;
        
        std::vector<Instruction> instructions;
        REQUIRE_NOTHROW(instructions = parser.parse(input));
        REQUIRE(instructions.size() == 1);
        REQUIRE(instructions[0].getType() == InstructionType::R_FORMAT);
        REQUIRE(instructions[0].getOpcode() == 0);
        REQUIRE(instructions[0].getRd() == 1);
        REQUIRE(instructions[0].getRs() == 2);
        REQUIRE(instructions[0].getRt() == 3);
        REQUIRE(instructions[0].getShamt() == 0);
        REQUIRE(instructions[0].getFunct() == 32);
    }

    SECTION("Parsing a non-numerical line returns the proper instruction") {

        std::string input = "add $v1, $zero, $v0";
        AddParser parser;
        
        std::vector<Instruction> instructions;
        REQUIRE_NOTHROW(instructions = parser.parse(input));
        REQUIRE(instructions.size() == 1);
        REQUIRE(instructions[0].getType() == InstructionType::R_FORMAT);
        REQUIRE(instructions[0].getOpcode() == 0);
        REQUIRE(instructions[0].getRd() == 3);
        REQUIRE(instructions[0].getRs() == 0);
        REQUIRE(instructions[0].getRt() == 2);
        REQUIRE(instructions[0].getShamt() == 0);
        REQUIRE(instructions[0].getFunct() == 32);
    }


    // MARK: -- Invalid Tests

    SECTION("Parsing a line with an opcode missing throws a syntax error") {

        std::string input = "$v1, $zero, $v0";
        AddParser parser;
        REQUIRE_THROWS_AS(parser.parse(input), SyntaxError);
    }

    SECTION("Parsing a line with one register missing throws a syntax error") {

        std::string input = "add $v1, $v0";
        AddParser parser;
        REQUIRE_THROWS_AS(parser.parse(input), SyntaxError);
    }

    SECTION("Parsing a line with two registers missing throws a syntax error") {

        std::string input = "add $v0";
        AddParser parser;
        REQUIRE_THROWS_AS(parser.parse(input), SyntaxError);
    }

    SECTION("Parsing a line with all registers missing throws a syntax error") {

        std::string input = "add";
        AddParser parser;
        REQUIRE_THROWS_AS(parser.parse(input), SyntaxError);
    }

    SECTION("Parsing a line with everything missing throws a syntax error") {

        std::string input = "";
        AddParser parser;
        REQUIRE_THROWS_AS(parser.parse(input), SyntaxError);
    }

    SECTION("Parsing a line with only whitespace/delimiters throws a syntax error") {
        
        std::string input = " \n  \t";
        AddParser parser;
        REQUIRE_THROWS_AS(parser.parse(input), SyntaxError);
    }

    SECTION("Parsing a line with invalid registers throws a syntax error") {
        
        std::string input = "add $1, $2, $35";
        AddParser parser;
        REQUIRE_THROWS_AS(parser.parse(input), SyntaxError);
    }

    SECTION("Parsing a line with writing to the zero register throws a syntax error") {

        std::string input = "add $0, $1, $2";
        AddParser parser;
        REQUIRE_THROWS_AS(parser.parse(input), SyntaxError);        
    }
}