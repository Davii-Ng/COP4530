/*
 * Authored by Ngoc Viet Nguyen
 * Declares TreeNode and the LinkedTree class for a general linked tree.
 */

#ifndef LINKED_TREE_H
#define LINKED_TREE_H

#include <string>
#include <vector>
using namespace std;

// One node of the tree, linked to its parent and children.
struct TreeNode {
    int position;
    int level;
    string edgeLabel;
    string content;
    TreeNode* parent;
    vector<TreeNode*> children;

    TreeNode(int position, int level, const string& edgeLabel, const string& content, TreeNode* parent)
        : position(position), level(level), edgeLabel(edgeLabel), content(content), parent(parent) {}
};

// General tree made of linked nodes. It owns and frees every node.
class LinkedTree {
public:
    LinkedTree() : root(nullptr) {}
    ~LinkedTree() { deleteSubtree(root); }

    // Copying would free the same nodes twice.
    LinkedTree(const LinkedTree&) = delete;
    LinkedTree& operator=(const LinkedTree&) = delete;

    TreeNode* addRoot(int position, const string& content);
    TreeNode* addChild(TreeNode* parent, int position, const string& edgeLabel, const string& content);

    const TreeNode* getRoot() const { return root; }

    // Each returns nullptr if there is no such node.
    const TreeNode* findByPosition(int position) const;
    const TreeNode* getAncestor(const TreeNode* node) const;
    const TreeNode* getDescendant(const TreeNode* node) const;
    const TreeNode* getSibling(const TreeNode* node) const;

    static bool isInternal(const TreeNode* node) { return !node->children.empty(); }

private:
    TreeNode* root;

    static const TreeNode* findInSubtree(const TreeNode* node, int position);
    static void deleteSubtree(TreeNode* node);
};

#endif
