#include <bits/stdc++.h>
using namespace std;
int Rotate_Right(int R_idx, int turns, Register& r)
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
    return dec2;

}


