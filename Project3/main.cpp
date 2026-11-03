/*
 * Authored by Minh Duong Nguyen & Ngoc Viet Nguyen
 * Loads the tree file, writes about_tree.txt, then starts the console explorer.
 */

#include <iostream>
#include "src/LinkedTree.h"
#include "src/TreeParser.h"
#include "src/TreeReport.h"
#include "src/TreeExplorer.h"
using namespace std;

// Builds the tree from the file argument, writes the report, then starts the explorer.
// Returns 1 if the arguments, the tree file or the report output are bad.
int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <tree-file>\n";
        return 1;
    }

    LinkedTree tree;
    string error;
    if (!buildTreeFromFile(argv[1], tree, error)) {
        cout << "Error: " << argv[1] << ": " << error << "\n";
        return 1;
    }

    if (!writeReport(tree, "about_tree.txt")) {
        cout << "Error: could not write about_tree.txt\n";
        return 1;
    }
    runExplorer(tree);

    return 0;
}
