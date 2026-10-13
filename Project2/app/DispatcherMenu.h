#ifndef DISPATCHERMENU_H
#define DISPATCHERMENU_H

#include "../cars/CarFactory.h"
#include "../track/Siding.h"
#include "../track/Train.h"

// The menu. It owns the train and the siding and calls their functions.
// Positions the user types start at 1.
class DispatcherMenu {
public:
    void run();   // repeats until the user picks 0

private:
    Train train_;     // the train being built
    Siding siding_;   // parking track
    int nextId_ = 1;  // ID for the next car that is made

    void printMenu() const;
    CarPtr buildCar();   // asks the user what car to make

    void coupleCar(bool atFront);
    void uncoupleCar(bool atFront);
    void shuntToSiding();
    void pullFromSiding();
    void insertCar();
    void removeCar();
    void findCar() const;
    void showStatistics() const;
    void inspectAndDepart();
};

#endif
