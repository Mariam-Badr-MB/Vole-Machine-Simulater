#ifndef MACHINESIMULATOR_H
#define MACHINESIMULATOR_H

#include <bits/stdc++.h>
using namespace std;

const int regSize = 16;
const int memSize = 256;

string dec_frac_bin(double num);
double bin_frac_dec(const string& binary);
string dec_bin(int decimal);
int bin_dec(string& binary);
string decBin(int decimal);

class CPU ;
class Machine ;

class Memory {
protected:
    vector<string> data_M = vector<string>(memSize, "0");
public:
    const string& getcell(int m) const;
    void setcell(int m, string d);
};

class Register {
protected:
    vector<int> data_R = vector<int>(regSize, 0);
public:
    int getcell(int r);
    void setcell(int r, int d);
};

class ALU {
public:
    void add_Two_complement(int idx1, int idx2, int idx3, Register &reg);
    void add_Floating_point(int idx1, int idx2, int idx3, Register &reg);
    void bitWise_OR(int idx1, int idx2, int idx3, Register &reg);
    void bitWise_AND(int idx1, int idx2, int idx3, Register &reg);
    void bitWise_XOR(int idx1, int idx2, int idx3, Register &reg);

    int hex_dec(const string &hex_number);
    string dec_hex(int number);
    bool isValid(const string &hex_number);
    int bin_float_point(float &num);
};

class CU : public ALU {
public:
    void load(int Reg, int Mem, Register& reg, Memory& mem);
    void load(int idxReg, int val, Register& reg);
    void store(int idxReg, int idxMem, Register& reg, Memory& mem);
    void move(int r1, int r2, Register& reg);
    string hex_binary(int R_idx, Register r);
    string comp_2(string s);

    void Rotate_Right(int R, int turns, Register& reg);

    void halt();
};

class CPU {
protected:
    string IR = "";
    Memory& memory;
    Register& reg;
    ALU alu;
    CU cu;
    Machine* machine;
    int val;

public:
    static int PC;
    CPU(Memory& mem, Register& reg);



    void fetch();
    void decode();
    void execute(int opcode, int R, int XY);
    void runNextStep();
    void comparison(Register r,int R_idx,int XY);
    void jump(int R, int XY, Register& reg, int& PC);
    friend void outputState(Machine& machine, CPU& cpu);
};

class Machine{
public:
    Memory memory;
    Register reg;
    CPU cpu;
    ALU alu;

    Machine();
    void loadProgramFile(const string& filename);
    void loadProgramIns(const string& instructions);
    friend void outputState(Machine& machine, CPU& cpu);
};

class MainUI : public Machine{
protected:
    Machine machine;
    bool enterFileOrInstructions;

public:
    MainUI();
    void DisplayMenu();
    void getFileOrinstruction();
    void inputFileName();
    void inputInstruction();
};

void outputState(Machine& machine, CPU& cpu);
void show(Register &reg ,Memory &memory) ;
#endif