/*
 * Authored by Ngoc Viet Nguyen
 * Declares buildTreeFromFile for reading a tree file into a LinkedTree.
 */

#ifndef TREE_PARSER_H
#define TREE_PARSER_H

#include <string>
#include "LinkedTree.h"
using namespace std;

// Each line is "level position edge-label content", split by tabs or spaces.
// The root line may be content only. Returns false and sets error if the file is missing or invalid.
bool buildTreeFromFile(const string& path, LinkedTree& tree, string& error);

#endif
