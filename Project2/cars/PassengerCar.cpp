#include "PassengerCar.h"
#include "../Config.h"

PassengerCar::PassengerCar(int id, int passengerCount)
    : RailCar(id), passengerCount_(passengerCount) {}

double PassengerCar::weight() const {
    return Config::PASSENGER_TARE +
           passengerCount_ * Config::PASSENGER_WEIGHT_PER_PERSON;
}

double PassengerCar::revenue() const {
    return passengerCount_ * Config::TICKET_PRICE;
}

string PassengerCar::describe() const {
    return "[#" + to_string(id()) + "] Passenger | " +
           to_string(passengerCount_) + " pax | " +
           formatOneDecimal(weight()) + " t";
}