/*
 * Authored by Ngoc Viet Nguyen
 * Computes node counts, height, preorder lists, and binary tree checks.
 */

#include "TreeAnalyzer.h"
#include <algorithm>
using namespace std;

// Adds internal (or external) nodes of the subtree to result in preorder.
static void collectPreorder(const TreeNode* node, bool wantInternal, vector<const TreeNode*>& result) {
    if (node == nullptr) return;
    if (LinkedTree::isInternal(node) == wantInternal) result.push_back(node);

    for (const TreeNode* child : node->children) {
        collectPreorder(child, wantInternal, result);
    }
}

// A leaf has height 0, a missing node -1.
static int subtreeHeight(const TreeNode* node) {
    if (node == nullptr) return -1;

    int tallest = -1;
    for (const TreeNode* child : node->children) {
        tallest = max(tallest, subtreeHeight(child));
    }
    return tallest + 1;
}

// True if every node in the subtree has at most 2 children.
static bool isBinarySubtree(const TreeNode* node) {
    const vector<TreeNode*>& children = node->children;
    return children.size() <= 2 && all_of(children.begin(), children.end(), isBinarySubtree);
}

// True if every node in the subtree has 0 or 2 children.
static bool isProperSubtree(const TreeNode* node) {
    const vector<TreeNode*>& children = node->children;
    return (children.empty() || children.size() == 2) && all_of(children.begin(), children.end(), isProperSubtree);
}

// True if every leaf of the subtree sits at leafDepth; depth is the node's own depth.
static bool allLeavesAtDepth(const TreeNode* node, int depth, int leafDepth) {
    const vector<TreeNode*>& children = node->children;
    if (children.empty()) return depth == leafDepth;

    return all_of(children.begin(), children.end(),
                  [&](const TreeNode* child) { return allLeavesAtDepth(child, depth + 1, leafDepth); });
}

// Assumes a binary tree. A missing child counts as height -1.
static bool isBalancedSubtree(const TreeNode* node) {
    if (node == nullptr) return true;

    const TreeNode* left = node->children.size() > 0 ? node->children[0] : nullptr;
    const TreeNode* right = node->children.size() > 1 ? node->children[1] : nullptr;
    int leftHeight = subtreeHeight(left);
    int rightHeight = subtreeHeight(right);
    if (max(leftHeight, rightHeight) - min(leftHeight, rightHeight) > 1) return false;

    return isBalancedSubtree(left) && isBalancedSubtree(right);
}

// Counted from the preorder list so the definition of "internal" lives in one place.
int countInternalNodes(const LinkedTree& tree) {
    return internalNodesPreorder(tree).size();
}

// Counted from the preorder list, same as the internal count.
int countExternalNodes(const LinkedTree& tree) {
    return externalNodesPreorder(tree).size();
}

// Height of the root, so an empty tree gives -1 and a single node gives 0.
int treeHeight(const LinkedTree& tree) {
    return subtreeHeight(tree.getRoot());
}

// Nodes with at least one child, in preorder.
vector<const TreeNode*> internalNodesPreorder(const LinkedTree& tree) {
    vector<const TreeNode*> result;
    collectPreorder(tree.getRoot(), true, result);
    return result;
}

// Leaves (nodes with no children), in preorder.
vector<const TreeNode*> externalNodesPreorder(const LinkedTree& tree) {
    vector<const TreeNode*> result;
    collectPreorder(tree.getRoot(), false, result);
    return result;
}

// Binary: no node has more than 2 children.
bool isBinary(const LinkedTree& tree) {
    return isBinarySubtree(tree.getRoot());
}

// Proper: every node has 0 or 2 children.
bool isProper(const LinkedTree& tree) {
    return isProperSubtree(tree.getRoot());
}

// Perfect: proper, and every leaf is as deep as the tree is tall.
bool isPerfect(const LinkedTree& tree) {
    return isProper(tree) && allLeavesAtDepth(tree.getRoot(), 0, treeHeight(tree));
}

// Balanced: binary, and the two child heights differ by at most 1 at every node.
bool isBalanced(const LinkedTree& tree) {
    return isBinary(tree) && isBalancedSubtree(tree.getRoot());
}
