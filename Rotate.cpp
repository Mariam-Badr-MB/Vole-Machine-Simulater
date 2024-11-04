#include <bits/stdc++.h>
using namespace std;

string Rotate_Right(int R_idx, int turns, Register& r)
{
    string bin = hex_binary(R_idx, r);

    for(int i=0; i<turns; i++)
    {
        int temp1 = bin[7];
        bin[7] = bin[6];
        bin[6] = bin[5];
        bin[5] = bin[4];
        bin[4] = bin[3];
        bin[3] = bin[2];
        bin[2] = bin[1];
        bin[1] = bin[0];
        bin[0] = temp1;

    }
    string hexa = bin_hex(bin);
    return hexa;
}


