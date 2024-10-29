#include <bits/stdc++.h>
using namespace std;

#ifndef CPU_H
#define CPU_H

class CPU {
private:
    string fetch(Memory& mem);
    void decode(const string& instruction, Memory& mem);

public:
    int PC = 0;
    string instructionRegister ;
    Register reg;
    ALU alu;
    CU cu;

    void runNextStep(Memory& mem);
    
};

#endif // CPU_H

void CPU::runNextStep(Memory& mem) {
    instructionRegister = fetch(mem);
    decode(instructionRegister, mem);
}

string CPU::fetch(Memory& mem) {
    return mem.getCell(PC++);
}

void CPU::decode(const string& instruction, Memory& mem) {
        int opcode = alu.hex_dec(instruction.substr(0, 1));    
        int R = alu.hex_dec(instruction.substr(1, 1));
        int XY = alu.hex_dec(instruction.substr(2, 2));

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
            cu.jump(R, XY, reg, PC);
            break;
        case 'C' - '0':
            cu.halt();
            break;
        default:
            cout << "Invalid instruction" << endl;
    }
}
