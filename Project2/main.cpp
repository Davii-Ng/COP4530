#include <iostream>
#include "cars/CarFactory.h"

using namespace std;

// Prints the numbered menu.
void printMenu() {
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
         << " 0. Exit\n"
         << "Choice: ";
}

int main() {
    // TODO: create Train and Siding objects here
    int choice = -1;

    while (choice != 0) {
        printMenu();
        cin >> choice;

        switch (choice) {
            case 1:  // TODO: print the train
            case 2:  // TODO: build a car with makeCar(), push to front
            case 3:  // TODO: build a car with makeCar(), push to rear
            case 4:  // TODO: pop front car
            case 5:  // TODO: pop rear car
            case 6:  // TODO: move rear car to siding
            case 7:  // TODO: move siding car back to train
            case 8:  // TODO: insert car at position
            case 9:  // TODO: remove car at position
            case 10: // TODO: find car by ID
            case 11: // TODO: sort by weight
            case 12: // TODO: reverse train
            case 13: // TODO: print statistics
            case 14: // TODO: run safety checks, then depart
            case 15: // TODO: load demo train
                cout << "Not implemented yet.\n";
                break;
            case 0:
                cout << "Goodbye.\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }
    }
    return 0;
}
