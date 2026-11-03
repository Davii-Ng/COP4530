/*
 * Authored by Minh Duong Nguyen
 * Writes the tree drawing, tree properties, and binary analysis to about_tree.txt.
 */

#include "TreeReport.h"
#include <fstream>
#include "TreeAnalyzer.h"
using namespace std;

static const char* yesNo(bool value) {
    return value ? "Yes" : "No";
}

// The root has no edge label, so it is printed without brackets.
static void writeTreeDrawing(ostream& out, const TreeNode* node) {
    out << string(2 * node->level, '-');
    if (node->parent != nullptr) out << "[" << node->edgeLabel << "] ";
    out << node->content << "\n";

    for (const TreeNode* child : node->children) {
        writeTreeDrawing(out, child);
    }
}

static void writeNodeList(ostream& out, const string& title, const vector<const TreeNode*>& nodes) {
    out << title << ":\n";
    for (const TreeNode* node : nodes) {
        out << "  " << node->content << "\n";
    }
}

static void writeProperties(ostream& out, const LinkedTree& tree) {
    out << "Root: " << tree.getRoot()->content << "\n";
    out << "Internal nodes: " << countInternalNodes(tree) << "\n";
    out << "External nodes: " << countExternalNodes(tree) << "\n";
    out << "Height: " << treeHeight(tree) << "\n";
    writeNodeList(out, "Internal nodes in preorder", internalNodesPreorder(tree));
    writeNodeList(out, "External nodes in preorder", externalNodesPreorder(tree));
}

// Proper, perfect and balanced only make sense for a binary tree, so they are skipped otherwise.
static void writeBinaryAnalysis(ostream& out, const LinkedTree& tree) {
    bool binary = isBinary(tree);
    out << "Binary Tree: " << yesNo(binary) << "\n";
    if (!binary) return;

    out << "Proper: " << yesNo(isProper(tree)) << "\n";
    out << "Perfect: " << yesNo(isPerfect(tree)) << "\n";
    out << "Balanced: " << yesNo(isBalanced(tree)) << "\n";
}

bool writeReport(const LinkedTree& tree, const string& outputPath) {
    ofstream out(outputPath);
    if (!out) return false;

    writeTreeDrawing(out, tree.getRoot());
    out << "\n";
    writeProperties(out, tree);
    out << "\n";
    writeBinaryAnalysis(out, tree);
    return out.good();
}
