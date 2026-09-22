#include <iostream>
#include <cstdlib>
using namespace std;

class Object {
public:
    virtual void printMe() = 0;   // abstract: can't instantiate
};

class Place : public Object {
public:
    virtual void printMe() { cout << "Buy it.\n"; }
};

class Region : public Place {
public:
    virtual void printMe() { cout << "Box it.\n"; }
};

class State : public Region {
public:
    virtual void printMe() { cout << "Ship it.\n"; }
};

class Maryland : public State {
public:
    virtual void printMe() { cout << "Read it.\n"; }
};

int main() {
    Region* mid = new State;      // object is State
    State*  md  = new Maryland;   // object is Maryland
    Object* obj = new Place;      // object is Place
    Place*  usa = new Region;     // object is Region

    md->printMe();                              // md is Maryland -> Read it.
    mid->printMe();                             // mid is State -> Ship it.
    (dynamic_cast<Place*>(obj))->printMe();     // obj is Place -> Buy it.

    obj = md;                                   // obj now points to Maryland
    (dynamic_cast<Maryland*>(obj))->printMe();  // -> Read it.

    obj = usa;                                  // obj now points to Region
    (dynamic_cast<Place*>(obj))->printMe();     // cast to Place*, but object is Region -> Box it.

    usa = md;                                   // usa now points to Maryland
    (dynamic_cast<Place*>(usa))->printMe();     // -> Read it.

    return EXIT_SUCCESS;
}

/*
Reasoning: printMe() is virtual, so each call runs the override of the
object's actual type (set by new), not the pointer type or the cast.
Casts only re-type the pointer; they never change which function runs.
Track each pointer's last assignment to know the object.

Output:
Read it.
Ship it.
Buy it.
Read it.
Box it.
Read it.
*/