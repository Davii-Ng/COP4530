#include <iostream>
#include <string>

using namespace std;

// Represents a circular doubly linked list of strings.
class CircularLinkedList {
private:

    // Represents one node in the circular linked list.
    // Each node stores a string value and pointers to both
    // the next and previous nodes.
    struct Node {
        string value;
        Node* next;
        Node* prev;

        // Constructs a node with the given value.
        // The next and previous pointers are initialized to nullptr
        // until the node is connected to the list.
        Node(string newValue) {
            value = newValue;
            next = nullptr;
            prev = nullptr;
        }
    };

    // Points to the first node in the list.
    Node* head;

    // Points to the current node in the list.
    // For the music player project, this represents the current song.
    Node* cursor;

    // Stores the number of nodes currently in the list.
    int count;

public:

    // Constructs an empty circular linked list.
    CircularLinkedList() {
        head = nullptr;
        cursor = nullptr;
        count = 0;
    }

    // Destructor that deletes every node in the list
    // and releases dynamically allocated memory.
    ~CircularLinkedList() {

        // If the list is already empty, there is nothing to delete.
        if (head == nullptr) {
            return;
        }

        // Start with the node immediately after the head.
        Node* currentNode = head->next;

        // Delete each node until the traversal returns to the head.
        while (currentNode != head) {
            Node* nodeToDelete = currentNode;
            currentNode = currentNode->next;

            delete nodeToDelete;
        }

        // Delete the head node last.
        delete head;

        // Reset the list's data members.
        head = nullptr;
        cursor = nullptr;
        count = 0;
    }

    // Inserts a new node containing the given value
    // at the end of the circular linked list.
    void insertEnd(string value) {

        Node* newNode = new Node(value);

        // If the list is empty, the new node becomes both
        // the head and the current node.
        if (head == nullptr) {
            head = newNode;
            cursor = newNode;

            // A one-node circular list points to itself
            // in both directions.
            newNode->next = head;
            newNode->prev = head;

            count++;
            return;
        }

        // Traverse the list until the last node is found.
        Node* currentNode = head;

        while (currentNode->next != head) {
            currentNode = currentNode->next;
        }

        // Connect the previous last node to the new node.
        currentNode->next = newNode;

        // Connect the new node back to the head and previous node.
        newNode->next = head;
        newNode->prev = currentNode;

        // Update the head's previous pointer so that it points
        // to the new last node.
        head->prev = newNode;

        count++;
    }

    // Prints the value stored in every node exactly once,
    // beginning at the head of the circular linked list.
    void printValues() {

        // Nothing is printed if the list is empty.
        if (head == nullptr) {
            return;
        }

        Node* currentNode = head;

        // A do-while loop is used because the list is circular
        // and each node should be visited once before returning to head.
        do {
            cout << currentNode->value << endl;
            currentNode = currentNode->next;

        } while (currentNode != head);
    }
};

