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
    virtual string typeName() const = 0;
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

#endif