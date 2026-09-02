#include <iostream>
using namespace std;

int main(){
    int number;
    cin >> number;
    if (number > 0){
        cout << "This number is postive";
    }else if(number < 0){
        cout << "This number is negative";
    }else{
        cout << "This number is 0";
    }
}