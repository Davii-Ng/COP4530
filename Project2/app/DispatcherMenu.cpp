#include "DispatcherMenu.h"
#include <iostream>
#include "InputUtils.h"

void DispatcherMenu::run() {
    int choice = -1;
    while (choice != 0) {
        printMenu();
        choice = readInt("Choice: ", 0, 15);

        if (choice == 1) train_.printDetails();
        else if (choice == 2) coupleCar(true);
        else if (choice == 3) coupleCar(false);
        else if (choice == 4) uncoupleCar(true);
        else if (choice == 5) uncoupleCar(false);
        else if (choice == 6) shuntToSiding();
        else if (choice == 7) pullFromSiding();
        else if (choice == 8) insertCar();
        else if (choice == 9) removeCar();
        else if (choice == 10) findCar();
        else if (choice == 11) train_.sortByWeight();
        else if (choice == 12) train_.reverseTrain();
        else if (choice == 13) showStatistics();
        else if (choice == 14) inspectAndDepart();
        else if (choice == 15) train_.loadDemo(nextId_);

        // After every option, show the train and the siding.
        cout << "\n";
        train_.print();
        siding_.print();
    }
    cout << "Goodbye.\n";
}

void DispatcherMenu::printMenu() const {
    cout << "\n=== RailYard Dispatcher ===\n"
         << " 1. View train\n"
         << " 2. Couple car to front\n"
         << " 3. Couple car to rear\n"
         << " 4. Uncouple front car\n"
         << " 5. Uncouple rear car\n"
         << " 6. Shunt rear car to siding\n"
         << " 7. Pull car from siding\n"
         << " 8. Insert car at position\n"
         << " 9. Remove car at position\n"
         << "10. Find car by ID\n"
         << "11. Sort by weight\n"
         << "12. Reverse train\n"
         << "13. Statistics\n"
         << "14. Inspect and depart\n"
         << "15. Load demo train\n"
         << " 0. Exit\n";
}

CarPtr DispatcherMenu::buildCar() {
    int type = readInt("Type (1 Locomotive, 2 Passenger, 3 Freight, 4 Tanker): ", 1, 4);
    int id = nextId_;
    nextId_++;

    if (type == 1) {
        return makeCar(CarKind::Locomotive, id);
    }
    if (type == 2) {
        int people = readInt("Passengers: ", 0, Config::PASSENGER_MAX_SEATS);
        return makeCar(CarKind::Passenger, id, people);
    }
    if (type == 3) {
        double tons = readDouble("Cargo tons: ", 0, Config::FREIGHT_MAX_LOAD);
        return makeCar(CarKind::Freight, id, tons);
    }
    double tons = readDouble("Cargo tons: ", 0, Config::TANKER_MAX_LOAD);
    bool dangerous = readYesNo("Dangerous cargo?");
    return makeCar(CarKind::Tanker, id, tons, dangerous);
}

// Options 2 and 3
void DispatcherMenu::coupleCar(bool atFront) {
    if (train_.full()) {
        cout << "The train is full.\n";
        return;
    }
    CarPtr car = buildCar();
    if (atFront) train_.addFront(move(car));
    else train_.addRear(move(car));
}

// Options 4 and 5
void DispatcherMenu::uncoupleCar(bool atFront) {
    if (train_.empty()) {
        cout << "The train is empty.\n";
        return;
    }
    bool toSiding = readYesNo("Send the car to the siding? (n = scrap it)");
    if (toSiding && siding_.full()) {
        cout << "The siding is full.\n";
        return;
    }

    CarPtr car;
    if (atFront) car = train_.removeFront();
    else car = train_.removeRear();

    if (toSiding) siding_.push(move(car));   // otherwise the car is deleted here
}

// Option 6
void DispatcherMenu::shuntToSiding() {
    if (train_.empty()) {
        cout << "The train is empty.\n";
    } else if (siding_.full()) {
        cout << "The siding is full.\n";
    } else {
        siding_.push(train_.removeRear());
    }
}

// Option 7
void DispatcherMenu::pullFromSiding() {
    if (siding_.empty()) {
        cout << "The siding is empty.\n";
    } else if (train_.full()) {
        cout << "The train is full.\n";
    } else {
        train_.addRear(siding_.pop());
    }
}

// Option 8
void DispatcherMenu::insertCar() {
    if (train_.full()) {
        cout << "The train is full.\n";
        return;
    }
    int last = train_.size() + 1;
    int pos = readInt("Position (1-" + to_string(last) + "): ", 1, last);
    train_.insertAt(pos - 1, buildCar());
}

// Option 9
void DispatcherMenu::removeCar() {
    if (train_.empty()) {
        cout << "The train is empty.\n";
        return;
    }
    int pos = readInt("Position (1-" + to_string(train_.size()) + "): ", 1, train_.size());
    train_.removeAt(pos - 1);   // the car is deleted
}

// Option 10
void DispatcherMenu::findCar() const {
    int id = readInt("Car ID: ", 1, 9999);
    int pos = train_.findById(id);
    if (pos == -1) cout << "No car with that ID.\n";
    else cout << "Found at position " << pos + 1 << ".\n";
}

// Option 13
void DispatcherMenu::showStatistics() const {
    cout << "Locomotives: " << train_.countKind(CarKind::Locomotive) << "\n"
         << "Passenger cars: " << train_.countKind(CarKind::Passenger) << "\n"
         << "Freight cars: " << train_.countKind(CarKind::Freight) << "\n"
         << "Tanker cars: " << train_.countKind(CarKind::Tanker) << "\n"
         << "Total weight: " << formatOneDecimal(train_.totalWeight()) << " t\n"
         << "Pulling capacity: " << formatOneDecimal(train_.totalPull()) << " t\n"
         << "Revenue: $" << formatOneDecimal(train_.totalRevenue()) << "\n";
}

// Option 14
void DispatcherMenu::inspectAndDepart() {
    cout << "Inspecting...\n";
    if (train_.inspect()) {
        cout << "Inspection passed.\n";
        train_.depart();
    } else {
        cout << "Inspection failed. The train cannot depart.\n";
    }
}
