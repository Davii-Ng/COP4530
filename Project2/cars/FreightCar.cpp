#include "FreightCar.h"
#include "../Config.h"

FreightCar::FreightCar(int id, double cargoTons)
    : RailCar(id), cargoTons_(cargoTons) {}

double FreightCar::weight() const {
    return Config::FREIGHT_TARE + cargoTons_;
}

double FreightCar::revenue() const {
    return cargoTons_ * Config::FREIGHT_RATE_PER_TON;
}

string FreightCar::describe() const {
    return "[#" + to_string(id()) + "] Freight | " +
           formatOneDecimal(cargoTons_) + " t cargo | " +
           formatOneDecimal(weight()) + " t";
}
