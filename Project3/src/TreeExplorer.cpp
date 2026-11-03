/*
 * Authored by Minh Duong Nguyen
 * Runs the console loop that shows a node's content and its relatives.
 */

#include "TreeExplorer.h"
#include <iostream>
using namespace std;

// stoi alone accepts trailing text such as "6x", so the whole input must be consumed.
static bool parsePosition(const string& input, int& position) {
    try {
        size_t used = 0;
        position = stoi(input, &used);
        return used == input.size();
    } catch (const exception&) {
        return false;
    }
}

static void printRelative(const string& label, const TreeNode* relative) {
    cout << label << ": " << (relative != nullptr ? relative->content : "None") << "\n";
}

static void showNode(const LinkedTree& tree, const TreeNode* node) {
    cout << "Node's content: " << node->content << "\n";
    printRelative("Ancestor", tree.getAncestor(node));
    printRelative("Descendant", tree.getDescendant(node));
    printRelative("Sibling", tree.getSibling(node));
}

void runExplorer(const LinkedTree& tree) {
    string input;
    while (true) {
        cout << "Which node would you like to explore (enter position or \"exit\"): ";
        if (!getline(cin, input)) break;

        if (input == "exit") break;

        int position;
        const TreeNode* node = parsePosition(input, position) ? tree.findByPosition(position) : nullptr;
        if (node == nullptr) {
            cout << "Invalid input. Please try again.\n";
            continue;
        }
        showNode(tree, node);
    }
    cout << "Goodbye!\n";
}
