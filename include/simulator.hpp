#pragma once

#include <memory>

#include "memory/memory.hpp"
#include "registers/register_bank.hpp"

/**
 * The main simulator class. Responsible for opening, running, and
 * controlling all aspects of the simulation.
 */
class Simulator {
public:

    // MARK: -- Construction

    /**
     * Constructor.
     * @param memory The memory for the simulator to use
     * @param registerBank The register bank to use
     */
    Simulator(std::unique_ptr<Memory> memory, std::unique_ptr<RegisterBank> registerBank);

    /**
     * Destructor
     */
    ~Simulator() = default;

private:

    // MARK: -- Private Variables

    /** The memory of the program. */
    std::unique_ptr<Memory> m_memory;

    /** The register bank of the program. */
    std::unique_ptr<RegisterBank> m_registerBank;
};