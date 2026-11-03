# Decision Tree Explorer

A console program that reads a decision tree from a file, builds it as a general linked tree, writes an analysis to `about_tree.txt`, and lets the user explore nodes by position.

## Features

- Build the tree from any valid file (tab or space separated)
- Tree drawing with dash indentation and `[edge]` labels
- Tree properties: root, internal/external counts, height, preorder node lists
- Binary tree analysis: binary, proper, perfect, balanced
- Interactive explorer: content, ancestor, descendant, sibling of a node

## File Structure

```
.
├── main.cpp                  # entry point, connects the modules
├── src/
│   ├── LinkedTree            # TreeNode and the linked tree
│   ├── TreeParser            # reads the file, builds the tree
│   ├── TreeAnalyzer          # counts, height, binary checks
│   ├── TreeReport            # writes about_tree.txt
│   └── TreeExplorer          # console loop
└── data/
    ├── tree-car-2.txt
    └── tree-investment-2.txt
```

## Build & Run

Requires a C++17 compiler.

```
g++ -std=c++17 -Wall -Wextra main.cpp src/*.cpp -o decision_tree
./decision_tree data/tree-car-2.txt
```

`about_tree.txt` is written to the current directory.

## Input Format

Each line: `level position edge-label content`. The root line may omit the edge label, or be content only.

```
0 1 Do you currently own a car?
1 2 Yes Is the car in good working condition?
```

## Explorer

```
Which node would you like to explore (enter position or "exit"): 6
Node's content: Does the car typically require expensive repairs?
Ancestor: Is the car in good working condition?
Descendant: Purchase a car
Sibling: Is the monthly payment for the new car, plus the monthly payment of your current car, within your monthly budget?
```

Invalid positions print `Invalid input. Please try again.`, and `exit` prints `Goodbye!`.
