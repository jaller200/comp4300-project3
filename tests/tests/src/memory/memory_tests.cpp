#include "tests/include/catch.hpp"

#include "memory/memory.hpp"
#include "types.hpp"

#include <iostream>

TEST_CASE("Memory can be written to and read from", "[memory]") {

    size_t dataSize = 0x2000;
    size_t textSize = 0x1000;
    Memory memory(dataSize, textSize);

    REQUIRE(memory.getDataSize() == dataSize);
    REQUIRE(memory.getTextSize() == textSize);
    REQUIRE(memory.getTotalSize() == dataSize + textSize);


    // MARK: -- Byte Reads / Writes
    /**
     * Desired Confidence: boundary-value analysis
     * 
     * Valid Tests:
     *      Read / write value at nominal address
     *      Read / write value on low-boundary and high boundary - sizeof(byte_t)
     * 
     * Valid Outputs:
     *      True for write, true for read and valid number
     *      True for write, true for read and valid number
     * 
     * Invalid Tests:
     *      Read value one under low-boundary or on high boundary
     *      Read value under low-boundary and above high boundary
     * 
     *      Write value one under low-boundary or on high boundary
     *      Write value under low-boundary and above high boundary
     * 
     * Invalid Outputs:
     *      False for all function calls
     */
    SECTION("writing and reading byte works properly") {
        
        byte_t byte;
        REQUIRE(memory.writeByte(0x1500, 0x2) == true);
        REQUIRE(memory.readByte(0x1500, byte) == true);
        REQUIRE(byte == 0x2);
    }

    SECTION("writing and reading byte on but within the byte boundaries succeeds") {

        byte_t byte;
        REQUIRE(memory.writeByte(0x1000, 0x2) == true);
        REQUIRE(memory.readByte(0x1000, byte) == true);
        REQUIRE(byte == 0x2);

        REQUIRE(memory.writeByte(0x1000+textSize+dataSize-1, 0x3) == true);
        REQUIRE(memory.readByte(0x1000+textSize+dataSize-1, byte) == true);
        REQUIRE(byte == 0x3);
    }

    SECTION("writing byte at the byte boundaries fails") {

        REQUIRE(memory.writeByte(0x1000-1, 0x2) == false);
        REQUIRE(memory.writeByte(0x1000+textSize+dataSize, 0x2) == false);
    }

    SECTION("writing byte outside of byte boundaries fails") {

        REQUIRE(memory.writeByte(0x2, 0x2) == false);
        REQUIRE(memory.writeByte(0x1000+textSize+dataSize+100, 0x2) == false);
    }

    SECTION("reading byte at the byte boundaries fails") {

        byte_t byte;
        REQUIRE(memory.readByte(0x1000-1, byte) == false);
        REQUIRE(memory.readByte(0x1000+textSize+dataSize, byte) == false);
    }

    SECTION("reading byte outside of byte boundaries fails") {

        byte_t byte;
        REQUIRE(memory.readByte(0x2, byte) == false);
        REQUIRE(memory.readByte(0x1000+textSize+dataSize+100, byte) == false);
    }


    // MARK: -- Word Reads / Writes
    /**
     * Desired Confidence: boundary-value analysis
     * 
     * Valid Tests:
     *      Read / write value at nominal address
     *      Read / write value on low-boundary and high boundary - sizeof(word_t)
     * 
     * Valid Outputs:
     *      True for write, true for read and valid number
     *      True for write, true for read and valid number
     * 
     * Invalid Tests:
     *      Read value one under low-boundary or on high boundary - sizeof(word_t) + 1
     *      Read value under low-boundary and above high boundary
     * 
     *      Write value one under low-boundary or on high boundary - sizeof(word_t) + 1
     *      Write value under low-boundary and above high boundary
     * 
     * Invalid Outputs:
     *      False for all function calls
     */
    SECTION("writing and reading word works properly") {
        
        word_t word;
        REQUIRE(memory.writeWord(0x1500, 0x12345678) == true);
        REQUIRE(memory.readWord(0x1500, word) == true);
        REQUIRE(word == 0x12345678);
    }

    SECTION("writing and reading word on but within the byte boundaries succeeds") {

        word_t word;
        REQUIRE(memory.writeWord(0x1000, 0x12345678) == true);
        REQUIRE(memory.readWord(0x1000, word) == true);
        REQUIRE(word == 0x12345678);

        REQUIRE(memory.writeWord(0x1000+textSize+dataSize-4, 0x33333314) == true);
        REQUIRE(memory.readWord(0x1000+textSize+dataSize-4, word) == true);
        REQUIRE(word == 0x33333314);
    }

    SECTION("writing word at the byte boundaries fails") {

        REQUIRE(memory.writeWord(0x1000-1, 0x12345678) == false);
        REQUIRE(memory.writeWord(0x1000+textSize+dataSize-3, 0x12345678) == false);
    }

    SECTION("writing word outside of byte boundaries fails") {

        REQUIRE(memory.writeWord(0x2, 0x12345678) == false);
        REQUIRE(memory.writeWord(0x1000+textSize+dataSize+100, 0x12345678) == false);
    }

    SECTION("reading word at the byte boundaries fails") {

        word_t word;
        REQUIRE(memory.readWord(0x1000-1, word) == false);
        REQUIRE(memory.readWord(0x1000+textSize+dataSize-3, word) == false);
    }

    SECTION("reading word outside of byte boundaries fails") {

        word_t word;
        REQUIRE(memory.readWord(0x2, word) == false);
        REQUIRE(memory.readWord(0x1000+textSize+dataSize+100, word) == false);
    }


    // MARK: -- String Read / Writes
    /**
     * Desired Confidence: boundary-value analysis
     * 
     * Valid Tests:
     *      Write / read string at nominal address
     *      Write / read string on low-boundary and high boundary - sizeof(str)
     *      Write string at address and read it from starting address + 1.
     * 
     * Valid Outputs:
     *      True for write, true for read and valid string
     *      True for write, true for read and valid string
     *      True for write, true for read and valid string w/ missing first character
     * 
     * Invalid Tests:
     *      Write value starting one under low-boundary or on high boundary - sizeof(str) + 1
     *      Write value starting under low-boundary and above high boundary
     * 
     *      Read value starting at one under low-boundary on on the high boundary
     *      Read value starting under low-boundary and above high boundary
     * 
     * Invalid Outputs:
     *      False for all function calls
     */
    SECTION("writing and reading strings works properly") {

        ascii_t str;
        REQUIRE(memory.writeString(0x1500, "test") == true);
        
        byte_t byte;
        memory.readByte(0x1500, byte);
        REQUIRE(byte == 't');
        memory.readByte(0x1502, byte);
        REQUIRE(byte == 's');
        memory.readByte(0x1504, byte);
        REQUIRE(byte == '\0');

        REQUIRE(memory.readString(0x1500, str) == true);
        REQUIRE(str == "test");
    }

    SECTION("writing and reading string on but within the byte boundaries succeeds") {

        ascii_t str;
        REQUIRE(memory.writeString(0x1000, "test") == true);
        REQUIRE(memory.readString(0x1000, str) == true);
        REQUIRE(str == "test");

        REQUIRE(memory.writeString(0x1000+textSize+dataSize-5, "gary") == true);
        REQUIRE(memory.readString(0x1000+textSize+dataSize-5, str) == true);
        REQUIRE(str == "gary");
    }

    SECTION("writing string then reading partial string works properly") {

        ascii_t str;
        REQUIRE(memory.writeString(0x1300, "bobby") == true);
        REQUIRE(memory.readString(0x1300+1, str) == true);
        REQUIRE(str == "obby");
    }

    SECTION("writing string at the byte boundaries fails") {

        REQUIRE(memory.writeString(0x1000-1, "test") == false);
        REQUIRE(memory.writeString(0x1000+textSize+dataSize-4, "test") == false);
    }

    SECTION("writing string outside of byte boundaries fails") {
        
        REQUIRE(memory.writeString(0x2, "test") == false);
        REQUIRE(memory.writeString(0x1000+textSize+dataSize+100, "test") == false);
    }

    SECTION("reading string at the byte boundaries fails") {

        ascii_t str;
        REQUIRE(memory.readString(0x1000-1, str) == false);
        REQUIRE(memory.readString(0x1000+textSize+dataSize, str) == false);
    }

    SECTION("reading string outside of byte boundaries fails") {

        ascii_t str;
        REQUIRE(memory.readString(0x2, str) == false);
        REQUIRE(memory.readString(0x1000+textSize+dataSize+100, str) == false);
    }
}