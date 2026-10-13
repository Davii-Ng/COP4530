#ifndef PASSENGERCAR_H
#define PASSENGERCAR_H

#include "RailCar.h"

// Car carrying passengers.
class PassengerCar : public RailCar {
public:
    PassengerCar(int id, int passengerCount);

    CarKind kind() const override { return CarKind::Passenger; }
    string typeName() const override;
    double weight() const override;
    double revenue() const override;
    string describe() const override;

private:
    int passengerCount_;
};

#endif