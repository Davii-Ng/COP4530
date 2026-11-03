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

    // TODO: writeReport(tree, "about_tree.txt"); print an error and return 1 if it fails.
    // TODO: runExplorer(tree);

    return 0;
}
