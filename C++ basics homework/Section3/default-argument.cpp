#include <iostream>
using namespace std;


void applyDiscount(double price, double discount = 10.0){
    cout << "Final Price: " << price * (1- discount /100) << endl;
}

int main(){
    applyDiscount(100);
    applyDiscount(100, 20);
    return 0;
}
