#include "Machine Simulator.h"
vector<int>screen;
// Definitions for Memory class
const string& Memory::getcell(int m) const {
    if (m < 0 || m >= memSize) throw out_of_range("Memory access out of bounds");
    return data_M[m];
}
void Memory::setcell(int m, string d) {
    if (m < 0 || m >= memSize) throw out_of_range("Memory access out of bounds");
    data_M[m] = d;
}

// Definitions for Register class
int Register::getcell(int r) { return data_R[r]; }
void Register::setcell(int r, int d) { data_R[r] = d; }

void show(Register &reg ,Memory &memory) {
    cout <<"\n";
    for (int i = 0; i < screen.size(); i++) {
        cout << screen[i] << " ";
        if ((i + 1) % 16 == 0) cout << endl;
    }
    cout << endl;
    cout << "Registers:" << endl << endl;
    for (int i = 0; i < regSize; i++) {
        cout << "R" << i << ": " << reg.getcell(i) << " ";
        if ((i + 1) % 16 == 0) cout << endl;
    }
    cout << endl;

    cout << "Memory :" << endl << endl;
    for (int i = 0; i < memSize; i++) {
        cout << "M" << i << ": " <<memory.getcell(i) << " ";
        if ((i + 1) % 16 == 0) cout << endl;
    }
    cout << endl;}
// Definitions for ALU
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
    unordered_map<char, int> hexMap = {
        {'0', 0}, {'1', 1}, {'2', 2}, {'3', 3}, {'4', 4}, {'5', 5}, {'6', 6},
        {'7', 7}, {'8', 8}, {'9', 9}, {'A', 10}, {'B', 11}, {'C', 12},
        {'D', 13}, {'E', 14}, {'F', 15}
    };
    int decimal_value = 0;
    int power = hex_number.length() - 1;
    for (char digit : hex_number) {
        decimal_value += hexMap[toupper(digit)] * pow(16, power);
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

    return hex_number.empty() ? "0" : hex_number;
}
void ALU::bitWise_OR(int idx1, int idx2, int idx3, Register &reg){
    string S = dec_bin(reg.getcell(idx2)) ;
    string T = dec_bin(reg.getcell(idx3)) ;

    string result ;
   for(int i = 0 ; i < 8 ; i++){

       if(S[i] == '0' && T[i] == '0'){
         result += '0';
       }else{
        result += '1';
       }
   }
    int res = bin_dec(result);
    reg.setcell(idx1 , res);

}
void ALU::bitWise_AND(int idx1, int idx2, int idx3, Register &reg){
    string S = dec_bin(reg.getcell(idx2)) ;
    string T = dec_bin(reg.getcell(idx3)) ;

   string result ;
   for(int i = 0 ; i < 8 ; i++){

       if(S[i] == '1' && T[i] == '1'){
         result += '1';
       }else{
        result += '0';
       }
   }
   int res = bin_dec(result);
   reg.setcell(idx1 , res);

}
void ALU::bitWise_XOR(int idx1, int idx2, int idx3, Register &reg){
    string S = dec_bin(reg.getcell(idx2)) ;
    string T = dec_bin(reg.getcell(idx3)) ;

    string result ;
   for(int i = 0 ; i < 8 ; i++){

       if(S[i] == T[i]){
         result += '0';
       }else{
        result += '1';
       }
   }
    int res = bin_dec(result);
    reg.setcell(idx1 , res);

}
void ALU::add_Two_complement(int idx1, int idx2, int idx3, Register &reg) {
    const int bits = 8;

    int mask = (1 << bits) - 1;

    int result = (reg.getcell(idx2) + reg.getcell(idx3)) & mask;

    if (result & (1 << (bits - 1))) {
        result -= (1 << bits);
    }
    reg.setcell(idx1, result);

}
void ALU::add_Floating_point(int idx1, int idx2, int idx3, Register &reg) {

    string binRep1 = dec_bin(reg.getcell(idx2));
    string binRep2 = dec_bin(reg.getcell(idx3));

    int sign1 = binRep1[0] - '0';
    int sign2 = binRep2[0] - '0';


    int ex1 = bin_frac_dec(binRep1.substr(1, 3));
    int ex2 = bin_frac_dec(binRep2.substr(1, 3));


    double M1 = bin_frac_dec("0." + binRep1.substr(4));
    double M2 = bin_frac_dec("0." + binRep2.substr(4));


    double num1 = pow(-1, sign1) * M1 * pow(2, ex1 - 4);
    double num2 = pow(-1, sign2) * M2 * pow(2, ex2 - 4);


    double result = num1 + num2;
    int intPart = static_cast<int>(result);


    if (result >= 1 || result <= -1) {
        string exBin = decBin(intPart);
        string exponent = decBin(exBin.size() + 4);

        while (exponent.size() < 3) exponent.insert(0, "0");

        string mantissa = exBin + dec_frac_bin(result - intPart);
        while (mantissa.size() < 4) mantissa += "0";

        string binaryResult = (result < 0 ? '1' : '0') + exponent + mantissa;
        reg.setcell(idx1, bin_dec(binaryResult));
            cout <<  bin_dec(binaryResult) << endl ;

    } else {
        string mantissa = dec_frac_bin(fabs(result));
        while (mantissa.size() < 4) mantissa += "0";
        string ex = decBin(0 + 4);
        string binaryResult = (result < 0 ? '1' : '0') + ex + mantissa;
        reg.setcell(idx1, bin_dec(binaryResult));
    }
}

// Definitions for  CU classes
string CU::hex_binary(int R_idx, Register r) {
    map<char, string> hex_binary_ = {
        {'0', "0000"}, {'1', "0001"}, {'2', "0010"}, {'3', "0011"},
        {'4', "0100"}, {'5', "0101"}, {'6', "0110"}, {'7', "0111"},
        {'8', "1000"}, {'9', "1001"}, {'A', "1010"}, {'B', "1011"},
        {'C', "1100"}, {'D', "1101"}, {'E', "1110"}, {'F', "1111"}
    };

    int hexValue = r.getcell(R_idx);
    stringstream ss;
    ss << uppercase << hex << hexValue;
    string hexStr = ss.str();

    string binary;
    for (char ch : hexStr) {
        binary += hex_binary_[ch];
    }

    return binary;
}
string CU::comp_2(string s){
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

void CU::Rotate_Right(int R_idx, int turns, Register& r)
{
        int dec = r.getcell(R_idx);
        string bin = dec_bin(dec);
        string new_bin = "";
        while(bin.size() < 8){
            bin = '0' + bin;
        }
        turns = turns%8;
        new_bin += bin.substr(8-turns);
        new_bin += bin.substr(0, 8-turns);
        int dec2 = bin_dec(new_bin);
        r.setcell(R_idx, dec2);




}

void CU::load(int Reg, int Mem, Register& reg, Memory& mem) {
        int value = hex_dec(mem.getcell(Mem));
        reg.setcell(Reg, value);
    }
void CU::load(int idxReg, int val, Register& reg) {
        reg.setcell(idxReg, val);
    }
void CU::store(int idxReg, int idxMem, Register& reg, Memory& mem) {

        int value = reg.getcell(idxReg);
        string val = dec_hex(value);

        mem.setcell(idxMem, val);
    }
void CU::move(int r1, int r2, Register& reg) {
        int value = reg.getcell(r2);
        reg.setcell(r1, value);

    }
void CU::halt() {
        cout << "*** Thanks For Using This Machine Simulator ***" << endl;
        exit(0);
    }
int CPU::PC = 10;

// Definitions for CPU class
CPU::CPU(Memory& mem, Register& reg) : memory(mem), reg(reg) {}

 void CPU::fetch() {
        IR.clear();
        IR = memory.getcell(PC) + memory.getcell(PC + 1);
        cout << "IR =  " << IR << endl;
        cout << "PC =  " << PC << endl ;
    }

void CPU::comparison( Register r, int R_idx,int XY) {
    int jump_idx = PC;
    bool jump = false;
    int dec1 = r.getcell(R_idx);
    int dec2 = r.getcell(0);
    string bin1 = decBin(dec1);
    string bin2 = decBin(dec2);

    while(bin1.size()<8)
    {
        bin1 = '0' + bin1;
    }
    while(bin2.size()<8)
    {
        bin2 = '0' + bin2;
    }

    string bin1_2sComp = cu.comp_2(bin1);
    string bin2_2sComp = cu.comp_2(bin2);

    if((bin1_2sComp[0] == '1') && (bin2_2sComp[0] == '0')){

    }else if((bin1_2sComp[0] == '0') && (bin2_2sComp[0] == '1'))
        PC = XY, PC -= 2, jump = true;

    else{
        if((bin1_2sComp[0] == '0') && (bin2_2sComp[0] == '0')){
            for(int j=0; j<8; j++){
                if(bin1_2sComp[j]>bin2_2sComp[j]){
                    PC = XY, PC -= 2, jump = true;
                    break;
                }
            }
        }else if((bin1_2sComp[0] == '1') && (bin2_2sComp[0] == '1')){
            for(int j=0; j<8; j++){
                if(bin1_2sComp[j]<bin2_2sComp[j]){
                    PC = XY, PC -= 2, jump = true;
                    break;

                }
            }
        }
    }
    
    if(jump){
        int iterations = ((jump_idx+2 - XY)/2) + 1;
        for (int i=0; i<iterations; i++){
            runNextStep();
        }
    }
}
void CPU::jump(int R, int XY, Register& reg, int& PC) {
    if(reg.getcell(R)==reg.getcell(0)) {
        int jump_idx=PC;
        PC = XY;
        int iterations = ((jump_idx- XY)/2) + 1;
        for (int i=0; i<iterations; i++){
            runNextStep();
        }
    }
}

void CPU::decode() {

        int opcode = alu.hex_dec(IR.substr(0, 1));
        int R = alu.hex_dec(IR.substr(1, 1));
        int XY = (opcode == 4 || opcode == 5 || opcode == 6)
        ? alu.hex_dec(IR.substr(2, 1)) * 10 + alu.hex_dec(IR.substr(3, 1)) : alu.hex_dec(IR.substr(2, 2));

        if(opcode == 10)
            val = IR[3];
        execute(opcode, R, XY);
    }
void CPU::execute(int opcode, int R, int XY) {

        switch (opcode) {
            case 1: cu.load(R, XY, reg, memory); break;
            case 2: cu.load(R, XY, reg); break;
            case 3:
                if (XY == 00) screen.push_back(reg.getcell(R));
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
            case 7:
                alu.bitWise_OR(R, XY % 10, (XY / 10) % 10, reg);
                break;
            case 8:
                alu.bitWise_AND(R, XY % 10, (XY / 10) % 10, reg);
                break;
            case 9:
                alu.bitWise_XOR(R, XY % 10, (XY / 10) % 10, reg);
                break;
            case 10:
                cu.Rotate_Right(R, val, reg);
                break ;
            case 11:
                jump(R, XY, reg, PC);
                break;
            case 12: {
                show(reg, memory);   cu.halt(); break;
            }
            case 13:
                comparison( reg, R, XY); 
                break;
            default:
                cout << endl << "Invalid Instruction.\n Please, Try Again." << endl << endl ;
        }
    }
void CPU::runNextStep() {
        fetch();
        decode();
        PC += 2;
    }

// Definitions for Machine class
Machine::Machine() : cpu(memory, reg) {}
void Machine::loadProgramFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) throw runtime_error("Unable to open file");
    static int address = 10;
    string instruction;
    while (file >> instruction && address < memSize) {
        memory.setcell(address++, instruction.substr(0, 2));
        memory.setcell(address++, instruction.substr(2, 2));
        cpu.runNextStep();
    }
    file.close();
}
void Machine::loadProgramIns(const string& instructions) {
    stringstream ss(instructions);
    string instruction;
    static int address = 10;
    while (ss >> instruction && address < memSize) {
        memory.setcell(address, instruction.substr(0, 2));
        address++;
        memory.setcell(address, instruction.substr(2, 2));
        address++;
        cpu.runNextStep();
    }
}

// Definitions for MainUI class
MainUI::MainUI() : enterFileOrInstructions(false) {}
void MainUI::DisplayMenu() {
    while (true) {
        cout << "\nA) Load File\nB) Add Instruction\nC) View Current State\nD) Exit\n";
        char choice;
        cout << "Please, enter your option: ";
        cin >> choice;
        choice = toupper(choice);
        switch (choice) {
            case 'A': inputFileName(); break;
            case 'B': inputInstruction(); break;
            case 'C': outputState(machine, cpu); break;
            case 'D': cout << "Program Ended \n *** Thanks For Using This Machine Simulator ***"; exit(0);
            default: cout << "Invalid Choice.\n";
        }
    }
}
void MainUI::inputFileName() {
    cout << "Please, enter your filename: ";
    string FileName;
    cin >> FileName;
    machine.loadProgramFile(FileName);
}
void MainUI::inputInstruction() {
    cout << "Please, enter your instructions: ";
    string Ins_str;
    cin.ignore();
    getline(cin, Ins_str);
    machine.loadProgramIns(Ins_str);
}

// Definitions for helper functions, dec_bin, bin_dec, etc.
string dec_frac_bin(double num) {
    if (num == 0) return "0";
    string result = "";
    while (num > 0) {
        num *= 2;
        int bit = (int)num;
        result += to_string(bit);
        num -= bit;
    }
    return result;
}

double bin_frac_dec(const string& binary) {

    size_t point = binary.find('.');
    double dec = 0.0;
    if (point != string::npos) {
        for (size_t i = 0; i < point; ++i) {
            if (binary[i] == '1') dec += pow(2, point - i - 1);

        }

        for (size_t i = point + 1; i < binary.size(); ++i) {
            if (binary[i] == '1') dec += 1.0 / pow(2, i - point);
        }
    } else {
        for (size_t i = 0; i < binary.size(); ++i) {
            if (binary[i] == '1') {
                dec += pow(2, binary.size() - i - 1);
            }
        }
    }
    return dec;
}

string dec_bin(int decimal) {
    const int bits = 8 ;
    bitset<bits> binary(decimal);
    return binary.to_string();
}

int bin_dec(string& binary) {
    int decimal = 0;
    int length = binary.length();
    for (int i = 0; i < length; ++i) {
        if (binary[length - i - 1] == '1') {
            decimal += pow(2, i);
        }
    }
    return decimal;
}

string decBin(int decimal) {
    if (decimal == 0) return "0";

    string binary = "";
    while (decimal > 0) {
        binary = (decimal % 2 == 0 ? "0" : "1") + binary;
        decimal /= 2;
    }
    return binary;
}

void outputState(Machine& machine, CPU& cpu) {
    cout <<"\n";
    for (int i = 0; i < screen.size(); i++) {
        cout << screen[i] << " ";
        if ((i + 1) % 16 == 0) cout << endl;
    }
    cout << endl;
    cout << "Registers:" << endl << endl;
    for (int i = 0; i < regSize; i++) {
        cout << "R" << i << ": " << machine.reg.getcell(i) << " ";
        if ((i + 1) % 16 == 0) cout << endl;
    }
    cout << endl;

    cout << "Memory :" << endl << endl;
    for (int i = 0; i < memSize; i++) {
        cout << "M" << i << ": " << machine.memory.getcell(i) << " ";
        if ((i + 1) % 16 == 0) cout << endl;
    }
    cout << endl;
}