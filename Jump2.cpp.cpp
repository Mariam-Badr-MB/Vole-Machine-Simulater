#include <bits/stdc++.h>
using namespace std;

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

void jump2 (CPU &cpu, Register r,int R_idx, int mem_idx)
{
    if(comparison(R_idx, r))
        cpu.PC = mem_idx;
}