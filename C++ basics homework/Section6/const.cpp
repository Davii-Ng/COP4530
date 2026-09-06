#include <iostream>
#include <string>
using namespace std;

const double TAX_RATE = 0.07;   // constant variable

double addTax(const double &price) {  //Lock the price
    // price = 0;    // won't compile — price is read-only here    
    return price + (price * TAX_RATE);
}

int main() {
    double item = 25.00;
    cout << "Before tax: " << item << endl;
    cout << "After tax:  " << addTax(item) << endl;
    return 0;
}
