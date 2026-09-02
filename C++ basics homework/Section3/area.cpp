#include <iostream>
using namespace std;

double calculateArea(double length, double width);

int main(){
    double length;
    double width;
    double area;

    cout << "Enter the length: ";
    cin >> length;

    cout << "Enter the width: ";
    cin >> width;

    area = calculateArea(length, width);

    cout << "Calculated area: " << area;
    return 0;
}

double calculateArea(double length, double width){
    return length * width;
}