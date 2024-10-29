#include <bits/stdc++.h>
using namespace std;

#ifndef CPU_H
#define CPU_H

class CPU {
public:
    int programCounter = 0;
    string instructionRegister;
    Register reg;
    ALU alu;
    CU cu;

    void runNextStep(Memory& mem);
    
private:
    string fetch(Memory& mem);
    void decode(const string& instruction, Memory& mem);
};

#endif // CPU_H

void CPU::runNextStep(Memory& mem) {
    instructionRegister = fetch(mem);
    decode(instructionRegister, mem);
}

string CPU::fetch(Memory& mem) {
    return mem.getCell(programCounter++);
}

void CPU::decode(const string& instruction, Memory& mem) {
    int opcode = instruction[0] - '0';
    int R = instruction[1] - '0';
    int XY = stoi(instruction.substr(2, 2), nullptr, 16);

    switch (opcode) {
        case 1:
            cu.load(R, XY, reg, mem);
            break;
        case 2:
            cu.load(R, XY, reg);
            break;
        case 3:
            cu.store(R, XY, reg, mem);
            break;
        case 4:
            cu.move(R, XY, reg);
            break;
        case 5:
            alu.add(R, instruction[2] - '0', instruction[3] - '0', reg);
            break;
        case 'B' - '0':
            cu.jump(R, XY, reg, programCounter);
            break;
        case 'C' - '0':
            cu.halt();
            break;
        default:
            cout << "Invalid instruction" << endl;
    }
}
