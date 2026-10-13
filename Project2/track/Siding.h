#ifndef SIDING_H
#define SIDING_H

#include "Track.h"
#include "../Config.h"

// Dead-end track. Cars go on and come off the rear only, so it works like a stack.
class Siding : public Track {
public:
    Siding() : Track(Config::SIDING_CAPACITY) {}

    bool push(CarPtr car);   // returns false if the siding is full
    CarPtr pop();            // returns nullptr if the siding is empty
    void print() const override;
};

#endif
