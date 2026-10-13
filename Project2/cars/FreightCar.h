#ifndef FREIGHTCAR_H
#define FREIGHTCAR_H

#include "RailCar.h"

// Car transporting general cargo.
class FreightCar : public RailCar {
public:
    FreightCar(int id, double cargoTons);

    CarKind kind() const override { return CarKind::Freight; }
    double weight() const override;
    double revenue() const override;
    string describe() const override;

private:
    double cargoTons_;
};

#endif