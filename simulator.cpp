#include <bits/stdc++.h>
using namespace std;

const int REGISTER_SIZE = 16;
const int MEMORY_SIZE = 256;
class MainUI;
class Machine;
string dec_bin(int decimal) ;
string sub1(string& binary);
int bin_dec(string& binary);

class Memory {
protected:
    vector<string> data_M = vector<string>(MEMORY_SIZE, "0");
public:
    const string& getcell(int m) const {
        if (m < 0 || m >= MEMORY_SIZE) {
            throw out_of_range("Memory access out of bounds");
        }

        return data_M[m];
    }

    void setcell(int m, string d) {
        if (m < 0 || m >= MEMORY_SIZE) {
            throw out_of_range("Memory access out of bounds");
        }

        data_M[m] = d;
    }
};

class Register {
protected:
    vector<int> data_R = vector<int>(REGISTER_SIZE, 0);
public:
    int getcell(int r) {
        return data_R[r];
    }
    void setcell(int r, int d) {
        data_R[r] = d;
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
class CPU;
class CU : public ALU{
public:
    void load(int Reg, int Mem, Register& reg, Memory& mem) {
        int value = hex_dec(mem.getcell(Mem));
        reg.setcell(Reg, value);
    }
    void load(int idxReg, int val, Register& reg) {
        reg.setcell(idxReg, val);
    }
    void store(int idxReg, int idxMem, Register& reg, Memory& mem) {
        int value = reg.getcell(idxReg);
        string val = dec_hex(value);
        mem.setcell(idxMem, val);
    }
    void move(int r1, int r2, Register& reg) {
        int value = reg.getcell(r2);
        reg.setcell(r1, value);

    }
    void jump(int R, int XY, Register& reg, int& PC) {
        if(reg.getcell(R)==reg.getcell(0)) {
            PC = XY;
            PC-=2;

        }
    }

    string hex_binary(int R_idx, Register r)
    {
        map<char,string> hex_binary_;
        hex_binary_['0'] = "0000";
        hex_binary_['1'] = "0001";
        hex_binary_['2'] = "0010";
        hex_binary_['3'] = "0011";
        hex_binary_['4'] = "0100";
        hex_binary_['5'] = "0101";
        hex_binary_['6'] = "0110";
        hex_binary_['7'] = "0111";
        hex_binary_['8'] = "1000";
        hex_binary_['9'] = "1001";
        hex_binary_['A'] = "1010";
        hex_binary_['B'] = "1011";
        hex_binary_['C'] = "1100";
        hex_binary_['D'] = "1101";
        hex_binary_['E'] = "1110";
        hex_binary_['F'] = "1111";

        int hex = r.getcell(R_idx);
        string hex_ = to_string(hex);
        string binary;
        binary += hex_binary_[hex_[0]];
        binary += hex_binary_[hex_[1]];

        return binary;
    }

    string comp_2(string s)
    {
        for(int j=0; j<s.size(); j++)
        {
            if(s[j] == '0')
                s[j] = '1';
            else if(s[j] == '1')
                s[j] = '0';
        }

        if (s[s.size()-1] == '0')
            s[s.size()-1] = '1';
        else
        {
            for(int k= s.size()-1; k>-1; k--)
            {
                if(s[k] == '1')
                    s[k] = '0';
                else
                {
                    s[k] = '1';
                    break;
                }
            }
        }
        return s;
    }

    bool comparison(int R_idx, Register r)
    {
        string bin1 = hex_binary(R_idx, r);
        string bin2 = hex_binary(0, r);

        string bin1_2sComp = comp_2(bin1);
        string bin2_2sComp = comp_2(bin2);

        if((bin1_2sComp[0] == '1') && (bin2_2sComp[0] == '0'))
            return false;

        else if((bin1_2sComp[0] == '0') && (bin2_2sComp[0] == '1'))
            return true;

        else
        {
            if (bin1_2sComp > bin2_2sComp)
                return true;
            else if (bin1_2sComp < bin2_2sComp)
                return false;
            else
                cout<<"Registers are Equal.\n";
        }
    }

    void jump2 (CPU* cpu, Register r,int R_idx, int mem_idx);

    void Rotate_Right(int R_idx, int turns, Register& r)
    {
        int reg = r.getcell(R_idx);
        string reg_ = dec_hex(reg);
        for (int j=0; j<turns; j++)
        {
            char temp = reg_[0];
            reg_[0]= reg_[1]; reg_[1] = temp;
        }
    }

    void halt() {
     //  outputstate();
        cout << "* Thanks For Using This Machine Simulator *" << endl;
        exit(0);
    }
};

void ALU::add_Two_complement(int idx1, int idx2, int idx3, Register &reg) {

     string S = dec_bin(reg.getcell(idx2)) ;
     string T = dec_bin(reg.getcell(idx3)) ;
     string s = sub1(S);
     string t = sub1(T);

    for(int i = 0 ; i < s.size() ; i++){
        if(s[i] == '0') s[i] = '1';
        else s[i] = '0';
     }
    for(int i = 0 ; i < t.size() ; i++){
        if(t[i] == '0') t[i] = '1';
        else t[i] = '0';
     }
     int id1 = bin_dec(s);
     if(S[0] == '1') id1 *= -1 ;
     int id2 = bin_dec(t);
     if(T[0] == '1') id2 *= -1 ;


    int res = id1 + id2 ;
    reg.setcell(idx1, res);
}

void ALU::add_Floating_point(int idx1, int idx2, int idx3, Register &reg) {
    float s = *reinterpret_cast<float*>(reg.getcell(idx2));
    float t = *reinterpret_cast<float*>(reg.getcell(idx3));
    float result = s + t;
    reg.setcell(idx1, *reinterpret_cast<int*>(&result));
}

bool ALU::isValid(const string &hex_number) {
    for (char digit : hex_number) {
        if (!isxdigit(digit)) return false;
    }
    return true;
}

int ALU::hex_dec(const string &hex_number) {
    int decimal_value;
    stringstream ss;
    ss << hex << hex_number;
    ss >> decimal_value;
    return decimal_value;
}

string ALU::dec_hex(int number) {
    stringstream ss;
    ss << hex << uppercase << number;
    return ss.str();
}
string dec_bin(int decimal) {
    if (decimal == 0) return "0";

    string binary = "";
    while (decimal > 0) {
        binary = to_string(decimal % 2) + binary;
        decimal /= 2;
    }

    return binary;
}
string sub1( string& binary) {
    string result = binary;
    int len = result.length();

    for (int i = len - 1; i >= 0; --i) {
        if (result[i] == '1') {
            result[i] = '0';
            break;
        } else {
            result[i] = '1';
        }
    }

    int firstOnePos = result.find('1');
    if (firstOnePos != string::npos) {
        result = result.substr(firstOnePos);
    } else {
        result = "0";
    }

    return result;
}

int bin_dec(string& binary) {
    int decimal = 0;
    int power = 0;

    for (int i = binary.length() - 1; i >= 0; --i) {
        if (binary[i] == '1') {
            decimal += std::pow(2, power);
        }
        power++;
    }

    return decimal;
}

class CPU {
protected:
    string IR = "";
    Memory& memory;
    Register& reg;
    ALU alu;
    CU cu;
    Machine* machine;

public:
    static int PC;
    CPU(Memory& mem, Register& reg) : memory(mem), reg(reg) {}
    friend void outputState(Machine& machine, CPU& cpu);

    void fetch() {
        IR.clear();
        IR = memory.getcell(PC) + memory.getcell(PC + 1);
        cout << "IR: " << IR << endl;
    }

    void decode() {
        int opcode = alu.hex_dec(IR.substr(0, 1));
        int R = alu.hex_dec(IR.substr(1, 1));
        int XY = (opcode == 4 || opcode == 5 || opcode == 6)
                 ? alu.hex_dec(IR.substr(2, 1)) * 10 + alu.hex_dec(IR.substr(3, 1))
                 : alu.hex_dec(IR.substr(2, 2));
        int val;
        if(opcode == 10)
            val = IR[3];

        execute(opcode, R, XY, val);
    }

    void execute(int opcode, int R, int XY, int val) {
        switch (opcode) {
            case 1: cu.load(R, XY, reg, memory); break;
            case 2: cu.load(R, XY, reg); break;
            case 3:
                if (XY == 0) cout << reg.getcell(R) << "\n";
                cu.store(R, XY, reg, memory);
                break;
            case 4:
                cu.move(XY % 10, XY / 10, reg);
                break;
            case 5:
                alu.add_Two_complement(R, XY % 10, (XY / 10) % 10, reg);
                break;
            case 6:
                alu.add_Floating_point(R, XY % 10, (XY / 10) % 10, reg);
                break;
            case 10:
                cu.Rotate_Right(R, val, reg);
            case 11:
                cu.jump(R, XY, reg, PC);
                break;
            case 12:
                outputState(*this->machine, *this);
                cu.halt();
                break;
            case 13:
                CPU* point;
                cu.jump2(point, reg, R, XY);
            default:
                cout << "Invalid instruction" << endl;
        }
    }


    void runNextStep() {
        fetch();
        decode();
        PC += 2;
    }
};

int CPU::PC = 10;

void CU :: jump2 (CPU* cpu, Register r,int R_idx, int mem_idx)
{
    if(comparison(R_idx, r))
        cpu->PC = mem_idx;
}

class Machine {
public:
    Memory memory;
    Register reg;
    CPU cpu;
    ALU alu;

    Machine() : cpu(memory, reg) {}

    void loadProgramFile(const string& filename);
    void loadProgramIns(const string& instructions);
    friend void outputState(Machine& machine, CPU& cpu);
};

void outputState(Machine &machine , CPU &cpu) {

    cout << "Registers:" << endl << endl ;
    for (int i = 0; i < REGISTER_SIZE; i++) {
        cout << "R" << i << ": " << machine.reg.getcell(i) << " ";
        if ((i + 1) % 16 == 0) {
            cout << endl;
        }
    }
    cout << endl;

    cout << "Memory :" << endl << endl ;
    for (int i = 0; i < MEMORY_SIZE; i++) {
        cout << "M" << i << ": " << machine.memory.getcell(i) << " ";
        if ((i + 1) % 16 == 0) {
            cout << endl;
        }
    }
    cout << endl;
}

void Machine::loadProgramFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Unable to open file");
    }

    static int address = 10;
    string instruction;
    while (file >> instruction && address < MEMORY_SIZE) {
        // string check =instruction.substr(2,instruction.size());
        // if(alu.hex_dec(check)>256 || alu.hex_dec(check)<0)
        //     cout<<"Invalid Instruction"<<"\n";
        memory.setcell(address++, instruction.substr(0,2));

        memory.setcell(address++, instruction.substr(2,2));
        cout<<"second"<<memory.getcell(address)<<"\n";
       cpu.runNextStep();

    }
    file.close();

}

void Machine::loadProgramIns(const string& instructions)
{

    stringstream ss(instructions);
       // string check =instructions.substr(2,instructions.size());
       //  if(alu.hex_dec(check)>256 || alu.hex_dec(check)<0) {
       //      cout<<"Invalid Instruction"<<"\n";
       //     void MainUI::DisplayMenu();
       //
       //  }
    string instruction;
   static int address = 10;
    while (ss >> instruction && address < MEMORY_SIZE) {

        memory.setcell(address, instruction.substr(0,2));

        address++;
        memory.setcell(address,instruction.substr(2,2));
        address++;
        cpu.runNextStep();
    }
}

class MainUI : public Machine{
protected:
    Machine machine;
    bool enterFileOrInstructions;

public:
    MainUI() : enterFileOrInstructions(false) {}

    void DisplayMenu() {
        while (true) {
            cout << "\nA) Load File\nB) Add Instruction\nC)View Current State\nD) Exit\n";
            char choice;
            cout << "Choose an option: ";
            cin >> choice;
            choice = toupper(choice);
            switch (choice) {
            case 'A':
                inputFileName();
                break;
            case 'B':
                inputInstruction();
                break;
            case 'C':
                outputState(machine , cpu);
                break;
            case 'D':
                cout << "Program Ended\n";
                exit(0);
            default:
                cout << "Invalid Choice.\n";
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
        cout<<"enter File Name: ";
        string FileName;
        cin>>FileName;
        machine.loadProgramFile(FileName);
    }

    void inputInstruction()
    {
        cout<<"Please, enter Instructions spaced: ";
        string Ins_str;
        cin.ignore();
        getline (cin, Ins_str);

        machine.loadProgramIns(Ins_str);

    }

};

int main() {
    cout << "* Vole Machine Simulator *" << endl;
    MainUI ui;
    ui.DisplayMenu();
    return 0;
}