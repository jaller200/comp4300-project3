#include "simulator.hpp"

// MARK: -- Construction

// Constructs the simulator
Simulator::Simulator(std::unique_ptr<Memory> memory, std::unique_ptr<RegisterBank> registerBank)
: m_memory(std::move(memory))
, m_registerBank(std::move(registerBank))
{ }