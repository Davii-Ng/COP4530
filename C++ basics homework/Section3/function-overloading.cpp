#include <iostream>
using namespace std;

int add(int a , int b){
    return a + b;
}

int add(int a, int b, int c){
    return a + b + c;
}

double add(double a, double b){
    return a + b;
}

int main(){
    // Compiler calls the first version: add(int, int)
    cout << add(5, 10) << endl;      

    // Compiler calls the second version: add(int, int, int)
    cout << add(5, 10, 20) << endl;  

    // Compiler calls the third version: add(double, double)
    cout << add(5.5, 2.3) << endl;   

    return 0;
}
