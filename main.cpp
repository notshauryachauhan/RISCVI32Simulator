#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>

#include "Memory.h"
#include "ALU.h"
#include "RegisterFile.h"
#include "CPU.h"
#include "Decoder.h"


int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <program_file>" << std::endl;
        return 1;
    }

    Memory memory;
    memory.loadProgram(argv[1]);

    std::cout << "Loaded program with " << memory.instructionCount() << " instructions." << std::endl;

    for (uint32_t i = 0; i < memory.instructionCount(); ++i) {
        uint32_t instruction = memory.fetchInstruction(i*4);
        std::cout << "Instruction at address " << i << ": " << std::hex << instruction << std::endl;
    }

    return 0;
}