#include <iostream>
using namespace std;

void swapInts(int &a, int &b){
    int temp;
    temp = b;
    b = a;
    a = temp;
}

int main(){
    int a = 6;
    int b = 7;
    cout << "Before swap: " << a << " " << b << "\n";
    swapInts(a, b);
    cout << "After swap: " << a << " " << b;
    return 0;
}
