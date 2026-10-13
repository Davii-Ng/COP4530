#include "Locomotive.h"
#include "../Config.h"

double Locomotive::weight() const { return Config::LOCO_WEIGHT; }

// Engines pull the train but earn nothing.
double Locomotive::revenue() const { return 0.0; }

double Locomotive::pullCapacity() const { return Config::LOCO_PULL_CAPACITY; }

string Locomotive::describe() const {
    return "[#" + to_string(id()) + "] Locomotive | pulls " +
           formatOneDecimal(pullCapacity()) + " t | " +
           formatOneDecimal(weight()) + " t";
}