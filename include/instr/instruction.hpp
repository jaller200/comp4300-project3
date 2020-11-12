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
    using funct_t = byte_t;         // A type holding a 6-bit function type

    // Values
    using imm_t = shword_t;         // A type holding a 16-bit signed immediate value
    using reg_t = byte_t;           // A type holding a 5-bit register number (0-32)
    using shamt_t = byte_t;         // A type holding a 5-bit shift amount (0-32)

private:

    // MARK: -- Private Variables

    /** The function type. */
    funct_t m_funct;

    /** 16-bit immediate value. */
    imm_t m_immediate;

    /** Destination register. */
    reg_t m_regRd;

    /** Source register(s) */
    reg_t m_regRs, m_regRt;

    /** The shift amount. */
    shamt_t m_shamt;

    /** The instruction type. */
    InstructionType m_type;

public:

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
     * Returns the function types.
     * @return The function type
     */
    funct_t getFunct() const;

    /**
     * Returns the signed 16-bit immediate value.
     * @return The immediate value
     */
    imm_t getImmediate() const;

    /**
     * Returns the destination register.
     * @return The destination register
     */
    reg_t getRd() const;

    /**
     * Returns the first source register.
     * @return The first source register
     */
    reg_t getRs() const;

    /**
     * Returns the second source register.
     * @return The second source register
     */
    reg_t getRt() const;

    /**
     * Returns the shift amount.
     * @return The shift amount
     */
    shamt_t getShamt() const;

    /**
     * Returns the instruction type.
     * @return The instruction type
     */
    InstructionType getType() const;

    /**
     * Sets the function type.
     * @param funct The function type
     */
    void setFunct(funct_t funct);

    /**
     * Sets the immediate value
     * @param immediate The immediate value
     */
    void setImmediate(imm_t immediate);

    /**
     * Sets the destination register.
     * @param rd The destination register
     */
    void setRd(reg_t rd);

    /**
     * Sets the first source register.
     * @param rs The first source register
     */
    void setRs(reg_t rs);

    /**
     * Sets the second source register.
     * @param rt The second source register
     */
    void setRt(reg_t rt);

    /**
     * Sets the shift amount.
     * @param shamt The shift amount
     */
    void setShamt(shamt_t shamt);

    /**
     * Sets the instruction type.
     * @param type The type
     */
    void setType(InstructionType type);
};