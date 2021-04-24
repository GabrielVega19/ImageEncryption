#ifndef FIBLFSR_H
#define FIBLFSR_H

#include <string>
#include <iostream>

using namespace std;

class FibLFSR {
public:
    FibLFSR(string seed); // constructor to create LFSR with the given initial seed and tap

    int step(); // simulate one step and return the new bit as 0 or 1   
    int generate(int k); // simulate k steps and return k-bit integer
    
    //helper functions for testing
    int getLength() const{
        return length;
    }
    int& operator[](int index){
        return data[index];
    }

    friend ostream& operator<<(ostream& out, const FibLFSR& object);

    ~FibLFSR();
private:
    int* data;
    int length;
};

ostream& operator<<(ostream& out, const FibLFSR& object);

#endif