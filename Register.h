#include <bits/stdc++.h>
using namespace std;

#ifndef REGISTER_H
#define REGISTER_H



class Register{
    protected:
 vector<int>data =vector<int>(16,0);
    public:
int getcell(int r) {
    return data[r] ;
}
  void setcell(int r,int d) {
data[r]+=d;

    }

};



#endif //REGISTER_H
