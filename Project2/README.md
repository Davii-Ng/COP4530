# RailYard Dispatcher

A console-based train yard simulator built on `std::deque`. The user plays the dispatcher: build cars, couple them to the train, shunt them onto a siding, inspect, and depart to earn revenue.

## Features

- Couple/uncouple cars at the front or rear of the train
- Insert/remove a car at any position
- Shunt cars to a siding and pull them back
- Find a car by ID
- Sort by weight, reverse the train
- Statistics (car counts, total weight, pulling capacity, revenue)
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

## Usage

The program shows a numbered menu. Type a number and press Enter. After every option, the train and the siding are drawn on the screen.

```
FRONT [L1]=[P2]=[F3]=[T4!] REAR
Siding (top is last): [F5] [P6]
```

- The front of the train is on the left.
- `L` locomotive, `P` passenger, `F` freight, `T` tanker. The number is the car ID.
- `!` marks a car with dangerous cargo.
- The siding is drawn bottom to top, so the last car is the next one to come off.
- Positions you type start at 1.
- Wrong input (letters, a number out of range) is rejected and asked again.

### Menu

| Option | Action | Details |
|--------|--------|---------|
| 1  | view train | one line per car with its position, weight, and details |
| 2  | couple car to front | asks for a car type and its details |
| 3  | couple car to rear | same, at the rear |
| 4  | uncouple front car | asks: send to siding, or scrap it |
| 5  | uncouple rear car | same, for the rear car |
| 6  | shunt rear car to siding | moves the train's rear car onto the siding |
| 7  | pull car from siding | moves the top siding car to the train's rear |
| 8  | insert car at position | asks for a position, then builds a car |
| 9  | remove car at position | the car is deleted |
| 10 | find car by ID | prints the position, or "No car with that ID." |
| 11 | sort by weight | lightest first; a lead locomotive stays in front |
| 12 | reverse train | turns the train around |
| 13 | statistics | car counts, total weight, pulling capacity, revenue |
| 14 | inspect and depart | checks the rules; if all pass, prints the departure report |
| 15 | load demo train | replaces the train with a 6-car train that passes inspection |
| 0  | exit | |

### Cars

All numbers are in `Config.h`. Weights are in tons.

| Car | Empty weight | Details you enter | Weight | Revenue |
|-----|--------------|-------------------|--------|---------|
| Locomotive | 60 | none | 60 | $0 (pulls up to 300 t) |
| Passenger | 25 | passengers, 0-80 | 25 + 0.08 per passenger | $40 per passenger |
| Freight | 20 | cargo tons, 0-70 | 20 + cargo | $15 per ton |
| Tanker | 30 | cargo tons, 0-60, dangerous y/n | 30 + cargo | $25 per ton, x1.5 if dangerous |

### Departure Rules

Option 14 lists every broken rule, not just the first. The train departs only when all five pass.

1. An engine must be at the front
2. Total weight must not exceed the engines' combined pulling capacity
3. A dangerous car cannot sit next to a passenger car
4. The train cannot exceed the maximum length (12 cars)
5. The train must carry something besides locomotives

The siding holds at most 6 cars. After a departure the train stays in place, so you can keep editing it.

### Messages for special cases

| Situation | Message |
|-----------|---------|
| uncouple, shunt, or remove on an empty train | `The train is empty.` |
| couple or insert on a full train (12 cars) | `The train is full.` |
| pull from an empty siding | `The siding is empty.` |
| shunt or send to a full siding (6 cars) | `The siding is full.` |
| find an unknown ID | `No car with that ID.` |

## Example Session

Input is shown after each prompt. Menus are left out to keep this short.

```
Choice: 2                                   (couple car to front)
Type (1 Locomotive, 2 Passenger, 3 Freight, 4 Tanker): 1

FRONT [L1] REAR
Siding (top is last): empty

Choice: 2
Type (1 Locomotive, 2 Passenger, 3 Freight, 4 Tanker): 4
Cargo tons: 67                              (too heavy for a tanker)
Please enter a number from 0 to 60.
Cargo tons: 60
Dangerous cargo? (y/n): y

FRONT [T2!]=[L1] REAR                       (tanker is in front of the locomotive)
Siding (top is last): empty

Choice: 12                                  (reverse train)

FRONT [L1]=[T2!] REAR
Siding (top is last): empty

Choice: 14                                  (inspect and depart)
Inspecting...
Inspection passed.

=== Departure report: trip 1 ===
  [#1] Locomotive | pulls 300.0 t | 60.0 t | revenue $0.0
  [#2] Tanker | 60.0 t cargo | 90.0 t | DANGEROUS | revenue $2250.0
  Total weight: 150.0 t
  Total revenue: $2250.0

Choice: 6                                   (shunt rear car to siding)

FRONT [L1] REAR
Siding (top is last): [T2!]

Choice: 14                                  (nothing to carry now)
Inspecting...
  Rule 5: the train has no cargo or passengers.
Inspection failed. The train cannot depart.
```

Tip: option 15 loads a ready-made train, which is a quick way to try options 10-14.

## Design Notes

- **Deque**: `Track` holds a `std::deque<std::unique_ptr<RailCar>>`. The train uses both ends, so it works like a double-ended queue. The siding uses the same deque from one end only, so it works like a stack.
- **Inheritance**: there are two hierarchies.
  - `RailCar` is abstract, with `Locomotive`, `PassengerCar`, `FreightCar`, and `TankerCar`. Each car type computes its own weight and revenue, so the rest of the program only calls `RailCar` functions.
  - `Track` is the base of `Train` and `Siding`. Both reuse the deque but expose different ends.
- **Single owner**: each car is held by a `unique_ptr`, so moving it between train and siding never copies it. A car that is removed or scrapped is deleted automatically.
- **Deque operations used**: `push_front`, `push_back`, `pop_front`, `pop_back`, `front`, `back`, `insert`, `erase`, `[]`, `size`, `empty`, `clear`. `Train` also uses `std::sort` and `std::reverse` from `<algorithm>`.
- **Car IDs** start at 1 and are never reused, even after a car is removed or the demo train is loaded again.

## Group Members

- Minh Duong Nguyen
- Ngoc Viet Nguyen
