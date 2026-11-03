/*
 * Authored by Ngoc Viet Nguyen
 * Reads a tree file and builds the LinkedTree from its records.
 */

#include "TreeParser.h"
#include <fstream>
#include <sstream>
using namespace std;

// One line of the file, before it is linked into the tree.
struct NodeRecord {
    int level = -1;      // -1 means no line has this position yet
    int position = 0;
    string edgeLabel;
    string content;
    int lineNumber = 0;
};

// Strips leading/trailing spaces, tabs, and '\r' (Windows line endings).
static string trim(const string& s) {
    size_t start = s.find_first_not_of(" \t\r");
    size_t end = s.find_last_not_of(" \t\r");
    if (start == string::npos) return "";
    return s.substr(start, end - start + 1);
}

// True only if the whole text is an integer.
static bool toInt(const string& text, int& value) {
    istringstream in(text);
    char extra;
    return (in >> value) && !(in >> extra);
}

static bool fail(string& error, int lineNumber, const string& message) {
    error = "line " + to_string(lineNumber) + ": " + message;
    return false;
}

// Fills record from one line. Tab format keeps spaces inside fields;
// space format reads a one-word edge label, and the rest of the line is the content.
static bool parseLine(const string& line, NodeRecord& record) {
    string levelText, positionText;
    if (line.find('\t') != string::npos) {
        vector<string> fields;
        string field;
        istringstream in(line);
        while (getline(in, field, '\t')) fields.push_back(trim(field));
        if (fields.size() < 3 || fields.size() > 4) return false;

        levelText = fields[0];
        positionText = fields[1];
        if (fields.size() == 4) record.edgeLabel = fields[2];
        record.content = fields.back();
    } else {
        istringstream in(line);
        in >> levelText >> positionText;
        if (levelText != "0") in >> record.edgeLabel;
        getline(in, record.content);
        record.content = trim(record.content);
    }

    if (!toInt(levelText, record.level) || !toInt(positionText, record.position)) return false;
    if (record.level == 0) record.edgeLabel = "";
    return record.level >= 0 && record.position >= 1 && !record.content.empty()
        && (record.level == 0 || !record.edgeLabel.empty());
}

// Reads all lines, puts each record at index (position - 1) so they end up in preorder,
// then links each node to the latest node one level above it.
bool buildTreeFromFile(const string& path, LinkedTree& tree, string& error) {
    ifstream file(path);
    if (!file.is_open()) {
        error = "could not open file";
        return false;
    }

    vector<NodeRecord> records;
    string line;
    int lineNumber = 0;
    while (getline(file, line)) {
        lineNumber++;
        line = trim(line);
        if (line.empty()) continue;

        NodeRecord record;
        record.lineNumber = lineNumber;
        string firstWord;
        int unused;
        istringstream(line) >> firstWord;

        if (records.empty() && !toInt(firstWord, unused)) {
            // Root given as content only
            record.level = 0;
            record.position = 1;
            record.content = line;
        } else if (!parseLine(line, record)) {
            return fail(error, lineNumber, "expected \"level position edge-label content\"");
        }
        records.push_back(record);
    }
    if (records.empty()) {
        error = "file has no nodes";
        return false;
    }

    vector<NodeRecord> preorder(records.size());
    for (const NodeRecord& record : records) {
        int index = record.position - 1;
        if (index >= (int)preorder.size() || preorder[index].level != -1)
            return fail(error, record.lineNumber, "positions must be unique and go from 1 to " + to_string(records.size()));
        preorder[index] = record;
    }

    for (size_t i = 0; i < preorder.size(); i++) {
        const NodeRecord& record = preorder[i];
        if (i == 0 && record.level != 0) return fail(error, record.lineNumber, "position 1 must be the root (level 0)");
        if (i > 0 && record.level == 0) return fail(error, record.lineNumber, "only one root is allowed");
        if (i > 0 && record.level > preorder[i - 1].level + 1) return fail(error, record.lineNumber, "level skips a parent");
    }

    vector<TreeNode*> lastAtLevel;   // lastAtLevel[k] = latest node seen at level k
    for (const NodeRecord& record : preorder) {
        TreeNode* node;
        if (record.level == 0) {
            node = tree.addRoot(record.position, record.content);
        } else {
            node = tree.addChild(lastAtLevel[record.level - 1], record.position, record.edgeLabel, record.content);
        }
        lastAtLevel.resize(record.level);
        lastAtLevel.push_back(node);
    }
    return true;
}
