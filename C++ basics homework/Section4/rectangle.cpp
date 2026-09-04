#include <iostream>
using namespace std;

class Rectangle {
    private:
        double length;
        double width;


    public:
        void setValues(double l, double w){
            length = l;
            width = w;
        }
        double getArea(){
            return length * width;
        }
        double getPerimeter(){
            return 2 * (length + width);
        }
};


int main(){
    Rectangle rectangle1;
    double length;
    double width;


    cout << "Enter the length: ";
    cin >> length;
    cout << "Enter the width: ";
    cin >> width;

    rectangle1.setValues(length, width);

    cout << "The area is: " << rectangle1.getArea() << endl;
    cout << "The perimeter is: " << rectangle1.getPerimeter();
}
