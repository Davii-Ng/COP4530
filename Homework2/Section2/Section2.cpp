#include <iostream>
#include <memory>
using namespace std;

class Object {
public:
    virtual ~Object() = default;
    virtual void printMe() = 0;   // abstract: Object cannot be instantiated
};

class Place : public Object {
public:
    void printMe() override { cout << "Buy it.\n"; }
};

class Region : public Place {
public:
    void printMe() override { cout << "Box it.\n"; }
};

class State : public Region {
public:
    void printMe() override { cout << "Ship it.\n"; }
};

class Maryland : public State {
public:
    void printMe() override { cout << "Read it.\n"; }
};

int main() {
    // Smart pointers own the objects, so the example has no memory leaks.
    auto state = make_unique<State>();
    auto maryland = make_unique<Maryland>();
    auto place = make_unique<Place>();
    auto region = make_unique<Region>();

    Region* mid = state.get();          // object is State
    State* md = maryland.get();         // object is Maryland
    Object* obj = place.get();          // object is Place
    Place* usa = region.get();          // object is Region

    md->printMe();                              // Maryland -> Read it.
    mid->printMe();                             // State -> Ship it.
    (dynamic_cast<Place*>(obj))->printMe();     // Place -> Buy it.

    obj = md;                                   // obj now points to Maryland
    (dynamic_cast<Maryland*>(obj))->printMe();  // -> Read it.

    obj = usa;                                  // obj now points to Region
    (dynamic_cast<Place*>(obj))->printMe();     // Region -> Box it.

    usa = md;                                   // usa now points to Maryland
    (dynamic_cast<Place*>(usa))->printMe();     // -> Read it.

    return 0;
}
