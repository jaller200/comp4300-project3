#pragma once

/**
 * A simple class of opcodes.
 */
enum class Opcodes {

    // MARK: -- Opcodes
    OPCODE_R_TYPE,          // 0 - All R-Type instructions have an opcode of 0
    OPCODE_BZ,              // 1 - All Branch on Zero instructions
    OPCODE_J,               // 2 - Jump to address
    OPCODE_JAL,             // 3 - Jump to address and link
    OPCODE_BEQ,             // 4 - Branch if equal
    OPCODE_BNE,             // 5 - Branch if not equal
    OPCODE_BLEZ,            // 6 - Branch on less than or equal to zero
    OPCODE_BGTZ,            // 7 - Branch on greather than or equal to zero
    OPCODE_ADDI,            // 8 - Add immediate
    OPCODE_ADDIU,           // 9 - Add immedate unsigned
    OPCODE_SLTI,            // 10 - Shift left immediate
    OPCODE_SLTIU,           // 11 - Shift left immediate unsigned
    OPCODE_ANDI,            // 12 - Bitwise AND immediate
    OPCODE_ORI,             // 13 - Bitwise OR immediate
    OPCODE_XORI,            // 14 - Bitwise XOR immediate
    OPCODE_LUI,             // 15 - Load upper immediate (imm << 16)
    OPCODE_LB,              // 16 - Load byte
    OPCODE_LH,              // 17 - Load half word
    OPCODE_LW,              // 18 - Load word
    OPCODE_LBU,             // 19 - Load byte unsigned
    OPCODE_LHU,             // 20 - Load half word unsigned
    OPCODE_SB,              // 21 - Store byte
    OPCODE_SH,              // 22 - Store half word
    OPCODE_SW               // 23 - Store word
};