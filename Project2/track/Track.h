#ifndef TRACK_H
#define TRACK_H

#include <deque>
#include <string>
#include "../cars/RailCar.h"
using namespace std;

// Base class for a stretch of track. It holds the deque of cars.
class Track {
public:
    Track(int capacity) : capacity_(capacity) {}
    virtual ~Track() {}

    int size() const { return cars_.size(); }
    bool empty() const { return cars_.empty(); }
    bool full() const { return size() >= capacity_; }

    // Draws the track on the screen.
    virtual void print() const = 0;

protected:
    deque<CarPtr> cars_;   // the cars, index 0 is the front
    int capacity_;         // most cars this track can hold

    // Short name of a car, like "L1" or "T5!" (! = dangerous).
    string symbol(const RailCar& car) const;
};

#endif
