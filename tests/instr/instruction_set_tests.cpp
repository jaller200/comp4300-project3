#include "catch.hpp"

#include <memory>

#include "instr/instruction_set.hpp"
#include "mocks/parsers/itype_instruction_parser.hpp"
#include "mocks/parsers/jtype_instruction_parser.hpp"
#include "mocks/parsers/psuedo_type_instruction_parser.hpp"
#include "mocks/parsers/rtype_instruction_parser.hpp"
#include "mocks/handlers/test_handler.hpp"

// MARK: -- Getter Methods

/**
 * Method: InstructionSet::getInstructionHandler(..)
 * Desired Confidence Level: Boundary value analysis
 * 
 * Inputs:
 *      opcode      -> A 6-bit unsigned integer value (0-63), unvalidated
 *      funct       -> A 6-bit unsigned integer value (0-63), unvalidated
 * 
 * Outputs:
 *      A raw pointer to the parser on success, nullptr otherwise
 * 
 * Valid Tests:
 *      opcode      -> nominal value (10)
 *                     min value (0)
 *                     max value (63)
 *      funct       -> nominal value (10)
 *                     min value (0)
 *                     max value (63)
 * 
 * Valid Outputs
 *      A raw pointer to the parser
 * 
 * Invalid Tests:
 *      opcode one above the max value
 *      opcode far above the max value
 *      funct one above the max value
 *      funct far above the max value
 */
TEST_CASE("Getting an instruction handler returns the proper output") {

    // First, set up our instruction set
    std::unique_ptr<InstructionParser> parser1(new RTypeInstructionParser());
    std::unique_ptr<InstructionParser> parser2(new RTypeInstructionParser());
    std::unique_ptr<InstructionParser> parser3(new RTypeInstructionParser());
    std::unique_ptr<TestHandler> handler1(new TestHandler());
    std::unique_ptr<TestHandler> handler2(new TestHandler());
    std::unique_ptr<TestHandler> handler3(new TestHandler());

    InstructionSet instrSet;
    instrSet.registerRType("test", 10, 10, std::move(parser1), std::move(handler1));
    instrSet.registerRType("test2", 0, 0, std::move(parser2), std::move(handler2));
    instrSet.registerRType("test3", 63, 63, std::move(parser3), std::move(handler3));


    // MARK: -- Valid Tests

    SECTION("Getting a handler for a nominal value returns the handler") {

        InstructionHandler * handler = instrSet.getInstructionHandler(10, 10);
        REQUIRE(handler != nullptr);
        REQUIRE(dynamic_cast<TestHandler*>(handler) != nullptr);
    }

    SECTION("Getting a handler for a minimum value returns the handler") {

        InstructionHandler * handler = instrSet.getInstructionHandler(0, 0);
        REQUIRE(handler != nullptr);
        REQUIRE(dynamic_cast<TestHandler*>(handler) != nullptr);
    }

    SECTION("Getting a handler for a maximum value returns the handler") {

        InstructionHandler * handler = instrSet.getInstructionHandler(63, 63);
        REQUIRE(handler != nullptr);
        REQUIRE(dynamic_cast<TestHandler*>(handler) != nullptr);
    }


    // MARK: -- Invalid Tests

    SECTION("Getting a handler for an opcode one outside of the bounds fails") {

        InstructionHandler * handler = instrSet.getInstructionHandler(64, 10);
        REQUIRE(handler == nullptr);
    }

    SECTION("Getting a handler for an opcode far outside of the bounds fails") {

        InstructionHandler * handler = instrSet.getInstructionHandler(100, 10);
        REQUIRE(handler == nullptr);
    }

    SECTION("Getting a handler for a funct one outside of the bounds fails") {

        InstructionHandler * handler = instrSet.getInstructionHandler(10, 64);
        REQUIRE(handler == nullptr);
    }

    SECTION("Getting a handler for a funct far outside of the bounds fails") {

        InstructionHandler * handler = instrSet.getInstructionHandler(10, 100);
        REQUIRE(handler == nullptr);
    }
}

/**
 * Method: InstructionSet::getInstructionParser(..)
 * Desired Confidence Level: Boundary value analysis
 * 
 * Inputs:
 *      name        -> A string without whitespace or delimiters, will be converted to lowercase, unvalidated
 *  
 * Outputs:
 *      A raw pointer to the parser on success, nullptr otherwise
 * 
 * Valid Tests:
 *      name        -> A nominal string ("test")
 *                     A string with some uppercase ("tEsT")
 * 
 * Valid Outputs:
 *      The parser
 * 
 * Invalid Tests:
 *      name is empty
 *      name contains delimiters
 *      name constains some whitespace and ASCII
 */
TEST_CASE("Getting an instruction parser for a name works properly") {

    // First, set up our instruction set
    std::unique_ptr<InstructionParser> parser1(new RTypeInstructionParser());
    std::unique_ptr<TestHandler> handler1(new TestHandler());

    InstructionSet instrSet;
    instrSet.registerRType("test", 10, 10, std::move(parser1), std::move(handler1));


    // MARK: -- Valid Tests

    SECTION("Getting a parser for a nominal name returns the parser") {

        InstructionParser * parser = instrSet.getInstructionParser("test");
        REQUIRE(parser != nullptr);
        REQUIRE(dynamic_cast<RTypeInstructionParser*>(parser) != nullptr);
    }

    SECTION("Getting a parser for a name with some upper case returns the parser") {

        InstructionParser * parser = instrSet.getInstructionParser("tEsT");
        REQUIRE(parser != nullptr);
        REQUIRE(dynamic_cast<RTypeInstructionParser*>(parser) != nullptr);
    }


    // MARK: -- Invalid Tests

    SECTION("Getting a parser for an empty name fails") {

        InstructionParser * parser = instrSet.getInstructionParser("");
        REQUIRE(parser == nullptr);
    }

    SECTION("Getting a parser for an name with only delimiters fails") {

        InstructionParser * parser = instrSet.getInstructionParser("     \n\t  ");
        REQUIRE(parser == nullptr);
    }

    SECTION("Getting a parser for a name with whitespace and ASCII fails") {

        InstructionParser * parser = instrSet.getInstructionParser("bobs diner");
        REQUIRE(parser == nullptr);
    }
}


// MARK: -- Normal Registration Methods

/**
 * Method: InstructionSet::registerIType(..)
 * Desired Confidence Level: Boundary value analysis
 * 
 * Inputs:
 *      name        -> A A string value without whitespace or delimiters, will be converted to lowercase, unvalidated
 *      opcode      -> A 6-bit unsigned integer value (0-63), unvalidated
 *      parser      -> A unique_ptr to a parser for this specific instruction, non-null, unvalidated
 *      handler     -> A unique_ptr to a handler for this specific instruction, non-null, unvalidated
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
 *      handler     -> nominal value
 * 
 * Invalid Tests:
 *      name string is empty
 *      name string with just whitespace
 *      name string with whitespace and ASCII
 *      name string with newline
 *      name string with tab
 *      opcode above max value
 *      parser null
 *      handler null
 *      attempting to register another i-type with the same opcode
 *      attempting to register another i-type with the same name
 *      attempting to register an r-type with the same opcode
 */
TEST_CASE("Instruction set is properly able to register I-Type instructions") {

    // MARK: -- Valid Tests

    SECTION("Registering a nominal I-Type instruction works properly") {

        InstructionSet instrSet;
        std::unique_ptr<InstructionParser> parser(new ITypeInstructionParser());
        std::unique_ptr<TestHandler> handler(new TestHandler());
        REQUIRE(instrSet.registerIType("test", 10, std::move(parser), std::move(handler)) == true);
        REQUIRE(instrSet.getType(10) == InstructionType::I_FORMAT);
        REQUIRE(instrSet.getType("test") == InstructionType::I_FORMAT);

        SECTION("Registering another I-Type instruction with the same opcode fails") {

            std::unique_ptr<InstructionParser> parser2(new ITypeInstructionParser());
            std::unique_ptr<TestHandler> handler2(new TestHandler());
            REQUIRE_FALSE(instrSet.registerIType("test2", 10, std::move(parser2), std::move(handler2)));
            REQUIRE(instrSet.getType(10) == InstructionType::I_FORMAT);
            REQUIRE(instrSet.getType("test") == InstructionType::I_FORMAT);
        }

        SECTION("Registering another I-Type instruction with the same name fails") {

            std::unique_ptr<InstructionParser> parser2(new ITypeInstructionParser());
            std::unique_ptr<TestHandler> handler2(new TestHandler());
            REQUIRE_FALSE(instrSet.registerIType("test", 30, std::move(parser2), std::move(handler2)));
            REQUIRE(instrSet.getType(30) == InstructionType::UNKNOWN);
            REQUIRE(instrSet.getType("test") == InstructionType::I_FORMAT);
        }

        SECTION("Registering a different format (R-Type) instruction with the same opcode fails") {

            std::unique_ptr<InstructionParser> parser2(new RTypeInstructionParser());
            std::unique_ptr<TestHandler> handler2(new TestHandler());
            REQUIRE_FALSE(instrSet.registerRType("test2", 10, 11, std::move(parser2), std::move(handler2)));
            REQUIRE(instrSet.getType(10) == InstructionType::I_FORMAT);
            REQUIRE(instrSet.getType("test") == InstructionType::I_FORMAT);
        }
    }

    SECTION("Registering an I-Type instruction with a min opcode works properly") {

        InstructionSet instrSet;
        std::unique_ptr<InstructionParser> parser(new ITypeInstructionParser());
        std::unique_ptr<TestHandler> handler(new TestHandler());
        REQUIRE(instrSet.registerIType("test", 0, std::move(parser), std::move(handler)) == true);
        REQUIRE(instrSet.getType(0) == InstructionType::I_FORMAT);
        REQUIRE(instrSet.getType("test") == InstructionType::I_FORMAT);
    }

    SECTION("Registering an I-Type instruction with a max opcode works properly") {

        InstructionSet instrSet;
        std::unique_ptr<InstructionParser> parser(new ITypeInstructionParser());
        std::unique_ptr<TestHandler> handler(new TestHandler());
        REQUIRE(instrSet.registerIType("test", 63, std::move(parser), std::move(handler)) == true);
        REQUIRE(instrSet.getType(63) == InstructionType::I_FORMAT);
        REQUIRE(instrSet.getType("test") == InstructionType::I_FORMAT);
    }

    SECTION("Registering an I-Type instruction with some uppercase letters in the name works properly") {

        InstructionSet instrSet;
        std::unique_ptr<InstructionParser> parser(new ITypeInstructionParser());
        std::unique_ptr<TestHandler> handler(new TestHandler());
        REQUIRE(instrSet.registerIType("TeSt", 10, std::move(parser), std::move(handler)) == true);
        REQUIRE(instrSet.getType(10) == InstructionType::I_FORMAT);
        REQUIRE(instrSet.getType("test") == InstructionType::I_FORMAT);
        REQUIRE(instrSet.getType("TeSt") == InstructionType::I_FORMAT);
    }


    // MARK: -- Invalid Tests

    SECTION("Registering an I-Type instruction with a blank name fails") {

        InstructionSet instrSet;
        std::unique_ptr<InstructionParser> parser(new ITypeInstructionParser());
        std::unique_ptr<TestHandler> handler(new TestHandler());
        REQUIRE_FALSE(instrSet.registerIType("", 10, std::move(parser), std::move(handler)));
        REQUIRE(instrSet.getType(10) == InstructionType::UNKNOWN);
        REQUIRE(instrSet.getType("") == InstructionType::UNKNOWN);
    }

    SECTION("Registering an I-Type instruction with just whitespace for a name fails") {

        InstructionSet instrSet;
        std::unique_ptr<InstructionParser> parser(new ITypeInstructionParser());
        std::unique_ptr<TestHandler> handler(new TestHandler());
        REQUIRE_FALSE(instrSet.registerIType("     ", 10, std::move(parser), std::move(handler)));
        REQUIRE(instrSet.getType(10) == InstructionType::UNKNOWN);
        REQUIRE(instrSet.getType("     ") == InstructionType::UNKNOWN);
    }

    SECTION("Registering an I-Type instruction with whitespace and ASCII fails") {

        InstructionSet instrSet;
        std::unique_ptr<InstructionParser> parser(new ITypeInstructionParser());
        std::unique_ptr<TestHandler> handler(new TestHandler());
        REQUIRE_FALSE(instrSet.registerIType("test diner", 10, std::move(parser), std::move(handler)));
        REQUIRE(instrSet.getType(10) == InstructionType::UNKNOWN);
        REQUIRE(instrSet.getType("test diner") == InstructionType::UNKNOWN);
    }

    SECTION("Registering an I-Type instruction with a newline fails") {

        InstructionSet instrSet;
        std::unique_ptr<InstructionParser> parser(new ITypeInstructionParser());
        std::unique_ptr<TestHandler> handler(new TestHandler());
        REQUIRE_FALSE(instrSet.registerIType("\ntest", 10, std::move(parser), std::move(handler)));
        REQUIRE(instrSet.getType(10) == InstructionType::UNKNOWN);
        REQUIRE(instrSet.getType("\ntest") == InstructionType::UNKNOWN);
    }

    SECTION("Registering an I-Type instruction with a tab fails") {

        InstructionSet instrSet;
        std::unique_ptr<InstructionParser> parser(new ITypeInstructionParser());
        std::unique_ptr<TestHandler> handler(new TestHandler());
        REQUIRE_FALSE(instrSet.registerIType("\ttest", 10, std::move(parser), std::move(handler)));
        REQUIRE(instrSet.getType(10) == InstructionType::UNKNOWN);
        REQUIRE(instrSet.getType("\ttest") == InstructionType::UNKNOWN);
    }

    SECTION("Registering an I-Type instruction with an opcode above max value fails") {

        InstructionSet instrSet;
        std::unique_ptr<InstructionParser> parser(new ITypeInstructionParser());
        std::unique_ptr<TestHandler> handler(new TestHandler());
        REQUIRE_FALSE(instrSet.registerIType("test", 64, std::move(parser), std::move(handler)));
        REQUIRE(instrSet.getType(10) == InstructionType::UNKNOWN);
        REQUIRE(instrSet.getType("test") == InstructionType::UNKNOWN);
    }

    SECTION("Registering an I-Type instruction with a null parser fails") {

        InstructionSet instrSet;
        std::unique_ptr<TestHandler> handler(new TestHandler());
        REQUIRE_FALSE(instrSet.registerIType("test", 10, nullptr, std::move(handler)));
        REQUIRE(instrSet.getType(10) == InstructionType::UNKNOWN);
        REQUIRE(instrSet.getType("test") == InstructionType::UNKNOWN);
    }

    SECTION("Registering an I-Type instruction with a null handler fails") {

        InstructionSet instrSet;
        std::unique_ptr<InstructionParser> parser(new ITypeInstructionParser());
        REQUIRE_FALSE(instrSet.registerIType("test", 10, std::move(parser), nullptr));
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
 *      handler     -> A unique_ptr to a handler for this specific instruction, non-null, unvalidated
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
 *      handler     -> nominal value
 * 
 * Invalid Tests:
 *      name string is empty
 *      name string is just whitespace
 *      name string with whitespace and ASCII
 *      name string with newline
 *      name string with tab
 *      opcode above max value
 *      parser null
 *      handler null
 *      attempting to register another j-type with the same opcode
 *      attempting to register anotiher j-type with the same name
 *      attempting to register a different format with the same opcode
 */
TEST_CASE("Instruction set is properly able to register J-Type instructions") {

    // MARK: -- Valid Tests

    SECTION("Registering a nominal J-Type instruction works properly") {

        InstructionSet instrSet;
        std::unique_ptr<InstructionParser> parser(new JTypeInstructionParser());
        std::unique_ptr<TestHandler> handler(new TestHandler());
        REQUIRE(instrSet.registerJType("test", 10, std::move(parser), std::move(handler)) == true);
        REQUIRE(instrSet.getType(10) == InstructionType::J_FORMAT);
        REQUIRE(instrSet.getType("test") == InstructionType::J_FORMAT);

        SECTION("Registering another J-Type instruction with the same opcode fails") {

            std::unique_ptr<InstructionParser> parser2(new JTypeInstructionParser());
            std::unique_ptr<TestHandler> handler2(new TestHandler());
            REQUIRE_FALSE(instrSet.registerJType("test2", 10, std::move(parser2), std::move(handler2)));
            REQUIRE(instrSet.getType(10) == InstructionType::J_FORMAT);
            REQUIRE(instrSet.getType("test") == InstructionType::J_FORMAT);
        }

        SECTION("Registering another J-Type instruction with the same name fails") {

            std::unique_ptr<InstructionParser> parser2(new JTypeInstructionParser());
            std::unique_ptr<TestHandler> handler2(new TestHandler());
            REQUIRE_FALSE(instrSet.registerJType("test", 30, std::move(parser2), std::move(handler2)));
            REQUIRE(instrSet.getType(30) == InstructionType::UNKNOWN);
            REQUIRE(instrSet.getType("test") == InstructionType::J_FORMAT);
        }

        SECTION("Registering a different format (R-Type) instruction with the same opcode fails") {

            std::unique_ptr<InstructionParser> parser2(new RTypeInstructionParser());
            std::unique_ptr<TestHandler> handler2(new TestHandler());
            REQUIRE_FALSE(instrSet.registerRType("test2", 10, 11, std::move(parser2), std::move(handler2)));
            REQUIRE(instrSet.getType(10) == InstructionType::J_FORMAT);
            REQUIRE(instrSet.getType("test") == InstructionType::J_FORMAT);
        }
    }

    SECTION("Registering an J-Type instruction with a min opcode works properly") {

        InstructionSet instrSet;
        std::unique_ptr<InstructionParser> parser(new JTypeInstructionParser());
        std::unique_ptr<TestHandler> handler(new TestHandler());
        REQUIRE(instrSet.registerJType("test", 0, std::move(parser), std::move(handler)) == true);
        REQUIRE(instrSet.getType(0) == InstructionType::J_FORMAT);
        REQUIRE(instrSet.getType("test") == InstructionType::J_FORMAT);
    }

    SECTION("Registering an J-Type instruction with a max opcode works properly") {

        InstructionSet instrSet;
        std::unique_ptr<InstructionParser> parser(new JTypeInstructionParser());
        std::unique_ptr<TestHandler> handler(new TestHandler());
        REQUIRE(instrSet.registerJType("test", 63, std::move(parser), std::move(handler)) == true);
        REQUIRE(instrSet.getType(63) == InstructionType::J_FORMAT);
        REQUIRE(instrSet.getType("test") == InstructionType::J_FORMAT);
    }

    SECTION("Registering an J-Type instruction with some uppercase letters in the name works properly") {

        InstructionSet instrSet;
        std::unique_ptr<InstructionParser> parser(new JTypeInstructionParser());
        std::unique_ptr<TestHandler> handler(new TestHandler());
        REQUIRE(instrSet.registerJType("TeSt", 10, std::move(parser), std::move(handler)) == true);
        REQUIRE(instrSet.getType(10) == InstructionType::J_FORMAT);
        REQUIRE(instrSet.getType("test") == InstructionType::J_FORMAT);
        REQUIRE(instrSet.getType("TeSt") == InstructionType::J_FORMAT);
    }


    // MARK: -- Invalid Tests

    SECTION("Registering an J-Type instruction with a blank name fails") {

        InstructionSet instrSet;
        std::unique_ptr<InstructionParser> parser(new JTypeInstructionParser());
        std::unique_ptr<TestHandler> handler(new TestHandler());
        REQUIRE_FALSE(instrSet.registerJType("", 10, std::move(parser), std::move(handler)));
        REQUIRE(instrSet.getType(10) == InstructionType::UNKNOWN);
        REQUIRE(instrSet.getType("") == InstructionType::UNKNOWN);
    }

    SECTION("Registering an J-Type instruction with just whitespace for a name fails") {

        InstructionSet instrSet;
        std::unique_ptr<InstructionParser> parser(new JTypeInstructionParser());
        std::unique_ptr<TestHandler> handler(new TestHandler());
        REQUIRE_FALSE(instrSet.registerJType("     ", 10, std::move(parser), std::move(handler)));
        REQUIRE(instrSet.getType(10) == InstructionType::UNKNOWN);
        REQUIRE(instrSet.getType("     ") == InstructionType::UNKNOWN);
    }

    SECTION("Registering an J-Type instruction with whitespace and ASCII fails") {

        InstructionSet instrSet;
        std::unique_ptr<InstructionParser> parser(new JTypeInstructionParser());
        std::unique_ptr<TestHandler> handler(new TestHandler());
        REQUIRE_FALSE(instrSet.registerJType("test bob", 10, std::move(parser), std::move(handler)));
        REQUIRE(instrSet.getType(10) == InstructionType::UNKNOWN);
        REQUIRE(instrSet.getType("test bob") == InstructionType::UNKNOWN);
    }

    SECTION("Registering an J-Type instruction with a newline fails") {

        InstructionSet instrSet;
        std::unique_ptr<InstructionParser> parser(new JTypeInstructionParser());
        std::unique_ptr<TestHandler> handler(new TestHandler());
        REQUIRE_FALSE(instrSet.registerJType("\ntest", 10, std::move(parser), std::move(handler)));
        REQUIRE(instrSet.getType(10) == InstructionType::UNKNOWN);
        REQUIRE(instrSet.getType("\ntest") == InstructionType::UNKNOWN);
    }

    SECTION("Registering an J-Type instruction with a tab fails") {

        InstructionSet instrSet;
        std::unique_ptr<InstructionParser> parser(new JTypeInstructionParser());
        std::unique_ptr<TestHandler> handler(new TestHandler());
        REQUIRE_FALSE(instrSet.registerJType("\ttest", 10, std::move(parser), std::move(handler)));
        REQUIRE(instrSet.getType(10) == InstructionType::UNKNOWN);
        REQUIRE(instrSet.getType("\ttest") == InstructionType::UNKNOWN);
    }

    SECTION("Registering an J-Type instruction with an opcode above max value fails") {

        InstructionSet instrSet;
        std::unique_ptr<InstructionParser> parser(new JTypeInstructionParser());
        std::unique_ptr<TestHandler> handler(new TestHandler());
        REQUIRE_FALSE(instrSet.registerJType("test", 64, std::move(parser), std::move(handler)));
        REQUIRE(instrSet.getType(10) == InstructionType::UNKNOWN);
        REQUIRE(instrSet.getType("test") == InstructionType::UNKNOWN);
    }

    SECTION("Registering a J-Type instruction with a null parser fails") {

        InstructionSet instrSet;
        std::unique_ptr<TestHandler> handler(new TestHandler());
        REQUIRE_FALSE(instrSet.registerJType("test", 10, nullptr, std::move(handler)));
        REQUIRE(instrSet.getType(10) == InstructionType::UNKNOWN);
        REQUIRE(instrSet.getType("test") == InstructionType::UNKNOWN);
    }

    SECTION("Registering a J-Type instruction with a null handler fails") {

        InstructionSet instrSet;
        std::unique_ptr<InstructionParser> parser(new JTypeInstructionParser());
        REQUIRE_FALSE(instrSet.registerJType("test", 10, std::move(parser), nullptr));
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
 *      handler     -> A unique_ptr to a handler for this specific instruction, non-null, unvalidated
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
 *      handler     -> nominal value
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
 *      handler null
 *      attempting to register another r-type with the same opcode & funct
 *      attempting to register another r-type with the same name
 */
TEST_CASE("Instruction set is properly able to register R-Type instructions") {

    // MARK: -- Valid Tests

    SECTION("Registering a nominal R-Type instruction works properly") {

        InstructionSet instrSet;
        std::unique_ptr<InstructionParser> parser(new RTypeInstructionParser());
        std::unique_ptr<TestHandler> handler(new TestHandler());
        REQUIRE(instrSet.registerRType("test", 10, 11, std::move(parser), std::move(handler)) == true);
        REQUIRE(instrSet.getType(10) == InstructionType::R_FORMAT);
        REQUIRE(instrSet.getType("test") == InstructionType::R_FORMAT);

        SECTION("Registering another R-Type instruction with the same opcode but different funct works properly") {

            std::unique_ptr<InstructionParser> parser2(new RTypeInstructionParser());
            std::unique_ptr<TestHandler> handler2(new TestHandler());
            REQUIRE(instrSet.registerRType("test2", 10, 12, std::move(parser2), std::move(handler2)) == true);
            REQUIRE(instrSet.getType(10) == InstructionType::R_FORMAT);
            REQUIRE(instrSet.getType("test") == InstructionType::R_FORMAT);
        }

        SECTION("Registering another R-Type instruction with the same opcode and type fails") {

            std::unique_ptr<InstructionParser> parser2(new RTypeInstructionParser());
            std::unique_ptr<TestHandler> handler2(new TestHandler());
            REQUIRE_FALSE(instrSet.registerRType("test2", 10, 11, std::move(parser2), std::move(handler2)));
            REQUIRE(instrSet.getType(10) == InstructionType::R_FORMAT);
            REQUIRE(instrSet.getType("test2") == InstructionType::UNKNOWN);
        }

        SECTION("Registering another R-Type instruction with the same name fails") {
            
            std::unique_ptr<InstructionParser> parser2(new RTypeInstructionParser());
            std::unique_ptr<TestHandler> handler2(new TestHandler());
            REQUIRE_FALSE(instrSet.registerRType("test", 12, 13, std::move(parser2), std::move(handler2)));
            REQUIRE(instrSet.getType(12) == InstructionType::UNKNOWN);
            REQUIRE(instrSet.getType("test") == InstructionType::R_FORMAT);
        }
    }

    SECTION("Registering an R-Type instruction with a min opcode works properly") {

        InstructionSet instrSet;
        std::unique_ptr<InstructionParser> parser(new RTypeInstructionParser());
        std::unique_ptr<TestHandler> handler(new TestHandler());
        REQUIRE(instrSet.registerRType("test", 0, 11, std::move(parser), std::move(handler)) == true);
        REQUIRE(instrSet.getType(0) == InstructionType::R_FORMAT);
        REQUIRE(instrSet.getType("test") == InstructionType::R_FORMAT);
    }

    SECTION("Registering an R-Type instruction with a max opcode works properly") {

        InstructionSet instrSet;
        std::unique_ptr<InstructionParser> parser(new RTypeInstructionParser());
        std::unique_ptr<TestHandler> handler(new TestHandler());
        REQUIRE(instrSet.registerRType("test", 63, 11, std::move(parser), std::move(handler)) == true);
        REQUIRE(instrSet.getType(63) == InstructionType::R_FORMAT);
        REQUIRE(instrSet.getType("test") == InstructionType::R_FORMAT);
    }

    SECTION("Registering an R-Type instruction with a min funct works properly") {

        InstructionSet instrSet;
        std::unique_ptr<InstructionParser> parser(new RTypeInstructionParser());
        std::unique_ptr<TestHandler> handler(new TestHandler());
        REQUIRE(instrSet.registerRType("test", 10, 0, std::move(parser), std::move(handler)) == true);
        REQUIRE(instrSet.getType(10) == InstructionType::R_FORMAT);
        REQUIRE(instrSet.getType("test") == InstructionType::R_FORMAT);
    }

    SECTION("Registering an R-Type instruction with a max funct works properly") {
        
        InstructionSet instrSet;
        std::unique_ptr<InstructionParser> parser(new RTypeInstructionParser());
        std::unique_ptr<TestHandler> handler(new TestHandler());
        REQUIRE(instrSet.registerRType("test", 10, 63, std::move(parser), std::move(handler)) == true);
        REQUIRE(instrSet.getType(10) == InstructionType::R_FORMAT);
        REQUIRE(instrSet.getType("test") == InstructionType::R_FORMAT);
    }

    SECTION("Registering an R-Type instruction with some uppercase letters in the name works properly") {

        InstructionSet instrSet;
        std::unique_ptr<InstructionParser> parser(new RTypeInstructionParser());
        std::unique_ptr<TestHandler> handler(new TestHandler());
        REQUIRE(instrSet.registerRType("TeSt", 10, 63, std::move(parser), std::move(handler)) == true);
        REQUIRE(instrSet.getType(10) == InstructionType::R_FORMAT);
        REQUIRE(instrSet.getType("test") == InstructionType::R_FORMAT);
        REQUIRE(instrSet.getType("TeSt") == InstructionType::R_FORMAT);
    }


    // MARK: -- Invalid Tests

    SECTION("Registering an R-Type instruction with a blank name fails") {

        InstructionSet instrSet;
        std::unique_ptr<InstructionParser> parser(new RTypeInstructionParser());
        std::unique_ptr<TestHandler> handler(new TestHandler());
        REQUIRE_FALSE(instrSet.registerRType("", 10, 11, std::move(parser), std::move(handler)));
        REQUIRE(instrSet.getType(10) == InstructionType::UNKNOWN);
        REQUIRE(instrSet.getType("") == InstructionType::UNKNOWN);
    }

    SECTION("Registering an R-Type instruction with just whitespace for a name fails") {

        InstructionSet instrSet;
        std::unique_ptr<InstructionParser> parser(new RTypeInstructionParser());
        std::unique_ptr<TestHandler> handler(new TestHandler());
        REQUIRE_FALSE(instrSet.registerRType("     ", 10, 11, std::move(parser), std::move(handler)));
        REQUIRE(instrSet.getType(10) == InstructionType::UNKNOWN);
        REQUIRE(instrSet.getType("     ") == InstructionType::UNKNOWN);
    }

    SECTION("Registering an R-Type instruction with whitespace and ASCII fails") {

        InstructionSet instrSet;
        std::unique_ptr<InstructionParser> parser(new RTypeInstructionParser());
        std::unique_ptr<TestHandler> handler(new TestHandler());
        REQUIRE_FALSE(instrSet.registerRType("test bob", 10, 11, std::move(parser), std::move(handler)));
        REQUIRE(instrSet.getType(10) == InstructionType::UNKNOWN);
        REQUIRE(instrSet.getType("test bob") == InstructionType::UNKNOWN);
    }

    SECTION("Registering an R-Type instruction with a newline fails") {

        InstructionSet instrSet;
        std::unique_ptr<InstructionParser> parser(new RTypeInstructionParser());
        std::unique_ptr<TestHandler> handler(new TestHandler());
        REQUIRE_FALSE(instrSet.registerRType("\ntest", 10, 11, std::move(parser), std::move(handler)));
        REQUIRE(instrSet.getType(10) == InstructionType::UNKNOWN);
        REQUIRE(instrSet.getType("\ntest") == InstructionType::UNKNOWN);
    }

    SECTION("Registering an R-Type instruction with a tab fails") {

        InstructionSet instrSet;
        std::unique_ptr<InstructionParser> parser(new RTypeInstructionParser());
        std::unique_ptr<TestHandler> handler(new TestHandler());
        REQUIRE_FALSE(instrSet.registerRType("\ttest", 10, 11, std::move(parser), std::move(handler)));
        REQUIRE(instrSet.getType(10) == InstructionType::UNKNOWN);
        REQUIRE(instrSet.getType("\ttest") == InstructionType::UNKNOWN);
    }

    SECTION("Registering an R-Type instruction with an opcode above max value fails") {

        InstructionSet instrSet;
        std::unique_ptr<InstructionParser> parser(new RTypeInstructionParser());
        std::unique_ptr<TestHandler> handler(new TestHandler());
        REQUIRE_FALSE(instrSet.registerRType("test", 64, 11, std::move(parser), std::move(handler)));
        REQUIRE(instrSet.getType(10) == InstructionType::UNKNOWN);
        REQUIRE(instrSet.getType("test") == InstructionType::UNKNOWN);
    }

    SECTION("Registering an R-Type instruction with a funct above max value fails") {

        InstructionSet instrSet;
        std::unique_ptr<InstructionParser> parser(new RTypeInstructionParser());
        std::unique_ptr<TestHandler> handler(new TestHandler());
        REQUIRE_FALSE(instrSet.registerRType("test", 10, 64, std::move(parser), std::move(handler)));
        REQUIRE(instrSet.getType(10) == InstructionType::UNKNOWN);
        REQUIRE(instrSet.getType("test") == InstructionType::UNKNOWN);
    }

    SECTION("Registering an R-Type instruction with a null parser fails") {

        InstructionSet instrSet;
        std::unique_ptr<TestHandler> handler(new TestHandler());
        REQUIRE_FALSE(instrSet.registerRType("test", 10, 11, nullptr, std::move(handler)));
        REQUIRE(instrSet.getType(10) == InstructionType::UNKNOWN);
        REQUIRE(instrSet.getType("test") == InstructionType::UNKNOWN);
    }

    SECTION("Registering an R-Type instruction with a null handler fails") {

        InstructionSet instrSet;
        std::unique_ptr<InstructionParser> parser(new RTypeInstructionParser());
        REQUIRE_FALSE(instrSet.registerRType("test", 10, 11, std::move(parser), nullptr));
        REQUIRE(instrSet.getType(10) == InstructionType::UNKNOWN);
        REQUIRE(instrSet.getType("test") == InstructionType::UNKNOWN);
    }
}



// MARK: -- Psuedo Registration Methods

/**
 * Method: InstructionSet::registerPsuedoType(..)
 * Desired Confidence Level: Boundary value analysis
 * 
 * Inputs:
 *      name        -> A string value without whitespace or delimiter, will be converted to lowercase, unvalidated
 *      parser      -> A unique_ptr to a parser for this specific instruction, non-null, unvalidated
 * 
 * Outputs:
 *      The function returns true if the instruction was registered successfully, otherwise it
 *          returns false
 * 
 * Valid Tests:
 *      name        -> nominal value
 *                     some uppercase letters
 *      parser      -> nominal value
 * 
 * Invalid Tests:
 *      name string is empty
 *      name string is just whitespace
 *      name string with whitespace and ASCII
 *      name string with newline
 *      name string with tab
 *      parser null
 *      attempting to register another psuedo instruction with the same name
 *      attempting to register another type with the same name
 */
TEST_CASE("Instruction set is properly able to register psuedo-instructions") {

    // MARK: -- Valid Tests

    SECTION("Registering a nominal psuedo instruction works properly") {

        InstructionSet instrSet;
        std::unique_ptr<PsuedoTypeInstructionParser> parser(new PsuedoTypeInstructionParser());
        REQUIRE(instrSet.registerPsuedoType("test", std::move(parser)) == true);
        REQUIRE(instrSet.getType("test") == InstructionType::PSUEDO);

        SECTION("Registering another psuedo instruction with the same name fails") {

            std::unique_ptr<PsuedoTypeInstructionParser> parser2(new PsuedoTypeInstructionParser());
            REQUIRE_FALSE(instrSet.registerPsuedoType("test", std::move(parser2)));
            REQUIRE(instrSet.getType("test") == InstructionType::PSUEDO);
        }

        SECTION("Registering an R-Type instruction with the same name fails") {

            std::unique_ptr<RTypeInstructionParser> parser2(new RTypeInstructionParser());
            std::unique_ptr<TestHandler> handler2(new TestHandler());
            REQUIRE_FALSE(instrSet.registerRType("test", 10, 11, std::move(parser2), std::move(handler2)));
            REQUIRE(instrSet.getType("test") == InstructionType::PSUEDO);
        }
    }

    SECTION("Registering a psuedo instruction with some uppercase letters in the name works properly") {

        InstructionSet instrSet;
        std::unique_ptr<PsuedoTypeInstructionParser> parser(new PsuedoTypeInstructionParser());
        REQUIRE(instrSet.registerPsuedoType("tEsT", std::move(parser)) == true);
        REQUIRE(instrSet.getType("test") == InstructionType::PSUEDO);
        REQUIRE(instrSet.getType("tEsT") == InstructionType::PSUEDO);
    }

    
    // MARK: -- Invalid Tests

    SECTION("Registering a psuedo instruction with an empty name fails") {

        InstructionSet instrSet;
        std::unique_ptr<PsuedoTypeInstructionParser> parser(new PsuedoTypeInstructionParser());
        REQUIRE_FALSE(instrSet.registerPsuedoType("", std::move(parser)));
        REQUIRE(instrSet.getType("") == InstructionType::UNKNOWN);
    }

    SECTION("Registering a psuedo instruction with whitespace fails") {

        InstructionSet instrSet;
        std::unique_ptr<PsuedoTypeInstructionParser> parser(new PsuedoTypeInstructionParser());
        REQUIRE_FALSE(instrSet.registerPsuedoType("    ", std::move(parser)));
        REQUIRE(instrSet.getType("    ") == InstructionType::UNKNOWN);
    }

    SECTION("Registering a psuedo instruction with whitespace and ASCII fails") {

        InstructionSet instrSet;
        std::unique_ptr<PsuedoTypeInstructionParser> parser(new PsuedoTypeInstructionParser());
        REQUIRE_FALSE(instrSet.registerPsuedoType("test bob", std::move(parser)));
        REQUIRE(instrSet.getType("test bob") == InstructionType::UNKNOWN);
    }

    SECTION("Registering a psuedo instruction with a newline fails") {

        InstructionSet instrSet;
        std::unique_ptr<PsuedoTypeInstructionParser> parser(new PsuedoTypeInstructionParser());
        REQUIRE_FALSE(instrSet.registerPsuedoType("\ntest", std::move(parser)));
        REQUIRE(instrSet.getType("\ntest") == InstructionType::UNKNOWN);
    }

    SECTION("Registering a psuedo instruction with a tab fails") {

        InstructionSet instrSet;
        std::unique_ptr<PsuedoTypeInstructionParser> parser(new PsuedoTypeInstructionParser());
        REQUIRE_FALSE(instrSet.registerPsuedoType("\ttest", std::move(parser)));
        REQUIRE(instrSet.getType("\ttest") == InstructionType::UNKNOWN);
    }

    SECTION("Registering a psuedo instruction with a null parser fails") {

        InstructionSet instrSet;
        REQUIRE_FALSE(instrSet.registerPsuedoType("test", nullptr));
        REQUIRE(instrSet.getType("test") == InstructionType::UNKNOWN);
    }
}