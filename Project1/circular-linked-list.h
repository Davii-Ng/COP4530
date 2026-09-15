#ifndef CIRCULAR_LIST_H
#define CIRCULAR_LIST_H

#include <vector>

using namespace std;

// Represents a generic doubly-linked circular list.
// The template type T allows the list to store different data types.
template <typename T>
class CircularList {
private:

    // Represents one node in the circular linked list.
    // Each node stores a value and pointers to both
    // the next and previous nodes.
    struct Node {
        T value;
        Node* next;
        Node* prev;

        // Constructs a node with the given value.
        Node(const T& newValue) {
            value = newValue;
            next = nullptr;
            prev = nullptr;
        }
    };

    // Points to the first node in the list.
    Node* head;

    // Points to the current node in the list.
    // In the music player, this represents the currently playing song.
    Node* cursor;

    // Stores the number of nodes currently in the list.
    int count;

public:

    // Constructs an empty circular linked list.
    CircularList() {
        head = nullptr;
        cursor = nullptr;
        count = 0;
    }

    // Deletes all dynamically allocated nodes in the list.
    ~CircularList() {

        // If the list is empty, there is nothing to delete.
        if (head == nullptr) {
            return;
        }

        // Begin with the node after head.
        Node* currentNode = head->next;

        // Delete each node until returning to head.
        while (currentNode != head) {
            Node* nodeToDelete = currentNode;

            currentNode = currentNode->next;

            delete nodeToDelete;
        }

        // Delete the head node last.
        delete head;

        head = nullptr;
        cursor = nullptr;
        count = 0;
    }

    // Disable copying because copying the node pointers directly
    // would create multiple lists pointing to the same nodes.
    CircularList(const CircularList&) = delete;
    CircularList& operator=(const CircularList&) = delete;

    // Adds a new value to the end of the circular linked list.
    void add(const T& value) {

        Node* newNode = new Node(value);

        // Handle an empty list.
        if (head == nullptr) {
            head = newNode;
            cursor = newNode;

            // A one-node circular list points to itself.
            newNode->next = head;
            newNode->prev = head;

            count++;
            return;
        }

        // The node before head is always the last node.
        Node* lastNode = head->prev;

        // Connect the previous last node to the new node.
        lastNode->next = newNode;

        // Connect the new node to the last node and head.
        newNode->prev = lastNode;
        newNode->next = head;

        // Update head's previous pointer.
        head->prev = newNode;

        count++;
    }

    // Inserts a new value immediately after the current cursor position.
    void insertAfterCurrent(const T& value) {

        // If the list is empty, add the first node normally.
        if (head == nullptr) {
            add(value);
            return;
        }

        Node* newNode = new Node(value);

        // Store the node that currently comes after the cursor.
        Node* nextNode = cursor->next;

        // Connect cursor to the new node.
        cursor->next = newNode;
        newNode->prev = cursor;

        // Connect the new node to the following node.
        newNode->next = nextNode;
        nextNode->prev = newNode;

        count++;
    }

    // Removes the node currently pointed to by cursor.
    // After removal, cursor moves to the next node.
    void removeCurrent() {

        // Nothing to remove if the list is empty.
        if (cursor == nullptr) {
            return;
        }

        // Special case: only one node exists.
        if (count == 1) {
            delete cursor;

            head = nullptr;
            cursor = nullptr;
            count = 0;

            return;
        }

        Node* nodeToDelete = cursor;

        // If the current node is the head,
        // move head to the next node.
        if (cursor == head) {
            head = cursor->next;
        }

        // Connect the nodes on each side of cursor.
        cursor->prev->next = cursor->next;
        cursor->next->prev = cursor->prev;

        // Move cursor to the next node.
        cursor = cursor->next;

        delete nodeToDelete;

        count--;
    }

    // Moves the cursor one position forward or backward.
    // direction = 1 moves forward.
    // direction = -1 moves backward.
    void advance(int direction) {

        // If the list is empty, the cursor cannot move.
        if (cursor == nullptr) {
            return;
        }

        if (direction == 1) {
            cursor = cursor->next;
        }
        else if (direction == -1) {
            cursor = cursor->prev;
        }
    }

    // Moves the cursor to the node at the given zero-based index.
    void jumpTo(int index) {

        // Ignore invalid indexes.
        if (index < 0 || index >= count) {
            return;
        }

        cursor = head;

        // Move forward until the requested index is reached.
        for (int i = 0; i < index; i++) {
            cursor = cursor->next;
        }
    }

    // Returns a reference to the value at the current cursor position.
    T& current() {
        return cursor->value;
    }

    // Returns the zero-based index of the cursor,
    // counting from the head node.
    int currentIndex() const {

        // An empty list has no valid current index.
        if (head == nullptr) {
            return -1;
        }

        int index = 0;
        Node* currentNode = head;

        // Move through the list until cursor is found.
        while (currentNode != cursor) {
            currentNode = currentNode->next;
            index++;
        }

        return index;
    }

    // Returns all list values in a vector,
    // starting from head and going around the list once.
    vector<T> toVector() const {

        vector<T> values;

        // Return an empty vector if the list is empty.
        if (head == nullptr) {
            return values;
        }

        Node* currentNode = head;

        do {
            values.push_back(currentNode->value);
            currentNode = currentNode->next;

        } while (currentNode != head);

        return values;
    }

    // Replaces the values stored in the nodes with the
    // values from the provided vector.
    // The node connections themselves are not changed.
    void reorder(const vector<T>& values) {

        // The vector must contain exactly one value for each node.
        if (values.size() != static_cast<size_t>(count)) {
            return;
        }

        if (head == nullptr) {
            return;
        }

        Node* currentNode = head;

        // Copy each vector value into the corresponding node.
        for (int i = 0; i < count; i++) {
            currentNode->value = values[i];
            currentNode = currentNode->next;
        }
    }

    // Returns the number of nodes currently stored in the list.
    int size() const {
        return count;
    }

    // Returns true if the list contains no nodes.
    bool isEmpty() const {
        return head == nullptr;
    }

    // Prints every value in the list once, starting from head.
    // This method is useful for testing the list.
    void printValues() const {

        if (head == nullptr) {
            return;
        }

        Node* currentNode = head;

        do {
            cout << currentNode->value << endl;
            currentNode = currentNode->next;

        } while (currentNode != head);
    }
};

#endif

