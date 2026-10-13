#include "TankerCar.h"
#include "../Config.h"

TankerCar::TankerCar(int id, double cargoTons, bool dangerous)
    : RailCar(id), cargoTons_(cargoTons), dangerous_(dangerous) {}

double TankerCar::weight() const {
    return Config::TANKER_TARE + cargoTons_;
}

double TankerCar::revenue() const {
    double baseRevenue = cargoTons_ * Config::TANKER_RATE_PER_TON;
    if (dangerous_) return baseRevenue * Config::DANGEROUS_SURCHARGE;
    return baseRevenue;
}

string TankerCar::describe() const {
    string text = "[#" + to_string(id()) + "] Tanker | " +
                  formatOneDecimal(cargoTons_) + " t cargo | " +
                  formatOneDecimal(weight()) + " t";
    if (dangerous_) text += " | DANGEROUS";
    return text;
}
