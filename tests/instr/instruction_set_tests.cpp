#include "catch.hpp"

#include <memory>

#include "instr/instruction_set.hpp"
#include "mocks/itype_instruction_parser.hpp"
#include "mocks/jtype_instruction_parser.hpp"
#include "mocks/rtype_instruction_parser.hpp"

/**
 * Method: InstructionSet::registerIType(..)
 * Desired confidence level: Boundary value analysis
 * 
 * Inputs:
 *      name        -> A A string value without whitespace or delimiters, will be converted to lowercase, unvalidated
 *      opcode      -> A 6-bit unsigned integer value (0-63), unvalidated
 *      parser      -> A unique_ptr to a parser for this specific instruction, non-null, unvalidated
 * 
 * Outputs:
 *      The function returns true if the instruction was registered successfully, otherwise it
 *          returns false
 * 
 * Valid Tests:
 *      name        -> nominal value
 *                     some uppercase letters
 *      opcode      -> nominal value (10)
 *                     minimum value (0, edge case)
 *                     maximum value (63, edge case)
 *      parser      -> nominal value
 * 
 * Invalid Tests:
 *      name string is empty
 *      name string with just whitespace
 *      name string with whitespace and ASCII
 *      name string with newline
 *      name string with tab
 *      opcode above max value
 *      parser null
 *      attempting to register another i-type with the same opcode
 *      attempting to register another i-type with the same name
 *      attempting to register an r-type with the same opcode
 */
TEST_CASE("Instruction set is properly able to register I-Type instructions") {

    // MARK: -- Valid Tests

    SECTION("Registering a nominal I-Type instruction works properly") {

        InstructionSet instrSet;
        std::unique_ptr<InstructionParser> parser(new ITypeInstructionParser());
        REQUIRE(instrSet.registerIType("test", 10, std::move(parser)) == true);
        REQUIRE(instrSet.getType(10) == InstructionType::I_FORMAT);
        REQUIRE(instrSet.getType("test") == InstructionType::I_FORMAT);

        SECTION("Registering another I-Type instruction with the same opcode fails") {

            std::unique_ptr<InstructionParser> parser2(new ITypeInstructionParser());
            REQUIRE_FALSE(instrSet.registerIType("test2", 10, std::move(parser2)));
            REQUIRE(instrSet.getType(10) == InstructionType::I_FORMAT);
            REQUIRE(instrSet.getType("test") == InstructionType::I_FORMAT);
        }

        SECTION("Registering another I-Type instruction with the same name fails") {

            std::unique_ptr<InstructionParser> parser2(new ITypeInstructionParser());
            REQUIRE_FALSE(instrSet.registerIType("test", 30, std::move(parser2)));
            REQUIRE(instrSet.getType(30) == InstructionType::UNKNOWN);
            REQUIRE(instrSet.getType("test") == InstructionType::I_FORMAT);
        }

        SECTION("Registering a different format (R-Type) instruction with the same opcode fails") {

            std::unique_ptr<InstructionParser> parser2(new RTypeInstructionParser());
            REQUIRE_FALSE(instrSet.registerRType("test2", 10, 11, std::move(parser2)));
            REQUIRE(instrSet.getType(10) == InstructionType::I_FORMAT);
            REQUIRE(instrSet.getType("test") == InstructionType::I_FORMAT);
        }
    }

    SECTION("Registering an I-Type instruction with a min opcode works properly") {

        InstructionSet instrSet;
        std::unique_ptr<InstructionParser> parser(new ITypeInstructionParser());
        REQUIRE(instrSet.registerIType("test", 0, std::move(parser)) == true);
        REQUIRE(instrSet.getType(0) == InstructionType::I_FORMAT);
        REQUIRE(instrSet.getType("test") == InstructionType::I_FORMAT);
    }

    SECTION("Registering an I-Type instruction with a max opcode works properly") {

        InstructionSet instrSet;
        std::unique_ptr<InstructionParser> parser(new ITypeInstructionParser());
        REQUIRE(instrSet.registerIType("test", 63, std::move(parser)) == true);
        REQUIRE(instrSet.getType(63) == InstructionType::I_FORMAT);
        REQUIRE(instrSet.getType("test") == InstructionType::I_FORMAT);
    }

    SECTION("Registering an I-Type instruction with some uppercase letters in the name works properly") {

        InstructionSet instrSet;
        std::unique_ptr<InstructionParser> parser(new ITypeInstructionParser());
        REQUIRE(instrSet.registerIType("TeSt", 10, std::move(parser)) == true);
        REQUIRE(instrSet.getType(10) == InstructionType::I_FORMAT);
        REQUIRE(instrSet.getType("test") == InstructionType::I_FORMAT);
    }


    // MARK: -- Invalid Tests

    SECTION("Registering an I-Type instruction with a blank name fails") {

        InstructionSet instrSet;
        std::unique_ptr<InstructionParser> parser(new ITypeInstructionParser());
        REQUIRE_FALSE(instrSet.registerIType("", 10, std::move(parser)));
        REQUIRE(instrSet.getType(10) == InstructionType::UNKNOWN);
    }

    SECTION("Registering an I-Type instruction with just whitespace for a name fails") {

        InstructionSet instrSet;
        std::unique_ptr<InstructionParser> parser(new ITypeInstructionParser());
        REQUIRE_FALSE(instrSet.registerIType("     ", 10, std::move(parser)));
        REQUIRE(instrSet.getType(10) == InstructionType::UNKNOWN);
    }

    SECTION("Registering an I-Type instruction with whitespace and ASCII fails") {

        InstructionSet instrSet;
        std::unique_ptr<InstructionParser> parser(new ITypeInstructionParser());
        REQUIRE_FALSE(instrSet.registerIType("   test", 10, std::move(parser)));
        REQUIRE(instrSet.getType(10) == InstructionType::UNKNOWN);
    }

    SECTION("Registering an I-Type instruction with a newline fails") {

        InstructionSet instrSet;
        std::unique_ptr<InstructionParser> parser(new ITypeInstructionParser());
        REQUIRE_FALSE(instrSet.registerIType("\ntest", 10, std::move(parser)));
        REQUIRE(instrSet.getType(10) == InstructionType::UNKNOWN);
    }

    SECTION("Registering an I-Type instruction with a tab fails") {

        InstructionSet instrSet;
        std::unique_ptr<InstructionParser> parser(new ITypeInstructionParser());
        REQUIRE_FALSE(instrSet.registerIType("\ttest", 10, std::move(parser)));
        REQUIRE(instrSet.getType(10) == InstructionType::UNKNOWN);
    }

    SECTION("Registering an I-Type instruction with an opcode above max value fails") {

        InstructionSet instrSet;
        std::unique_ptr<InstructionParser> parser(new ITypeInstructionParser());
        REQUIRE_FALSE(instrSet.registerIType("test", 64, std::move(parser)));
        REQUIRE(instrSet.getType(10) == InstructionType::UNKNOWN);
        REQUIRE(instrSet.getType("test") == InstructionType::UNKNOWN);
    }

    SECTION("Registering an I-Type instruction with a null parser fails") {

        InstructionSet instrSet;
        REQUIRE_FALSE(instrSet.registerIType("test", 10, nullptr));
        REQUIRE(instrSet.getType(10) == InstructionType::UNKNOWN);
        REQUIRE(instrSet.getType("test") == InstructionType::UNKNOWN);
    }
}

/**
 * Method: InstructionSet::registerJType(..)
 * Desired Confidence Level: Boundary value analysis
 * 
 * Inputs:
 *      name        -> A string value without whitespace or delimiters, will be converted to lowercase, unvalidated
 *      opcode      -> A 6-bit unsigned integer value (0-63), unvalidated
 *      parser      -> A unique_ptr to a parser for this specific instruction, non-null, unvalidated
 * 
 * Outputs:
 *      The function returns true if the instruction was registered successfully, otherwise it
 *          returns false
 * 
 * Valid Tests:
 *      name        -> nominal value
 *                     some uppercase letters
 *      opcode      -> nominal value (10)
 *                     minimum value (0, edge case)
 *                     maximum value (63, edge case)
 *      parser      -> nominal value
 * 
 * Invalid Tests:
 *      name string is empty
 *      name string is just whitespace
 *      name string with whitespace and ASCII
 *      name string with newline
 *      name string with tab
 *      opcode above max value
 *      parser null
 *      attempting to register another j-type with the same opcode
 *      attempting to register anotiher j-type with the same name
 *      attempting to register a different format with the same opcode
 */
TEST_CASE("Instruction set is properly able to register J-Type instructions") {

    // MARK: -- Valid Tests

    SECTION("Registering a nominal J-Type instruction works properly") {

        InstructionSet instrSet;
        std::unique_ptr<InstructionParser> parser(new JTypeInstructionParser());
        REQUIRE(instrSet.registerJType("test", 10, std::move(parser)) == true);
        REQUIRE(instrSet.getType(10) == InstructionType::J_FORMAT);
        REQUIRE(instrSet.getType("test") == InstructionType::J_FORMAT);

        SECTION("Registering another J-Type instruction with the same opcode fails") {

            std::unique_ptr<InstructionParser> parser2(new JTypeInstructionParser());
            REQUIRE_FALSE(instrSet.registerJType("test2", 10, std::move(parser2)));
            REQUIRE(instrSet.getType(10) == InstructionType::J_FORMAT);
            REQUIRE(instrSet.getType("test") == InstructionType::J_FORMAT);
        }

        SECTION("Registering another J-Type instruction with the same name fails") {

            std::unique_ptr<InstructionParser> parser2(new JTypeInstructionParser());
            REQUIRE_FALSE(instrSet.registerJType("test", 30, std::move(parser2)));
            REQUIRE(instrSet.getType(30) == InstructionType::UNKNOWN);
            REQUIRE(instrSet.getType("test") == InstructionType::J_FORMAT);
        }

        SECTION("Registering a different format (R-Type) instruction with the same opcode fails") {

            std::unique_ptr<InstructionParser> parser2(new RTypeInstructionParser());
            REQUIRE_FALSE(instrSet.registerRType("test2", 10, 11, std::move(parser2)));
            REQUIRE(instrSet.getType(10) == InstructionType::J_FORMAT);
            REQUIRE(instrSet.getType("test") == InstructionType::J_FORMAT);
        }
    }

    SECTION("Registering an J-Type instruction with a min opcode works properly") {

        InstructionSet instrSet;
        std::unique_ptr<InstructionParser> parser(new JTypeInstructionParser());
        REQUIRE(instrSet.registerJType("test", 0, std::move(parser)) == true);
        REQUIRE(instrSet.getType(0) == InstructionType::J_FORMAT);
        REQUIRE(instrSet.getType("test") == InstructionType::J_FORMAT);
    }

    SECTION("Registering an J-Type instruction with a max opcode works properly") {

        InstructionSet instrSet;
        std::unique_ptr<InstructionParser> parser(new JTypeInstructionParser());
        REQUIRE(instrSet.registerJType("test", 63, std::move(parser)) == true);
        REQUIRE(instrSet.getType(63) == InstructionType::J_FORMAT);
        REQUIRE(instrSet.getType("test") == InstructionType::J_FORMAT);
    }

    SECTION("Registering an J-Type instruction with some uppercase letters in the name works properly") {

        InstructionSet instrSet;
        std::unique_ptr<InstructionParser> parser(new JTypeInstructionParser());
        REQUIRE(instrSet.registerJType("TeSt", 10, std::move(parser)) == true);
        REQUIRE(instrSet.getType(10) == InstructionType::J_FORMAT);
        REQUIRE(instrSet.getType("test") == InstructionType::J_FORMAT);
    }


    // MARK: -- Invalid Tests

    SECTION("Registering an J-Type instruction with a blank name fails") {

        InstructionSet instrSet;
        std::unique_ptr<InstructionParser> parser(new JTypeInstructionParser());
        REQUIRE_FALSE(instrSet.registerJType("", 10, std::move(parser)));
        REQUIRE(instrSet.getType(10) == InstructionType::UNKNOWN);
    }

    SECTION("Registering an J-Type instruction with just whitespace for a name fails") {

        InstructionSet instrSet;
        std::unique_ptr<InstructionParser> parser(new JTypeInstructionParser());
        REQUIRE_FALSE(instrSet.registerJType("     ", 10, std::move(parser)));
        REQUIRE(instrSet.getType(10) == InstructionType::UNKNOWN);
    }

    SECTION("Registering an J-Type instruction with whitespace and ASCII fails") {

        InstructionSet instrSet;
        std::unique_ptr<InstructionParser> parser(new JTypeInstructionParser());
        REQUIRE_FALSE(instrSet.registerJType("   test", 10, std::move(parser)));
        REQUIRE(instrSet.getType(10) == InstructionType::UNKNOWN);
    }

    SECTION("Registering an J-Type instruction with a newline fails") {

        InstructionSet instrSet;
        std::unique_ptr<InstructionParser> parser(new JTypeInstructionParser());
        REQUIRE_FALSE(instrSet.registerJType("\ntest", 10, std::move(parser)));
        REQUIRE(instrSet.getType(10) == InstructionType::UNKNOWN);
    }

    SECTION("Registering an J-Type instruction with a tab fails") {

        InstructionSet instrSet;
        std::unique_ptr<InstructionParser> parser(new JTypeInstructionParser());
        REQUIRE_FALSE(instrSet.registerJType("\ttest", 10, std::move(parser)));
        REQUIRE(instrSet.getType(10) == InstructionType::UNKNOWN);
    }

    SECTION("Registering an J-Type instruction with an opcode above max value fails") {

        InstructionSet instrSet;
        std::unique_ptr<InstructionParser> parser(new JTypeInstructionParser());
        REQUIRE_FALSE(instrSet.registerJType("test", 64, std::move(parser)));
        REQUIRE(instrSet.getType(10) == InstructionType::UNKNOWN);
        REQUIRE(instrSet.getType("test") == InstructionType::UNKNOWN);
    }

    SECTION("Registering a J-Type instruction with a null parser fails") {

        InstructionSet instrSet;
        REQUIRE_FALSE(instrSet.registerJType("test", 10, nullptr));
        REQUIRE(instrSet.getType(10) == InstructionType::UNKNOWN);
        REQUIRE(instrSet.getType("test") == InstructionType::UNKNOWN);
    }
}

/**
 * Method: InstructionSet::registerRType(..)
 * Desired Confidence Level: Boundary value analysis
 * 
 * Inputs:
 *      name        -> A string value without whitespace or delimiters, will be converted to lowercase, unvalidated
 *      opcode      -> A 6-bit unsigned integer value (0-63), unvalidated
 *      funct       -> A 6-bit unsigned integer value (0-63), unvalidated
 *      parser      -> A unique_ptr to a parser for this specific instruction, non-null, unvalidated
 * 
 * Outputs:
 *      The function returns true if the instruction was registered successfully, otherwise it
 *          returns false.
 * 
 * Valid Tests:
 *      name        -> nominal value
 *                     some uppercase letters
 *      opcode      -> nominal value (10)
 *                     minimum value (0, edge case)
 *                     maximum value (63, edge case)
 *      funct       -> nominal value (11)
 *                     nominal value #2 (same opcode, different funct)
 *                     minimum value (0, edge case)
 *                     maximum value (63, edge case)
 *      parser      -> nominal value
 * 
 * Invalid Tests:
 *      name string is empty
 *      name string with just whitespace
 *      name string with whitespace and ASCII
 *      name string with newline
 *      name string with tab
 *      opcode above max value
 *      funct above max value
 *      parser null
 *      attempting to register another r-type with the same opcode & funct
 *      attempting to register another r-type with the same name
 */
TEST_CASE("Instruction set is properly able to register R-Type instructions") {

    // MARK: -- Valid Tests

    SECTION("Registering a nominal R-Type instruction works properly") {

        InstructionSet instrSet;
        std::unique_ptr<InstructionParser> parser(new RTypeInstructionParser());
        REQUIRE(instrSet.registerRType("test", 10, 11, std::move(parser)) == true);
        REQUIRE(instrSet.getType(10) == InstructionType::R_FORMAT);
        REQUIRE(instrSet.getType("test") == InstructionType::R_FORMAT);

        SECTION("Registering another R-Type instruction with the same opcode but different funct works properly") {

            std::unique_ptr<InstructionParser> parser2(new RTypeInstructionParser());
            REQUIRE(instrSet.registerRType("test2", 10, 12, std::move(parser2)) == true);
            REQUIRE(instrSet.getType(10) == InstructionType::R_FORMAT);
            REQUIRE(instrSet.getType("test") == InstructionType::R_FORMAT);
        }

        SECTION("Registering another R-Type instruction with the same opcode and type fails") {

            std::unique_ptr<InstructionParser> parser2(new RTypeInstructionParser());
            REQUIRE_FALSE(instrSet.registerRType("test2", 10, 11, std::move(parser2)));
            REQUIRE(instrSet.getType(10) == InstructionType::R_FORMAT);
            REQUIRE(instrSet.getType("test2") == InstructionType::UNKNOWN);
        }

        SECTION("Registering another R-Type instruction with the same name fails") {
            
            std::unique_ptr<InstructionParser> parser2(new RTypeInstructionParser());
            REQUIRE_FALSE(instrSet.registerRType("test", 12, 13, std::move(parser2)));
            REQUIRE(instrSet.getType(12) == InstructionType::UNKNOWN);
            REQUIRE(instrSet.getType("test") == InstructionType::R_FORMAT);
        }
    }

    SECTION("Registering an R-Type instruction with a min opcode works properly") {

        InstructionSet instrSet;
        std::unique_ptr<InstructionParser> parser(new RTypeInstructionParser());
        REQUIRE(instrSet.registerRType("test", 0, 11, std::move(parser)) == true);
        REQUIRE(instrSet.getType(0) == InstructionType::R_FORMAT);
        REQUIRE(instrSet.getType("test") == InstructionType::R_FORMAT);
    }

    SECTION("Registering an R-Type instruction with a max opcode works properly") {

        InstructionSet instrSet;
        std::unique_ptr<InstructionParser> parser(new RTypeInstructionParser());
        REQUIRE(instrSet.registerRType("test", 63, 11, std::move(parser)) == true);
        REQUIRE(instrSet.getType(63) == InstructionType::R_FORMAT);
        REQUIRE(instrSet.getType("test") == InstructionType::R_FORMAT);
    }

    SECTION("Registering an R-Type instruction with a min funct works properly") {

        InstructionSet instrSet;
        std::unique_ptr<InstructionParser> parser(new RTypeInstructionParser());
        REQUIRE(instrSet.registerRType("test", 10, 0, std::move(parser)) == true);
        REQUIRE(instrSet.getType(10) == InstructionType::R_FORMAT);
        REQUIRE(instrSet.getType("test") == InstructionType::R_FORMAT);
    }

    SECTION("Registering an R-Type instruction with a max funct works properly") {
        
        InstructionSet instrSet;
        std::unique_ptr<InstructionParser> parser(new RTypeInstructionParser());
        REQUIRE(instrSet.registerRType("test", 10, 63, std::move(parser)) == true);
        REQUIRE(instrSet.getType(10) == InstructionType::R_FORMAT);
        REQUIRE(instrSet.getType("test") == InstructionType::R_FORMAT);
    }

    SECTION("Registering an R-Type instruction with some uppercase letters in the name works properly") {

        InstructionSet instrSet;
        std::unique_ptr<InstructionParser> parser(new RTypeInstructionParser());
        REQUIRE(instrSet.registerRType("TeSt", 10, 63, std::move(parser)) == true);
        REQUIRE(instrSet.getType(10) == InstructionType::R_FORMAT);
        REQUIRE(instrSet.getType("test") == InstructionType::R_FORMAT);
    }


    // MARK: -- Invalid Tests

    SECTION("Registering an R-Type instruction with a blank name fails") {

        InstructionSet instrSet;
        std::unique_ptr<InstructionParser> parser(new RTypeInstructionParser());
        REQUIRE_FALSE(instrSet.registerRType("", 10, 11, std::move(parser)));
        REQUIRE(instrSet.getType(10) == InstructionType::UNKNOWN);
    }

    SECTION("Registering an R-Type instruction with just whitespace for a name fails") {

        InstructionSet instrSet;
        std::unique_ptr<InstructionParser> parser(new RTypeInstructionParser());
        REQUIRE_FALSE(instrSet.registerRType("     ", 10, 11, std::move(parser)));
        REQUIRE(instrSet.getType(10) == InstructionType::UNKNOWN);
    }

    SECTION("Registering an R-Type instruction with whitespace and ASCII fails") {

        InstructionSet instrSet;
        std::unique_ptr<InstructionParser> parser(new RTypeInstructionParser());
        REQUIRE_FALSE(instrSet.registerRType("   test", 10, 11, std::move(parser)));
        REQUIRE(instrSet.getType(10) == InstructionType::UNKNOWN);
    }

    SECTION("Registering an R-Type instruction with a newline fails") {

        InstructionSet instrSet;
        std::unique_ptr<InstructionParser> parser(new RTypeInstructionParser());
        REQUIRE_FALSE(instrSet.registerRType("\ntest", 10, 11, std::move(parser)));
        REQUIRE(instrSet.getType(10) == InstructionType::UNKNOWN);
    }

    SECTION("Registering an R-Type instruction with a tab fails") {

        InstructionSet instrSet;
        std::unique_ptr<InstructionParser> parser(new RTypeInstructionParser());
        REQUIRE_FALSE(instrSet.registerRType("\ttest", 10, 11, std::move(parser)));
        REQUIRE(instrSet.getType(10) == InstructionType::UNKNOWN);
    }

    SECTION("Registering an R-Type instruction with an opcode above max value fails") {

        InstructionSet instrSet;
        std::unique_ptr<InstructionParser> parser(new RTypeInstructionParser());
        REQUIRE_FALSE(instrSet.registerRType("test", 64, 11, std::move(parser)));
        REQUIRE(instrSet.getType(10) == InstructionType::UNKNOWN);
        REQUIRE(instrSet.getType("test") == InstructionType::UNKNOWN);
    }

    SECTION("Registering an R-Type instruction with a funct above max value fails") {

        InstructionSet instrSet;
        std::unique_ptr<InstructionParser> parser(new RTypeInstructionParser());
        REQUIRE_FALSE(instrSet.registerRType("test", 10, 64, std::move(parser)));
        REQUIRE(instrSet.getType(10) == InstructionType::UNKNOWN);
        REQUIRE(instrSet.getType("test") == InstructionType::UNKNOWN);
    }

    SECTION("Registering an R-Type instruction with a null parser fails") {

        InstructionSet instrSet;
        REQUIRE_FALSE(instrSet.registerRType("test", 10, 11, nullptr));
        REQUIRE(instrSet.getType(10) == InstructionType::UNKNOWN);
        REQUIRE(instrSet.getType("test") == InstructionType::UNKNOWN);
    }
}