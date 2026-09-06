#include <iostream>
using namespace std;

int main(){
    int number;

    cout << "Enter an integer: ";
    cin >> number;

    if (number > 0){
        cout << "This number is positive";
    }else if(number < 0){
        cout << "This number is negative";
    }else{
        cout << "This number is 0";
    }

    return 0;
}
