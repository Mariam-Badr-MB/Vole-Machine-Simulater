#include <bits/stdc++.h>

using namespace std;

#ifndef Alu_H
#define Alu_H

class Alu {
protected:
    unordered_map<char, int> hexMap = {
        {'0', 0}, {'1', 1}, {'2', 2}, {'3', 3}, {'4', 4}, {'5', 5}, {'6', 6},
        {'7', 7}, {'8', 8}, {'9', 9}, {'A', 10}, {'B', 11}, {'C', 12},
        {'D', 13}, {'E', 14}, {'F', 15}
    };


public:
    void add(int idx1, int idx2, int idx3, Register &reg);
    string hex_dec(const string &hex_number);
    string dec_hex(int number);
    bool isValid(const string &hex_number);
};

void Alu::add(int idx1, int idx2, int idx3, Register &reg) {
    reg.setCell(idx1, reg.getCell(idx2) + reg.getCell(idx3));
}

bool Alu::isValid(const string &hex_number) {
    for (char digit : hex_number) {
        if (hexMap.find(toupper(digit)) == hexMap.end()) {
            return false;
        }
    }
    return true;
}

string Alu::hex_dec(const string &hex_number) {
    int decimal_value = 0;
    int power = hex_number.length() - 1;
    for (char digit : hex_number) {
        decimal_value += hexMap[toupper(digit)] * pow(16, power);
        --power;
    }
    return to_string(decimal_value);
}

string Alu::dec_hex(int number) {
    if (number == 0) return "0";
    stringstream ss;
    ss << hex << uppercase << number;
    return ss.str();
}


#endif //Alu_H