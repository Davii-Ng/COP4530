#include "Siding.h"
#include <iostream>

bool Siding::push(CarPtr car) {
    if (full()) return false;
    cars_.push_back(move(car));   // the siding owns the car now
    return true;
}

CarPtr Siding::pop() {
    if (empty()) return nullptr;
    CarPtr car = move(cars_.back());   // the caller owns the car now
    cars_.pop_back();
    return car;
}

void Siding::print() const {
    cout << "Siding (top is last):";
    if (empty()) cout << " empty";
    for (int i = 0; i < size(); i++) cout << " " << symbol(*cars_[i]);
    cout << "\n";
}
