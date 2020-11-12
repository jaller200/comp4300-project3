#pragma once

/**
 * A basic class that holds an instruction set.
 * 
Instructions will be registered by Opcode & Function (if defined).
 * 
 *      Opcode      : 6 bits
 *      Function    : 6 bits
 * 
 * Registration will be done with 16 bits, where the first 6 bits are the opcode
 * and the second 6 bits are the function (if necessary). This way I-Type (opcode 0)
 * instructions can be stored just as easily as R-Type and branch.
 */
class InstructionSet {
public:

    // MARK: -- Construction
    InstructionSet() = default;
    ~InstructionSet() = default;
};