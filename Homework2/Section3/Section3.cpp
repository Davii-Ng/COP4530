#include <iostream>
#include <string>

using namespace std;

template <typename A, typename B>
class Pair {
private:
    A first;
    B second;

public:
    Pair(const A& firstValue, const B& secondValue)
        : first(firstValue), second(secondValue) {}

    void printMe() const {
        cout << first << ", " << second << '\n';
    }
};

int main() {
    Pair<int, string> p1(1, "apple");
    Pair<float, long> p2(3.14f, 100000L);
    Pair<char, double> p3('A', 2.718);
    Pair<string, bool> p4("active", true);
    Pair<int, char> p5(65, 'Z');

    p1.printMe();
    p2.printMe();
    p3.printMe();
    p4.printMe();
    p5.printMe();

    return 0;
}
