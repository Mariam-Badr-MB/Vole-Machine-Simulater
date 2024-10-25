#include <bits/stdc++.h>

using namespace std;

#ifndef MEMORY_H
#define MEMORY_H



class Memory {
protected:
    vector<string>data =vector<string>(256);
public:
    string  getcell(int m) {
        return data[m] ;
    }
    void setcell(int m,string d) {
        data[m]=d;
}
};



#endif //MEMORY_H
