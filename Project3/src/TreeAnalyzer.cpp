/*
 * Authored by Ngoc Viet Nguyen
 * Computes node counts, height, preorder lists, and binary tree checks.
 */

#include "TreeAnalyzer.h"
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
        int height = subtreeHeight(child);
        if (height > tallest) tallest = height;
    }
    return tallest + 1;
}

static bool isBinarySubtree(const TreeNode* node) {
    if (node->children.size() > 2) return false;

    for (const TreeNode* child : node->children) {
        if (!isBinarySubtree(child)) return false;
    }
    return true;
}

static bool isProperSubtree(const TreeNode* node) {
    if (node->children.size() == 1 || node->children.size() > 2) return false;

    for (const TreeNode* child : node->children) {
        if (!isProperSubtree(child)) return false;
    }
    return true;
}

static bool allLeavesAtDepth(const TreeNode* node, int depth, int leafDepth) {
    if (node->children.empty()) return depth == leafDepth;

    for (const TreeNode* child : node->children) {
        if (!allLeavesAtDepth(child, depth + 1, leafDepth)) return false;
    }
    return true;
}

// Assumes a binary tree. A missing child counts as height -1.
static bool isBalancedSubtree(const TreeNode* node) {
    if (node == nullptr) return true;

    const TreeNode* left = node->children.size() > 0 ? node->children[0] : nullptr;
    const TreeNode* right = node->children.size() > 1 ? node->children[1] : nullptr;
    int difference = subtreeHeight(left) - subtreeHeight(right);
    if (difference > 1 || difference < -1) return false;

    return isBalancedSubtree(left) && isBalancedSubtree(right);
}

int countInternalNodes(const LinkedTree& tree) {
    return internalNodesPreorder(tree).size();
}

int countExternalNodes(const LinkedTree& tree) {
    return externalNodesPreorder(tree).size();
}

int treeHeight(const LinkedTree& tree) {
    return subtreeHeight(tree.getRoot());
}

vector<const TreeNode*> internalNodesPreorder(const LinkedTree& tree) {
    vector<const TreeNode*> result;
    collectPreorder(tree.getRoot(), true, result);
    return result;
}

vector<const TreeNode*> externalNodesPreorder(const LinkedTree& tree) {
    vector<const TreeNode*> result;
    collectPreorder(tree.getRoot(), false, result);
    return result;
}

bool isBinary(const LinkedTree& tree) {
    return tree.getRoot() == nullptr || isBinarySubtree(tree.getRoot());
}

bool isProper(const LinkedTree& tree) {
    return tree.getRoot() == nullptr || isProperSubtree(tree.getRoot());
}

bool isPerfect(const LinkedTree& tree) {
    return isProper(tree) && (tree.getRoot() == nullptr || allLeavesAtDepth(tree.getRoot(), 0, treeHeight(tree)));
}

bool isBalanced(const LinkedTree& tree) {
    return isBinary(tree) && isBalancedSubtree(tree.getRoot());
}
