#include "mocks/handlers/test_handler.hpp"

// On post decode
void TestHandler::onPostDecode(InstructionDecodeBuffer& decodeBuffer, const RegisterBank& registerBank, Memory::addr_t& PC) { }

// On execute
word_t TestHandler::onExecute(const InstructionDecodeBuffer& decodeBuffer) { return 0; }

// On memory
word_t TestHandler::onMemory(const ExecutionBuffer& executionBuffer, const Memory& memory) { return 0; }