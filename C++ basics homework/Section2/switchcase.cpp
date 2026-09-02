#include <iostream>
#include <string>
using namespace std;

int main(){
    string week[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};

    int day;

    cout << "Enter a number of a day in the week: ";
    cin >> day;

    if(1 <= day <= 7){
        cout << week[day-1];
    }

    return 0;
}