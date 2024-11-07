#include <bits/stdc++.h>
using namespace std;

int Rotate_Right(int R_idx, int turns, Register& r)
{
   int dec = r.getcell(R_idx);
    string bin = dec_bin(dec);

    if(bin.size() < 8){
        new_bin = "";
        for(int i=bin.size(); i<8;i++){
            new_bin += '0';
        }
        new_bin += bin;
    }
    else{
        strcpy(new_bin, bin);
    }
    for(int i=0; i<turns; i++)
    {
        int temp1 = new_bin[7];
        new_bin[7] = new_bin[6];
        new_bin[6] = new_bin[5];
        new_bin[5] = new_bin[4];
        new_bin[4] = new_bin[3];
        new_bin[3] = new_bin[2];
        new_bin[2] = new_bin[1];
        new_bin[1] = new_bin[0];
        new_bin[0] = temp1;

    }
    int dec2 = bin_dec(bin);
    return dec2;

}


