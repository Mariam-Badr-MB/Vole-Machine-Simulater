#include <bits/stdc++.h>
using namespace std;

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

