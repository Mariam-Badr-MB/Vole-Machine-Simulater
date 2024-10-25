
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

};



#endif //CU_H
