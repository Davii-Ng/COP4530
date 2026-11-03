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
    int position;                // preorder position from the file
    int level;                   // root is 0
    string edgeLabel;            // empty for the root
    string content;
    TreeNode* parent;            // nullptr for the root
    vector<TreeNode*> children;  // left to right

    TreeNode(int position, int level, const string& edgeLabel, const string& content, TreeNode* parent)
        : position(position), level(level), edgeLabel(edgeLabel), content(content), parent(parent) {}
};

// General tree made of linked nodes. It owns and frees every node.
class LinkedTree {
public:
    LinkedTree() : root(nullptr), nodeCount(0) {}
    ~LinkedTree() { deleteSubtree(root); }

    // Copying would free the same nodes twice.
    LinkedTree(const LinkedTree&) = delete;
    LinkedTree& operator=(const LinkedTree&) = delete;

    TreeNode* addRoot(int position, const string& content);
    TreeNode* addChild(TreeNode* parent, int position, const string& edgeLabel, const string& content);

    const TreeNode* getRoot() const { return root; }
    int size() const { return nodeCount; }
    bool isEmpty() const { return nodeCount == 0; }

    // Each returns nullptr if there is no such node.
    const TreeNode* findByPosition(int position) const;
    const TreeNode* getAncestor(const TreeNode* node) const;     // parent
    const TreeNode* getDescendant(const TreeNode* node) const;   // first child
    const TreeNode* getSibling(const TreeNode* node) const;      // first other child of the parent

    static bool isExternal(const TreeNode* node) { return node->children.empty(); }
    static bool isInternal(const TreeNode* node) { return !node->children.empty(); }

private:
    TreeNode* root;
    int nodeCount;

    static const TreeNode* findInSubtree(const TreeNode* node, int position);
    static void deleteSubtree(TreeNode* node);
};

#endif
