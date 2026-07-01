#include "Memory.h"

#include <string>
#include <fstream>
#include <iostream>
#include <cstdint>
#include <vector>

void Memory::loadProgram(const std::string& filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open the file." << std::endl;
        return;
    }

    std::string line;

    while(std::getline(file, line)){
        if(line.empty()){
            continue;
        }

        uint32_t instruction = std::stoul(line, nullptr, 2);
        instrMem.push_back(instruction);
    }
}

uint32_t Memory::fetchInstruction(uint32_t address) const {
    if (address < instrMem.size() * 4) {
        return instrMem[address/4];
    } else {
        std::cerr << "Error: Instruction address out of bounds." << std::endl;
        return 0;
    }
}

uint32_t Memory::instructionCount() const {
    return instrMem.size();
}