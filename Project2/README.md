# RailYard Dispatcher

A console-based train yard simulator built on `std::deque`. The user plays the dispatcher: build cars, couple them to the train, shunt them onto a siding, inspect, and depart to earn revenue.

## Features

- Couple/uncouple cars at the front or rear of the train
- Insert/remove a car at any position
- Shunt cars to a siding and pull them back
- Find a car by ID
- Sort by weight, reverse the train
- Statistics (total weight, total revenue)
- Safety inspection before departure (reports every failed rule)
- Demo train

## File Structure

```
.
├── Config.h                       # shared constants
├── cars/
│   ├── RailCar.h                  # abstract base class
│   ├── Locomotive / PassengerCar  # car types
│   ├── FreightCar / TankerCar
│   └── CarFactory                 # builds a car by kind
├── track/
│   ├── Track                      # base class holding the deque
│   ├── Train                      # both ends
│   └── Siding                     # one end (stack)
├── app/
│   ├── InputUtils                 # safe input reading
│   └── DispatcherMenu             # menu and actions
└── main.cpp
```

## Build & Run

Requires a C++17 compiler.

```
g++ -std=c++17 -Wall -Wextra -pedantic cars/*.cpp track/*.cpp app/*.cpp main.cpp -o railyard
./railyard
```

## Menu

| Option | Action |
|--------|--------|
| 1  | view train |
| 2  | couple car to front |
| 3  | couple car to rear |
| 4  | uncouple front car |
| 5  | uncouple rear car |
| 6  | shunt rear car to siding |
| 7  | pull car from siding |
| 8  | insert car at position |
| 9  | remove car at position |
| 10 | find car by ID |
| 11 | sort by weight |
| 12 | reverse train |
| 13 | statistics |
| 14 | inspect and depart |
| 15 | load demo train |
| 0  | exit |

## Departure Rules

- An engine must be at the front
- Total weight must not exceed the engines' pulling capacity
- A dangerous tanker cannot sit next to a passenger car
- The train cannot exceed the maximum length

## Design Notes

- **Deque**: the train can grow or shrink at both ends. The siding uses the same deque from one end only, so it works like a stack.
- **Inheritance**: each car type computes its own weight and revenue, so the rest of the program only calls `RailCar` functions.
- **Single owner**: each car is held by a `unique_ptr`, so moving it between train and siding never copies it.

## Group Members

- Minh Duong Nguyen
- Ngoc Viet Nguyen
