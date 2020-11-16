#pragma once

#include <cstddef>

#include "memory/memory.hpp"

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
     */
    Simulator(const Memory& memory);

    /**
     * Destructor
     */
    ~Simulator() = default;

private:

    // MARK: -- Private Variables

    /** The memory of the program. */
    Memory m_memory;
};