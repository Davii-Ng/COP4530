#include "Track.h"

string Track::symbol(const RailCar& car) const {
    string text;
    if (car.kind() == CarKind::Locomotive) text = "L";
    else if (car.kind() == CarKind::Passenger) text = "P";
    else if (car.kind() == CarKind::Freight) text = "F";
    else text = "T";

    text += to_string(car.id());
    if (car.isDangerous()) text += "!";
    return "[" + text + "]";
}
