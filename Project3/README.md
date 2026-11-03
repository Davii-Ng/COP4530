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

Requires a C++11 or newer compiler (tested with `g++ -std=c++17` and `-std=c++11`). On the cluster, load or use `g++` and run the same commands from the project folder.

```
g++ -std=c++17 -Wall -Wextra main.cpp src/*.cpp -o decision_tree
./decision_tree data/tree-car-2.txt
```

On Windows PowerShell, run `.\decision_tree.exe data\tree-car-2.txt`.

The program takes exactly one argument, the tree file. `about_tree.txt` is written to the current directory, then the explorer prompt starts.

## Input Format

The first line is the root. Every other line has four fields separated by tabs (spaces also work):

```
level  position  edge-label  content
```

- `level`: depth of the node, root is 0.
- `position`: preorder position, 1 to the number of nodes, each used once.
- `edge-label`: label on the edge from the parent, such as `Yes` or `No`.
- `content`: text of the node.

The root line may be content only, or `0 1 content`. Example:

```
0 1 Do you currently own a car?
1 2 Yes Is the car in good working condition?
```

An invalid file prints `Error: <file>: line N: <reason>` and exits with code 1.

## Output File

`about_tree.txt` has three sections:

1. Tree drawing: `2 x level` dashes, then `[edge label]` and content.
2. Tree properties: root node, number of internal and external nodes, tree height (edges from root to deepest leaf), and both node lists in preorder.
3. Binary tree analysis: `Binary Tree: Yes/No`. Only when Yes, also `Proper Tree`, `Perfect Tree` and `Balanced Tree`.

```
Are you nervous?
--[Yes] Savings account
--[No] Will you need to access most of the money within the next 5 years?
...

Root node: Are you nervous?
Number of internal nodes: 3
Number of external nodes: 4
Tree height: 3
...

Binary Tree: Yes
Proper Tree: Yes
Perfect Tree: No
Balanced Tree: No
```

## Testing

1. Build, then run each sample file: `data/tree-car-2.txt` (not binary, one node has 3 children) and `data/tree-investment-2.txt` (binary, proper, not perfect, not balanced).
2. Open `about_tree.txt` and check the drawing, counts, height and lists by hand.
3. In the explorer, try a root (`1`, ancestor is `None`), a leaf (descendant is `None`), a middle node, then bad input (`abc`, `99`, `-1`, `6x`, empty line) and `exit`.
4. Try error cases: no argument, missing file, a file whose levels skip a parent, and duplicate positions.

Piped example: `printf '6\n1\nabc\nexit\n' | ./decision_tree data/tree-car-2.txt`

## Explorer

```
Which node would you like to explore (enter position or "exit"): 6
Node's content: Does the car typically require expensive repairs?
Ancestor: Is the car in good working condition?
Descendant: Purchase a car
Sibling: Is the monthly payment for the new car, plus the monthly payment of your current car, within your monthly budget?
```

Invalid positions print `Invalid input. Please try again.`, and `exit` prints `Goodbye!`.
