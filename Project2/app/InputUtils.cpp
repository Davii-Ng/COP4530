#include "InputUtils.h"
#include <cstdlib>
#include <iostream>

int readInt(string prompt, int min, int max) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value && value >= min && value <= max) {
            cin.ignore(1000, '\n');
            return value;
        }
        if (cin.eof()) exit(0);   // no more input
        cin.clear();              // clear the error, throw away the bad line
        cin.ignore(1000, '\n');
        cout << "Please enter a number from " << min << " to " << max << ".\n";
    }
}

double readDouble(string prompt, double min, double max) {
    double value;
    while (true) {
        cout << prompt;
        if (cin >> value && value >= min && value <= max) {
            cin.ignore(1000, '\n');
            return value;
        }
        if (cin.eof()) exit(0);
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Please enter a number from " << min << " to " << max << ".\n";
    }
}

bool readYesNo(string prompt) {
    char answer;
    while (true) {
        cout << prompt << " (y/n): ";
        if (!(cin >> answer)) exit(0);   // no more input
        cin.ignore(1000, '\n');
        if (answer == 'y' || answer == 'Y') return true;
        if (answer == 'n' || answer == 'N') return false;
        cout << "Please type y or n.\n";
    }
}
