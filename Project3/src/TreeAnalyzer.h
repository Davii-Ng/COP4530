/*
 * Authored by Ngoc Viet Nguyen
 * Declares functions that compute tree properties and binary tree checks.
 */

#ifndef TREE_ANALYZER_H
#define TREE_ANALYZER_H

#include <vector>
#include "LinkedTree.h"
using namespace std;

int countInternalNodes(const LinkedTree& tree);
int countExternalNodes(const LinkedTree& tree);

// Number of edges from the root to the deepest leaf.
int treeHeight(const LinkedTree& tree);

vector<const TreeNode*> internalNodesPreorder(const LinkedTree& tree);
vector<const TreeNode*> externalNodesPreorder(const LinkedTree& tree);

bool isBinary(const LinkedTree& tree);     // every node has at most 2 children
bool isProper(const LinkedTree& tree);     // every node has 0 or 2 children
bool isPerfect(const LinkedTree& tree);    // proper, and all leaves on the same level
bool isBalanced(const LinkedTree& tree);   // binary, child heights differ by at most 1 at every node

#endif
