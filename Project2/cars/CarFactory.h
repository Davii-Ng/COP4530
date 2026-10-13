#ifndef CARFACTORY_H
#define CARFACTORY_H

#include "RailCar.h"

// Creates a car of the given kind.
// amount = passengers or cargo tons (unused for Locomotive).
// dangerous = only used for Tanker.
CarPtr makeCar(CarKind kind, int id, double amount = 0.0, bool dangerous = false);

#endif