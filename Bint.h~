#ifndef _BINT_H
#define _BINT_H

#include <algorithm>
#include <iostream>

using namespace std;

// the first versoin only supports big integer add, subtraction, multiply

class BInt {
public:
    BInt(string num, bool negative);
    ~BInt();

    // overloading for +
    BInt operator+(const BInt &b);

    // overloading for -
    BInt operator-(const BInt &b);


    // overloading for *
    BInt operator*(const BInt &b);
    
    // overloading for <<
    ostream &operator<<(ostream &os, const BInt &num);

private:
    // inner sub and add without negative
    string innerSub(string a, string b);
    string innerAdd(string a, string b);


    // use strings to represent the two big numbers
    string num;
    bool negative;
};




#endif
