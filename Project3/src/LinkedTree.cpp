/*
 * Authored by Ngoc Viet Nguyen
 * Implements LinkedTree: linking nodes, finding by position, relatives, and cleanup.
 */

#include "LinkedTree.h"
using namespace std;

// Returns nullptr if the tree already has a root.
TreeNode* LinkedTree::addRoot(int position, const string& content) {
    if (root != nullptr) return nullptr;

    root = new TreeNode(position, 0, "", content, nullptr);
    return root;
}

// Adds the new node as the last child of parent.
TreeNode* LinkedTree::addChild(TreeNode* parent, int position, const string& edgeLabel, const string& content) {
    if (parent == nullptr) return nullptr;

    TreeNode* child = new TreeNode(position, parent->level + 1, edgeLabel, content, parent);
    parent->children.push_back(child);
    return child;
}

// Positions are unique, so the first match is the only match.
const TreeNode* LinkedTree::findByPosition(int position) const {
    return findInSubtree(root, position);
}

// The parent is the one ancestor reported; the root has none.
const TreeNode* LinkedTree::getAncestor(const TreeNode* node) const {
    if (node == nullptr) return nullptr;
    return node->parent;
}

// The first child is the one descendant reported; a leaf has none.
const TreeNode* LinkedTree::getDescendant(const TreeNode* node) const {
    if (node == nullptr || node->children.empty()) return nullptr;
    return node->children[0];
}

// The first other child of the parent is the one sibling reported; the root has none.
const TreeNode* LinkedTree::getSibling(const TreeNode* node) const {
    if (node == nullptr || node->parent == nullptr) return nullptr;

    for (const TreeNode* other : node->parent->children) {
        if (other != node) return other;
    }
    return nullptr;
}

// Preorder search: check the node, then each child subtree.
const TreeNode* LinkedTree::findInSubtree(const TreeNode* node, int position) {
    if (node == nullptr) return nullptr;
    if (node->position == position) return node;

    for (const TreeNode* child : node->children) {
        const TreeNode* found = findInSubtree(child, position);
        if (found != nullptr) return found;
    }
    return nullptr;
}

// Frees the children first, then the node.
void LinkedTree::deleteSubtree(TreeNode* node) {
    if (node == nullptr) return;

    for (TreeNode* child : node->children) {
        deleteSubtree(child);
    }
    delete node;
}
