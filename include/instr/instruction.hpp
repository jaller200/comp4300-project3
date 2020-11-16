#pragma once

#include "instr/instruction_type.hpp"
#include "types.hpp"

/**
 * An instruction class. 
 * 
 * This class can be constructed via the InstructionBuilder class.
 */
class Instruction {
public:

    // MARK: -- Public Types

    // Instructions
    using instr_t = word_t;         // A type holding an instruction


    // MARK: -- Public Constants

    // Flags
    static constexpr word_t FLAG_OPCODE     = 0x3F;             // Bits 0-5 (6 bits)
    static constexpr word_t FLAG_RS         = 0x7C0;            // Bits 6-11 (5 bits)
    static constexpr word_t FLAG_RT         = 0xF800;           // Bits 11-15 (5 bits)
    static constexpr word_t FLAG_RD         = 0x1F0000;         // Bits 16-20 (5 bits)
    static constexpr word_t FLAG_SHAMT      = 0x3E00000;        // Bits 21-25 (5 bits)
    static constexpr word_t FLAG_FUNCT      = 0xFC000000;       // Bits 26-31 (upper 6 bits)
    static constexpr word_t FLAG_IMM        = 0xFFFF0000;       // Bits 16-31 (upper 16 bits)
    static constexpr word_t FLAG_ADDR       = 0xFFFFFFC0;       // Bits 6-31 (upper 26 bits)

    // Limits (starting at 0 and ending at number)
    static constexpr word_t LIMIT_OPCODE    = 63;               // 6 bits (2^6-1 = 63)
    static constexpr word_t LIMIT_RS        = 31;               // 5 bits (2^5-1 = 31)
    static constexpr word_t LIMIT_RT        = 31;               // 5 bits (2^5-1 = 31)
    static constexpr word_t LIMIT_RD        = 31;               // 5 bits (2^5-1 = 31)
    static constexpr word_t LIMIT_SHAMT     = 31;               // 5 bits (2^5-1 = 31)
    static constexpr word_t LIMIT_FUNCT     = 63;               // 6 bits (2^6-1 = 63)
    static constexpr word_t LIMIT_IMM       = 65535;            // 16 bits (2^16-1 = 65,535)
    static constexpr word_t LIMIT_ADDR      = 67108863;         // 26 bits (2^26-1 = 67,108,863)


    // MARK: -- Construction
    Instruction();
    ~Instruction() = default;


    // MARK: -- Instruction Methods

    /**
     * Resets the entire instructions to 0s / unknown.
     */
    void reset();


    // MARK: -- Getters / Setters

    /**
     * Returns the address.
     * @return The address
     */
    word_t getAddr() const;

    /**
     * Returns the function types.
     * @return The function type
     */
    word_t getFunct() const;

    /**
     * Returns the signed 16-bit immediate value.
     * @return The immediate value
     */
    word_t getImmediate() const;

    /**
     * Returns the opcode.
     * @return The opcode
     */
    word_t getOpcode() const;

    /**
     * Returns the destination register.
     * @return The destination register
     */
    word_t getRd() const;

    /**
     * Returns the first source register.
     * @return The first source register
     */
    word_t getRs() const;

    /**
     * Returns the second source register.
     * @return The second source register
     */
    word_t getRt() const;

    /**
     * Returns the shift amount.
     * @return The shift amount
     */
    word_t getShamt() const;

    /**
     * Returns the instruction type.
     * @return The instruction type
     */
    InstructionType getType() const;

    /**
     * Sets the address.
     * @param addr The address to set
     * @return Whether or not the address was set
     */
    bool setAddr(word_t addr);

    /**
     * Sets the function type.
     * @param funct The function type
     * @return Whether or not the function was set
     */
    bool setFunct(word_t funct);

    /**
     * Sets the immediate value
     * @param immediate The immediate value
     * @return Whether or not the immediate value was set
     */
    bool setImmediate(word_t immediate);

    /**
     * Sets the opcode.
     * @param opcode The opcode
     * @return Whether or not the opcode was set
     */
    bool setOpcode(word_t opcode);

    /**
     * Sets the destination register.
     * @param rd The destination register
     * @return Whether or not the destination register was set
     */
    bool setRd(word_t rd);

    /**
     * Sets the first source register.
     * @param rs The first source register
     * @return Whether or not the first source register was set
     */
    bool setRs(word_t rs);

    /**
     * Sets the second source register.
     * @param rt The second source register
     * @return Whether or not the second source register was set
     */
    bool setRt(word_t rt);

    /**
     * Sets the shift amount.
     * @param shamt The shift amount
     * @return Whether or not the shift amount was set
     */
    bool setShamt(word_t shamt);

    /**
     * Sets the instruction type.
     * @param type The type
     */
    void setType(InstructionType type);

private:

    // MARK: -- Private Variables

    /** The address. */
    word_t m_wAddr;

    /** The function type. */
    word_t m_wFunct;

    /** 16-bit immediate value. */
    word_t m_wImmediate;

    /** The opcode. */
    word_t m_wOpcode;

    /** Destination register. */
    word_t m_wRegRd;

    /** Source register(s) */
    word_t m_wRegRs, m_wRegRt;

    /** The shift amount. */
    word_t m_wShamt;

    /** The instruction type. */
    InstructionType m_type;
};