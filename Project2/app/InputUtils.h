#ifndef INPUTUTILS_H
#define INPUTUTILS_H

#include <string>
using namespace std;

// Ask until the user types a valid answer.
int readInt(string prompt, int min, int max);
double readDouble(string prompt, double min, double max);
bool readYesNo(string prompt);

#endif
