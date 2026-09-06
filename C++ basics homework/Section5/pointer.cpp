#include <iostream>
using namespace std;

int main(){
    int x = 5;
    int *ptr = &x;  // The first * is used to declare variable type is a pointer
                    // The & references to the address of the variable
    cout << x << endl;
    cout << &x << endl;
    cout << ptr << endl;    //Pointer value is the same as address of the variable its pointing to
    cout << *ptr << endl;   // The * in this case is used to de-reference the pointer, which means that to print out the value of the pointer's address pointing to
    cout << &ptr << endl;
    

}