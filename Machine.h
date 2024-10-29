#include <bits/stdc++.h>
using namespace std;

#ifndef MACHINE_H
#define MACHINE_H

const int REGISTER_SIZE = 8;
const int MEMORY_SIZE = 256;


class Machine {
public:
    CPU processor;
    Memory memory;

    void loadProgramFile(const string& filename);
    void outputState() const;
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
        memory.setCell(address++, instruction);
    }
    file.close();
}

void Machine::outputState() const {
    cout << "CPU State:" << endl;
    cout << "Program Counter: " << processor.programCounter << endl;
    
    for (int i = 0; i < REGISTER_SIZE; ++i) {
        cout << "R" << i << ": " << processor.reg.getCell(i) << endl;
    }
}
