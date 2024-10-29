#include <bits/stdc++.h>
using namespace std;

#ifndef CPU_H
#define CPU_H

class CPU {
private:
    int PC;
    string IR;
public:
    CPU() : PC(0), IR("") {}
    Register reg;
    ALU alu;
    CU cu;

    void fetch(Memory& mem);
    void decode(const string& instruction, Memory& mem);
    void execute(int opcode, int R, int XY, Memory &mem, Register &reg);
    void runNextStep(Memory& mem, Register& reg);
};

void CPU::fetch(Memory& mem) {
    IR = mem.getcell(PC) + mem.getcell(PC + 1);
}

void CPU::decode(const string& instruction, Memory& mem) {
    int opcode = alu.hex_dec(instruction.substr(0, 1));
    int R = alu.hex_dec(instruction.substr(1, 1));
    int XY = alu.hex_dec(instruction.substr(2, 2));
    execute(opcode, R, XY, mem, reg);
}

void CPU::execute(int opcode, int R, int XY, Memory &mem, Register &reg) {
    switch (opcode) {
        case 1: cu.load(R, XY, reg, mem); break;
        case 2: cu.load(R, XY, reg); break;
        case 3: cu.store(R, XY, reg, mem); break;
        case 4: cu.move(R, XY, reg); break;
        case 5: alu.add_Two_complement(R, XY >> 4, XY & 0xF, reg); break;
        case 6: alu.add_Floating_point(R, XY >> 4, XY & 0xF, reg); break;
        case 11: cu.jump(R, XY, reg, PC); break;
        case 12: cu.halt(); break;
        default: cout << "Invalid instruction" << endl;
    }
}

void CPU::runNextStep(Memory &mem, Register &reg) {
    fetch(mem);
    decode(IR, mem);
    PC += 2;
}


