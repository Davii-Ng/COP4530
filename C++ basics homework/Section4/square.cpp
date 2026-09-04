#include <iostream>
using namespace std;


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


class Square : public Rectangle{
    public:
        void setSides(double s){
            setValues(s, s);
        }
};


int main(){
    Square sq;
    sq.setSides(4.5);
    cout << "Area of the square: "<< sq.getArea() << endl;
    cout << "Perimeter of the square: "<< sq.getPerimeter() << endl;
}