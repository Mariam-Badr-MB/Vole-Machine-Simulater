#include <bits/stdc++.h>

using namespace std;

#ifndef Alu_H
#define Alu_H

class Alu {

public:
    void add_Two_complement(int idx1, int idx2, int idx3, Register &reg);
    void add_Floating_point(int idx1, int idx2, int idx3, Register &reg);
    int hex_dec(const string &hex_number);
    string dec_hex(int number);
    bool isValid(const string &hex_number);
};

#endif //Alu_H

void Alu::add_Two_complement(int idx1, int idx2, int idx3, Register &reg) {
    reg.setcell(idx1, reg.getcell(idx2) + reg.getcell(idx3));
}
void Alu::add_Floating_point(int idx1, int idx2, int idx3, Register &reg) {
    float s = *reinterpret_cast<float*>(reg.getcell(idx2)); 
    float t = *reinterpret_cast<float*>(reg.getcell(idx3));
    
    float result = s + t ;
    reg.setcell(idx1, *reinterpret_cast<int*>(&result)); 
}

bool Alu::isValid(const string &hex_number) {
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
int Alu::hex_dec(const string &hex_number) {
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
string Alu::dec_hex(int number) {
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
