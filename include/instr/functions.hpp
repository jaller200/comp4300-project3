#pragma once

/**
 * A collection of R-Type functions.
 */
enum class Functions {

    // MARK: -- Functions
    FUNCT_SLL,                  // 0 - Left shift (shamt)
    FUNCT_UNUSED_1,             // 1 - ???
    FUNCT_SRL,                  // 2 - Unsigned right shift (shamt)
    FUNCT_SRA,                  // 3 - Signed right shift (shamt)
    FUNCT_SLLV,                 // 4 -  Left shift from register
    FUNCT_UNUSED_5,             // 5 - ???
    FUNCT_SRLV,                 // 6 - Unsigned right shift from register
    FUNCT_SRAV,                 // 7 - Signed right shift from register
    FUNCT_JR,                   // 8 - Jump from register
    FUNCT_JALR,                 // 9 - Jump and link from register (undefined if RS=RD, RS must be multiple of 4)
    FUNCT_UNUSED_10,            // 10 - ???
    FUNCT_UNUSED_11,            // 11 - ???
    FUNCT_SYSCALL,              // 12 - System call
    FUNCT_UNUSED_13,            // 13 - ???
    FUNCT_UNUSED_14,            // 14 - ???
    FUNCT_UNUSED_15,            // 15 - ???
    FUNCT_MFHI,                 // 16 - Move from HI
    FUNCT_MTHI,                 // 17 - Move to HI
    FUNCT_MFLO,                 // 18 - Move from LO
    FUNCT_MTLO,                 // 19 - Move to LO
    FUNCT_UNUSED_20,            // 20 - ???
    FUNCT_UNUSED_21,            // 21 - ???
    FUNCT_UNUSED_22,            // 22 - ???
    FUNCT_UNUSED_23,            // 23 - ??? 
    FUNCT_MULT,                 // 24 - Signed multiplication -> {HI, LO}
    FUNCT_MULTU,                // 25 - Unsigned multiplication -> {HI, LO}
    FUNCT_DIV,                  // 26 - Signed division {LO = RS/RD, HI = RS % RD}
    FUNCT_DIVU,                 // 27 - Unsigned division {LO = RS/RD, HI = RS % RD}
    FUNCT_UNUSED_28,            // 28 - ???
    FUNCT_UNUSED_29,            // 29 - ???
    FUNCT_UNUSED_30,            // 30 - ???
    FUNCT_UNUSED_31,            // 31 - ???
    FUNCT_ADD,                  // 32 - Signed add (exception on signed overflow)
    FUNCT_ADDU,                 // 33 - Unsigned add
    FUNCT_SUB,                  // 34 - Signed sub (exception on signed overflow)
    FUNCT_SUBU,                 // 35 - Unsigned sub
    FUNCT_AND,                  // 36 - Bitwise AND
    FUNCT_OR,                   // 37 - Bitwise OR
    FUNCT_XOR,                  // 38 - Bitwise XOR
    FUNCT_NOR,                  // 39 - Bitwise NOR
    FUNCT_UNUSED_40,            // 40 - ???
    FUNCT_UNUSED_41,            // 41 - ???
    FUNCT_SLT,                  // 42 - Signed comparison
    FUNCT_SLTU,                 // 43 - Unsigned comparison
};