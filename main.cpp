#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>

#include "include/Memory.h"
#include "ALU.h"
#include "RegisterFile.h"
#include "CPU.h"
#include "Decoder.h"

std::string instrTypeToString(InstrType type){
    switch (type) {
        case InstrType::R: return "R";
        case InstrType::I: return "I";
        case InstrType::S: return "S";
        case InstrType::B: return "B";
        case InstrType::U: return "U";
        case InstrType::J: return "J";
        case InstrType::SYSTEM: return "SYSTEM";
        default: return "UNKNOWN";
    }
}


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
        std::cout << "----------------------------------------" << std::endl;
    }

    Decoder decoder;
    for (uint32_t i = 0; i < memory.instructionCount(); ++i) {
        uint32_t instruction = memory.fetchInstruction(i*4);
        Instruction decoded = decoder.decode(instruction);
        std::cout << "Decoded instruction at address " << i << ": " << std::hex << decoded.raw << std::endl;
        std::cout << "  Type: " << instrTypeToString(decoded.type) << std::endl;
        std::cout << "  Opcode: " << std::hex << decoded.opcode << std::endl;
        std::cout << "  rd: " << std::dec << decoded.rd << std::endl;
        std::cout << "  rs1: " << std::dec << decoded.rs1 << std::endl;
        std::cout << "  rs2: " << std::dec << decoded.rs2 << std::endl;
        std::cout << "  funct3: " << std::hex << decoded.funct3 << std::endl;
        std::cout << "  funct7: " << std::hex << decoded.funct7 << std::endl;
        std::cout << "  imm: " << std::dec << decoded.imm << std::endl;
        std::cout << "----------------------------------------" << std::endl;
    }

    return 0;
}