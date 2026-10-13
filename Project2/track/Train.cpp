#include "Train.h"
#include <algorithm>
#include <iostream>
#include "../cars/CarFactory.h"

// Used by sort: true if car a is lighter than car b.
static bool lighter(const CarPtr& a, const CarPtr& b) {
    return a->weight() < b->weight();
}

bool Train::addFront(CarPtr car) {
    if (full()) return false;
    cars_.push_front(move(car));   // the train owns the car now
    return true;
}

bool Train::addRear(CarPtr car) {
    if (full()) return false;
    cars_.push_back(move(car));
    return true;
}

bool Train::insertAt(int pos, CarPtr car) {
    if (full() || pos < 0 || pos > size()) return false;
    cars_.insert(cars_.begin() + pos, move(car));
    return true;
}

CarPtr Train::removeFront() {
    if (empty()) return nullptr;
    CarPtr car = move(cars_.front());   // the caller owns the car now
    cars_.pop_front();
    return car;
}

CarPtr Train::removeRear() {
    if (empty()) return nullptr;
    CarPtr car = move(cars_.back());
    cars_.pop_back();
    return car;
}

CarPtr Train::removeAt(int pos) {
    if (pos < 0 || pos >= size()) return nullptr;
    CarPtr car = move(cars_[pos]);
    cars_.erase(cars_.begin() + pos);
    return car;
}

int Train::findById(int id) const {
    for (int i = 0; i < size(); i++) {
        if (cars_[i]->id() == id) return i;
    }
    return -1;
}

double Train::totalWeight() const {
    double total = 0;
    for (int i = 0; i < size(); i++) total += cars_[i]->weight();
    return total;
}

// Only locomotives have a pulling capacity above 0.
double Train::totalPull() const {
    double total = 0;
    for (int i = 0; i < size(); i++) total += cars_[i]->pullCapacity();
    return total;
}

double Train::totalRevenue() const {
    double total = 0;
    for (int i = 0; i < size(); i++) total += cars_[i]->revenue();
    return total;
}

int Train::countKind(CarKind kind) const {
    int count = 0;
    for (int i = 0; i < size(); i++) {
        if (cars_[i]->kind() == kind) count++;
    }
    return count;
}

void Train::sortByWeight() {
    // Skip the first car if it is a locomotive, so it stays in front.
    int start = 0;
    if (!empty() && cars_[0]->kind() == CarKind::Locomotive) start = 1;
    sort(cars_.begin() + start, cars_.end(), lighter);
}

void Train::reverseTrain() {
    reverse(cars_.begin(), cars_.end());
}

bool Train::inspect() const {
    bool ok = true;

    // Rule 1: a locomotive must be at the front.
    if (empty() || cars_[0]->kind() != CarKind::Locomotive) {
        cout << "  Rule 1: the front car must be a locomotive.\n";
        ok = false;
    }

    // Rule 2: the locomotives must be able to pull the total weight.
    if (totalWeight() > totalPull()) {
        cout << "  Rule 2: train weighs " << formatOneDecimal(totalWeight())
             << " t but the locomotives pull only " << formatOneDecimal(totalPull()) << " t.\n";
        ok = false;
    }

    // Rule 3: a dangerous car cannot be next to a passenger car.
    for (int i = 0; i + 1 < size(); i++) {
        const RailCar& a = *cars_[i];
        const RailCar& b = *cars_[i + 1];
        bool dangerousNextToPassenger =
            (a.isDangerous() && b.kind() == CarKind::Passenger) ||
            (a.kind() == CarKind::Passenger && b.isDangerous());
        if (dangerousNextToPassenger) {
            cout << "  Rule 3: " << symbol(a) << " is next to " << symbol(b) << ".\n";
            ok = false;
        }
    }

    // Rule 4: the train cannot be too long.
    if (size() > Config::MAX_TRAIN_LENGTH) {
        cout << "  Rule 4: the train is longer than " << Config::MAX_TRAIN_LENGTH << " cars.\n";
        ok = false;
    }

    // Rule 5: the train must carry something besides locomotives.
    if (size() == countKind(CarKind::Locomotive)) {
        cout << "  Rule 5: the train has no cargo or passengers.\n";
        ok = false;
    }

    return ok;
}

void Train::depart() {
    tripCount_++;
    cout << "\n=== Departure report: trip " << tripCount_ << " ===\n";
    for (int i = 0; i < size(); i++) {
        cout << "  " << cars_[i]->describe()
             << " | revenue $" << formatOneDecimal(cars_[i]->revenue()) << "\n";
    }
    cout << "  Total weight: " << formatOneDecimal(totalWeight()) << " t\n";
    cout << "  Total revenue: $" << formatOneDecimal(totalRevenue()) << "\n";
}

void Train::loadDemo(int& nextId) {
    cars_.clear();
    // The dangerous tanker is between freight cars, away from the passenger cars.
    addRear(makeCar(CarKind::Locomotive, nextId++));
    addRear(makeCar(CarKind::Passenger, nextId++, 40));
    addRear(makeCar(CarKind::Passenger, nextId++, 40));
    addRear(makeCar(CarKind::Freight, nextId++, 40));
    addRear(makeCar(CarKind::Tanker, nextId++, 30, true));
    addRear(makeCar(CarKind::Freight, nextId++, 30));
}

void Train::printDetails() const {
    for (int i = 0; i < size(); i++) {
        cout << (i + 1) << ". " << cars_[i]->describe() << "\n";
    }
}

void Train::print() const {
    cout << "FRONT ";
    if (empty()) cout << "(empty) ";
    for (int i = 0; i < size(); i++) {
        if (i > 0) cout << "=";
        cout << symbol(*cars_[i]);
    }
    cout << " REAR\n";
}
