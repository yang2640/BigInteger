#include "BInt.h"
#include <iostream>
using namespace std;

int main() {
    BInt num1("12");
    BInt num2("12");
    BInt res = num1 + num2;
    cout << res << endl;
    res = num1 * num2;
    cout << res << endl;
    res = num1 - num2;
    cout << res << endl;
    return 0;
}
