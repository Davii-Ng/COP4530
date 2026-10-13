#ifndef LOCOMOTIVE_H
#define LOCOMOTIVE_H

#include "RailCar.h"

// Engine car. Pulls the train, earns no revenue.
class Locomotive : public RailCar {
public:
    explicit Locomotive(int id) : RailCar(id) {}

    CarKind kind() const override { return CarKind::Locomotive; }
    string typeName() const override;
    double weight() const override;
    double revenue() const override;
    string describe() const override;
    double pullCapacity() const override;
};

#endif