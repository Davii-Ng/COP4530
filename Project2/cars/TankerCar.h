#ifndef TANKERCAR_H
#define TANKERCAR_H

#include "RailCar.h"

// Car transporting liquid. May be marked as dangerous cargo.
class TankerCar : public RailCar {
public:
    TankerCar(int id, double cargoTons, bool dangerous);

    CarKind kind() const override { return CarKind::Tanker; }
    string typeName() const override;
    double weight() const override;

    // Adds a surcharge if dangerous.
    double revenue() const override;

    string describe() const override;
    bool isDangerous() const override { return dangerous_; }

private:
    double cargoTons_;
    bool dangerous_;
};

#endif