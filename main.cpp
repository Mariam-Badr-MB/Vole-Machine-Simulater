#include<bits/stdc++.h>
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
    vector <string> re_data()
    {
        return data;
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

class CU {
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
    float s = reinterpret_cast<float>(reg.getcell(idx2));
    float t = reinterpret_cast<float>(reg.getcell(idx3));
    float result = s + t;
    reg.setcell(idx1, reinterpret_cast<int>(&result));
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



class CPU
{
protected:
    int PC;
    string IR;

public:
    Memory mem;
    Register reg;
    ALU alu;
    CU cu;

    CPU()
    {
        PC = 0;
        IR = "";
    }
    void fetch()
    {
        vector<string> data = mem.re_data();
        if(PC < mem.re_data().size())
        {
            IR += mem.getcell(PC);
            IR += mem.getcell(PC+1);
        }
    }

    vector<int> decode()
    {

        int op_code = alu.hex_dec(string(1,IR[0]));
        int reg = alu.hex_dec(string(1,IR[1]));
        int mem = alu.hex_dec(IR.substr(2));
        int val = alu.hex_dec(IR.substr(2));
        int reg1 = alu.hex_dec(string(1,IR[2]));
        int reg2 = alu.hex_dec(string(1,IR[3]));

        vector <int> decoded = {op_code, reg, mem, val, reg1, reg2};
        return decoded;
    }

    void execute(vector<int> &v)
    {
            if(v[0]== 1)
                cu.load(v[1], v[2], reg, mem);

            else if(v[0] == 2)
                cu.load(v[1], v[3],reg);

            else if(v[0] == 3)
                cu.store(v[1], v[2],reg,mem);

            else if(v[0] == 4)
                cu.move(v[4], v[5],reg);

            else if(v[0]== 11)
                cu.jump(v[1], v[2], reg, PC);

            else if(v[0] == 12)
                cu.halt();
    }

    void runNextStep()
    {
        fetch();
        vector <int> decoded = decode();
        execute(decoded);
        PC += 2;
    }

};

#ifndef MACHINE_H
#define MACHINE_H

const int REGISTER_SIZE = 8;
const int MEMORY_SIZE = 256;


class Machine : public CPU {
public:
    Memory memory;

    void loadProgramFile(const string& filename);
    void loadProgramIns(const string& instructions);
    void outputState();
};

#endif // MACHINE_H

void Machine::loadProgramFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Unable to open file");
    }

    int address = 0;
    string instruction;
    while (file >> instruction && address < MEMORY_SIZE) {
        memory.setcell(address++, instruction.substr(1));
        memory.setcell(address++, instruction.substr(2,2));
    }
    file.close();
}

void Machine::loadProgramIns(const string& instructions)
{
    stringstream(instructions);
    string instruction;
    int address = 0;
    while (instructions >> instruction && address < MEMORY_SIZE) {
        memory.setcell(address++, instruction.substr(1));
        memory.setcell(address++, instruction.substr(2,2));
    }
}

void Machine::outputState (){
    cout << "CPU State:" << endl;
    cout << "Program Counter: " << PC << endl;

    for (int i = 0; i < REGISTER_SIZE; ++i) {
        cout << "R" << i << ": " << reg.getcell(i) << endl;
    }
}
class MainUI
{
protected:
    Machine machine;
    bool enterFileOrInstructions;
public:
    MainUI()
    {
        enterFileOrInstructions = false;
    }
    void DisplayMenu()
    {
        while(true){
            cout<<"** Vole Machine Simulator **\nChoose the needed order:\n";
            cout<<"A) Load Program\nB) Add Instruction(option for manually program loading)\nC) Execute Program\nD) View Current State\nE) Exit\n:";
            char choice;
            cin>>choice;
            choice = toupper(choice);

            switch(choice)
            {
            case 'A':
                cout<<"How would you enter the instructions?a) In File\nb) One by One\n:";
                char tech;
                cin>>tech;
                if(tech == 'a')
                    enterFileOrInstructions = true;
                getFileOrinstruction();

            case 'B':
                inputInstruction();
                break;
            case 'C':
                machine.runNextStep();
                break;
            case 'D':
                machine.outputState();
                break;
            case 'E':
                cout<<"Program is Ended\n";
                exit(1);
                break;
            default:
                cout<<"Please Enter a Correct Choice\n";
                break;
            }
        }
    }

        void getFileOrinstruction()
    {
        if(enterFileOrInstructions)
            inputFileName();
        else
            inputInstruction();
    }

        void inputFileName()
    {
        cout<<"Enter File Name: ";
        string FileName;
        cin>>FileName;
        machine.loadProgramFile(FileName);
    }

        void inputInstruction()
    {
        cout<<"Enter Instructions spaced: ";
        string Ins_str;
        getline (cin, Ins_str);
        machine.loadProgramIns(Ins_str);
    }
};