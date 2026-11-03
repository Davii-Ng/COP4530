/*
 * Authored by Minh Duong Nguyen
 * Declares writeReport for generating about_tree.txt.
 */

#ifndef TREE_REPORT_H
#define TREE_REPORT_H

#include <string>
#include "LinkedTree.h"
using namespace std;

// Returns false if the output file cannot be written.
bool writeReport(const LinkedTree& tree, const string& outputPath);

#endif
