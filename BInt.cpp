#include "BInt.h"
#include <iostream>
#include <algorithm>
using namespace std;

BInt::BInt(string num, bool neg) {
    this->num = num;
    this->negative = neg;
}

BInt::BInt(string num): negative(false) {
    this->num = num;
}

BInt BInt::operator+(const BInt &b) {
    BInt res("");
    // determine the negative
    if (this->negative == false && b.negative == false) {
        // + +
        res.negative = false;
        res.num = innerAdd(this->num, b.num);
    }
    else if (this->negative == true && b.negative == true) {
        // - -
        res.negative = true;
        res.num = innerAdd(this->num, b.num);
    }
    else if (this->negative == false && b.negative == true) {
        // + -    a - b, need to compare a and b to determine the negative
        if (this->num == b.num) {
            res.negative = false;
            res.num = "0";
        }
        else if (this->num < b.num) {
            res.negative = true;
            res.num = innerSub(b.num, this->num);
        }
        else {
            res.negative = false;
            res.num = innerSub(this->num, b.num); 
        }
    }
    else if (this->negative == true && b.negative == false) {
        // - +, b - a, compare a and b to determine the negative
        if (this->num == b.num) {
            res.negative = false;
            res.num = "0";
        }
        else if (b.num > this->num) {
            res.negative = false;
            res.num = innerSub(b.num, this->num);
        }
        else {
            res.negative = true;
            res.num = innerSub(this->num, b.num);
        }
    }

    return res;

}

BInt BInt::operator-(const BInt &b) {
    BInt res("");
    if (this->negative == false && b.negative == true) {
        // a - (-b)
        res.negative = false;
        res.num = innerAdd(this->num, b.num);
    }
    else if (this->negative == true && b.negative == false) {
        // -a - b
        res.negative = true;
        res.num = innerAdd(this->num, b.num);
    }
    else if (this->negative == false && b.negative == false) {
        // a - b, compare a and b
        if (this->num == b.num) {
            res.negative = false;
            res.num = "0";
        }
        else if (this->num > b.num) {
            res.negative = false;
            res.num = innerSub(this->num, b.num);
        }
        else {
            res.negative = true;
            res.num = innerSub(b.num, this->num);
        }
    }
    else if (this->negative == true && b.negative == true) {
        // b - a, compare b and a
        if (this->num == b.num) {
            res.negative = false;
            res.num = "0";
        }
        else if (b.num > this->num) {
            res.negative = false;
            res.num = innerSub(b.num, this->num);
        }
        else {
            res.negative = true;
            res.num = innerSub(this->num, b.num);
        }
    }
    return res;
}

BInt BInt::operator*(const BInt &b) {
    BInt res("");
    // determine the negative first
    res.negative = this->negative == b.negative ? false : true;

    // determine the value
    res.num = innerMul(this->num, b.num);

    return res;
}

ostream& operator<<(ostream &os, const BInt& b) {
    string res;
    if (b.negative == true) {
        res = "-";
    }
    res += b.num;
    os << res; 
    return os;
}

// inner sub without negative
string BInt::innerSub(string a, string b) {
    // for this function, must a > b, and a +, b -

    int m = a.size(), n = b.size();
    int len = max(m, n);
    int i = m - 1, j = n - 1, k = len - 1;
    int carry = 0, val = 0;
    string res(len, '0');

    while (i >= 0 || j >= 0) {
        int aVal = i >= 0 ? a[i] - '0' : 0;
        int bVal = j >= 0 ? b[j] - '0' : 0;

        if (aVal + carry >= bVal) {
            val = aVal - bVal + carry;
            carry = 0;
        }
        else {
            val = aVal + 10 + carry - bVal;
            carry = -1;
        }
        res[k--] = '0' + val;
        --i;
        --j;
    }

    // remove the leading zeros
    int t = 0;
    while (t < len && res[t] == '0') {
        t++;
    }

    return res.substr(t);
}

// inner add without negative
string BInt::innerAdd(string a, string b) {
    int m = a.size(), n = b.size();
    int len = max(m, n);
    int i = m - 1, j = n - 1, k = len - 1;
    int carry = 0, val = 0;
    string res(len, ' ');

    while (i >= 0 || j >= 0) {
        int aVal = i >= 0 ? a[i] - '0' : 0;
        int bVal = j >= 0 ? b[j] - '0' : 0;

        val = (aVal + bVal + carry) % 10;
        carry = (aVal + bVal + carry) / 10; 
        res[k--] = val + '0';
        --i;
        --j;
    }
    if (carry > 0) {
        res.insert(0, "1");
    }
    return res;
}

string BInt::innerMul(string a, string b) {
    int m = a.size(), n = b.size();
    int len = m + n + 1;
    int i = m - 1, j = n - 1;
    string res(len, '0'); 

    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());

    int aVal = 0, bVal = 0, exist = 0, carry = 0;
    for (i = 0; i < m; ++i) {
        aVal = a[i] - '0';
        carry = 0;
        for (j = 0; j < n; ++j) {
            bVal = b[j] - '0';
            exist = res[i + j] - '0';
            res[i + j] = '0' + (aVal * bVal + exist + carry) % 10;
            carry = (aVal * bVal + exist + carry) / 10;
        }
        res[i + j] = '0' + carry;
    }
    // remove the leading zeros
    reverse(res.begin(), res.end());
    int t = 0;
    while (t < len && res[t] == '0') {
        ++t;
    }
    return res.substr(t);
}

BInt::~BInt() {

}
