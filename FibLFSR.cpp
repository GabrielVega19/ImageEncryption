#include "FibLFSR.h"
#include <string>
#include <iostream>

using namespace std;

FibLFSR::FibLFSR(string seed){
    length = seed.length();
    data = new int[length];
    
    for (int i = 0; i < length; i++){
        data[i] = (seed[i] == '1') ? 1 : 0;
    }
}

int FibLFSR::step(){
    int bit = data[0] ^ data[2] ^ data[3] ^ data[5];

    for (int i = 0; i < length - 1; i++){
        data[i] = data[i + 1];
    } 
    data[length - 1] = bit;

    return data[length - 1]; 
}
int FibLFSR::generate(int k){
    int num = 0;
    
    for (int i = 0; i < k; i++){
        num *= 2;
        num += step();
    }

    return num;
}

FibLFSR::~FibLFSR(){
    delete[] data;
    data = nullptr;
}


ostream& operator<<(ostream& out, const FibLFSR& object){
    for (int i = 0; i < object.length; i++){
        out << object.data[i];
    }

    return out;
}