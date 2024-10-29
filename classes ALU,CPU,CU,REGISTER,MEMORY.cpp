#include <bits/stdc++.h>
using namespace std;

class Memory {
protected:
    vector<string> data = vector<string>(256);
public:
    string getcell(int m) {
        return data[m];
    }
    void setcell(int m, string d) {
        data[m] = d;
    }
};

class Register {
protected:
    vector<int> data = vector<int>(16, 0);
public:
    int getcell(int r) {
        return data[r];
    }
    void setcell(int r, int d) {
        data[r] = d;
    }
};

class CU : public Register, Memory {
public:
    void load(int Reg, int Mem, Register& reg, Memory& mem) {
        int value = stoi(mem.getcell(Mem));
        reg.setcell(Reg, value);
    }
    void load(int idxReg, int val, Register& reg) {
        reg.setcell(idxReg, val);
    }
    void store(int idxReg, int idxMem, Register& reg, Memory& mem) {
        int value = reg.getcell(idxReg);
        mem.setcell(idxMem, to_string(value));
    }
    void move(int Reg, int Mem, Register& reg) {
        reg.setcell(Reg, reg.getcell(Mem));
    }
    void jump(int R, int XY, Register& reg, int& PC) {
        PC = reg.getcell(R) + XY;
    }
    void halt() {
        cout << "******************* Thanks For Using This Machine Simulator *******************" << endl;
    }
};

class ALU {
public:
    void add_Two_complement(int idx1, int idx2, int idx3, Register &reg);
    void add_Floating_point(int idx1, int idx2, int idx3, Register &reg);
    int hex_dec(const string &hex_number);
    string dec_hex(int number);
    bool isValid(const string &hex_number);
};

void ALU::add_Two_complement(int idx1, int idx2, int idx3, Register &reg) {
    reg.setcell(idx1, reg.getcell(idx2) + reg.getcell(idx3));
}

void ALU::add_Floating_point(int idx1, int idx2, int idx3, Register &reg) {
    float s = *reinterpret_cast<float*>(reg.getcell(idx2));
    float t = *reinterpret_cast<float*>(reg.getcell(idx3));
    float result = s + t;
    reg.setcell(idx1, *reinterpret_cast<int*>(&result));
}

bool ALU::isValid(const string &hex_number) {
    unordered_map<char, int> hexMap = {
        {'0', 0}, {'1', 1}, {'2', 2}, {'3', 3}, {'4', 4}, {'5', 5}, {'6', 6},
        {'7', 7}, {'8', 8}, {'9', 9}, {'A', 10}, {'B', 11}, {'C', 12},
        {'D', 13}, {'E', 14}, {'F', 15}
    };
    for (char digit : hex_number) {
        if (hexMap.find(toupper(digit)) == hexMap.end()) {
            return false;
        }
    }
    return true;
}

int ALU::hex_dec(const string &hex_number) {
    int decimal_value = 0;
    int power = hex_number.length() - 1;
    for (char digit : hex_number) {
        decimal_value += (digit <= '9' ? digit - '0' : toupper(digit) - 'A' + 10) * pow(16, power);
        --power;
    }
    return decimal_value;
}
string ALU::dec_hex(int number) {
    unordered_map<int, char> hexMap = {
        {0, '0'}, {1, '1'}, {2, '2'}, {3, '3'}, {4, '4'}, {5, '5'},
        {6, '6'}, {7, '7'}, {8, '8'}, {9, '9'}, {10, 'A'}, {11, 'B'},
        {12, 'C'}, {13, 'D'}, {14, 'E'}, {15, 'F'}
    };
   string hex_number = "";
    while (number > 0) {
        int digit = number % 16;
        hex_number = hexMap[digit] + hex_number;
        number /= 16;
    }

    return  hex_number;
}
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
