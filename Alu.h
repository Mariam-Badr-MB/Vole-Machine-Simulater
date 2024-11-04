
#include <bits/stdc++.h>

using namespace std;

const int REGISTER_SIZE = 16;
const int MEMORY_SIZE = 256;

float dec_float_point(string &num);
string dec_bin(int decimal) ;
string sub1(string& binary);
double bin_dec(string& binary);
string bin_hex(string& binaryStr);

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



class Alu {

public:
    void add_Two_complement(int idx1, int idx2, int idx3, Register &reg);
    void add_Floating_point(int idx1, int idx2, int idx3, Register &reg);
    int hex_dec(const string &hex_number);
    string dec_hex(int number);
    bool isValid(const string &hex_number);
    int bin_float_point(float &num);
};

void Alu::add_Two_complement(int idx1, int idx2, int idx3, Register &reg) {

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
void Alu::add_Floating_point(int idx1, int idx2, int idx3, Register &reg) {

      string S = dec_bin(reg.getcell(idx2)) ; 
      string T = dec_bin(reg.getcell(idx3)) ;
   
     float result = dec_float_point(T) + dec_float_point(T) ;
     int res =  bin_float_point(result);
     reg.setcell(idx1, res);    

}
int Alu:: bin_float_point(float &num){

     int sign = (num < 0 ? -1 : 1 ); 

     num = abs(num);

     int ex = num ;
     int Ex = dec_bin(ex).size() + 4 ;
     
     string M = dec_bin(ex) + (ex != num ? '1' : '0');
     string result = to_string(sign ) + dec_bin(Ex) + M ;
     
     result = bin_hex(result);
     int res = hex_dec(result);

    return res ;

}

float dec_float_point(string &num){

     int sign = num[0] - '0' ; string ex = num.substr(1, 4) ;
     int Ex = bin_dec(ex) - 4 ;
     int M = stoi(num.substr(4, 8));

     M /= 4;
     M *= (pow(Ex , 2)) ;
    string man = to_string(M) ;
    float result = (pow(-1,sign)) * bin_dec(man);
    return result ;

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
string bin_hex(string& binaryStr) {
    std::string hexStr = "";
    int len = binaryStr.length();

    // Pad the binary string with leading zeros if necessary
    int padding = (4 - (len % 4)) % 4; // Calculate padding needed
    std::string paddedBinaryStr = std::string(padding, '0') + binaryStr;

    // Process each group of 4 bits
    for (size_t i = 0; i < paddedBinaryStr.length(); i += 4) {
        std::string fourBits = paddedBinaryStr.substr(i, 4);
        int hexValue = 0;

        // Convert 4 bits to decimal
        for (size_t j = 0; j < fourBits.length(); ++j) {
            if (fourBits[j] == '1') {
                hexValue += (1 << (3 - j)); // 2^(3-j) for each bit
            }
        }

        // Convert decimal to hexadecimal character
        if (hexValue < 10) {
            hexStr += ('0' + hexValue); // '0' to '9'
        } else {
            hexStr += ('A' + (hexValue - 10)); // 'A' to 'F'
        }
    }

    return hexStr;
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
double bin_dec(string& binaryStr) {
    size_t pointPos = binaryStr.find('.');

    string integerPart = binaryStr.substr(0, pointPos);
    string fractionalPart = (pointPos != string::npos) ? binaryStr.substr(pointPos + 1) : "";

    double decimalValue = 0;
    int intLength = integerPart.length();
    for (int i = 0; i < intLength; ++i) {
        if (integerPart[i] == '1') {
            decimalValue += pow(2, intLength - i - 1);
        }
    }

    for (int i = 0; i < fractionalPart.length(); ++i) {
        if (fractionalPart[i] == '1') {
            decimalValue += pow(2, -(i + 1));
        }
    }

    return decimalValue;
}
