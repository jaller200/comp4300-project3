#include "tests/include/catch.hpp"

#include "memory/memory.h"
#include "types.h"

TEST_CASE("Memory can be written to and read from", "[memory]") {

    size_t dataSize = 0x2000;
    size_t textSize = 0x1000;
    Memory memory(dataSize, textSize);

    REQUIRE(memory.getDataSize() == dataSize);
    REQUIRE(memory.getTextSize() == textSize);
    REQUIRE(memory.getTotalSize() == dataSize + textSize);


    // MARK: -- Byte Reads / Writes
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
}