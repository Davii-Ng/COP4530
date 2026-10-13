#ifndef TRAIN_H
#define TRAIN_H

#include "Track.h"
#include "../Config.h"

// The train. Cars can be added or removed at both ends (a double-ended queue).
// Positions are 0-based.
class Train : public Track {
public:
    Train() : Track(Config::MAX_TRAIN_LENGTH) {}

    // Adding cars. Return false if the train is full (or pos is out of range).
    bool addFront(CarPtr car);
    bool addRear(CarPtr car);
    bool insertAt(int pos, CarPtr car);

    // Removing cars. Return nullptr if the train is empty (or pos is out of range).
    CarPtr removeFront();
    CarPtr removeRear();
    CarPtr removeAt(int pos);

    // Returns the position of the car with this ID, or -1 if there is none.
    int findById(int id) const;

    // Totals over all cars.
    double totalWeight() const;
    double totalPull() const;
    double totalRevenue() const;
    int countKind(CarKind kind) const;

    void sortByWeight();   // lightest first, a lead locomotive stays in front
    void reverseTrain();

    // Checks the 5 departure rules. Prints each broken rule.
    // Returns true if the train passes.
    bool inspect() const;

    // Prints the departure report.
    void depart();

    // Replaces the train with a 6-car train that passes inspection.
    // nextId is the next unused car ID; it is increased for each car made.
    void loadDemo(int& nextId);

    void printDetails() const;      // one line per car
    void print() const override;    // ASCII drawing

private:
    int tripCount_ = 0;   // number of departures so far
};

#endif
