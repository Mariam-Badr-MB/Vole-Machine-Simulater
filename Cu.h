
#ifndef CU_H
#define CU_H
#include "Memory.h"
#include "Register.h"


class Cu :public Register,public Memory{
public:
    void load(int Reg, int Mem, Register& reg, Memory& mem) {
      int value= mem.getcell(mem);
        reg.setcell(reg,value);
    }
    void load( int idxReg ,int val, Register&reg) {
        reg.setcell(idxReg,val);
    }
  void store( int idxReg, int idxMem, Register& reg, Memory& mem) {
        int value= reg.getcell(idxReg);
        string val = dec_hex(value);
        mem.setcell(idxMem,val);
    }
 void move(int idxReg1 , int idxReg2, Register&reg){
      int value= reg.getcell(idxReg1);
     reg.setcell(idxReg2,value);
 }
 void jump( int idxReg, int idxMem, Register&reg,int& PC){
if(reg[idxReg] ==reg[0]){
    PC =idxMem;
    
}
};
void halt() {
    exit(0);
}



#endif //CU_H
