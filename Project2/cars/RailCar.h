#ifndef RAILCAR_H
#define RAILCAR_H

#include <string>
#include <memory>
using namespace std;

enum class CarKind { Locomotive, Passenger, Freight, Tanker };

// Abstract base class for all rail cars.
class RailCar {
public:
    explicit RailCar(int id) : id_(id) {}
    virtual ~RailCar() = default;

    int id() const { return id_; }

    virtual CarKind kind() const = 0;
    virtual double weight() const = 0;
    virtual double revenue() const = 0;
    virtual string describe() const = 0;

    // Defaults; only TankerCar and Locomotive override these.
    virtual bool isDangerous() const { return false; }
    virtual double pullCapacity() const { return 0.0; }

private:
    int id_;
};

// Each car has exactly one owner (train or siding).
using CarPtr = unique_ptr<RailCar>;

// Formats a number with 1 decimal place, e.g. 28.2
inline string formatOneDecimal(double value) {
    long tenths = static_cast<long>(value * 10 + 0.5);
    return to_string(tenths / 10) + "." + to_string(tenths % 10);
}

#endif