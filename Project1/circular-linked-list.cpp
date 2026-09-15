#include <iostream>
#include <string>

using namespace std;

// Represents a generic circular doubly linked list.
// The template type T allows the list to store different data types.
template <typename T>
class CircularLinkedList {
private:

    // Represents one node in the circular linked list.
    // Each node stores a value of type T and pointers to both
    // the next and previous nodes in the list.
    struct Node {
        T value;
        Node* next;
        Node* prev;

        // Constructs a node with the given value.
        // The next and previous pointers are initialized to nullptr
        // until the node is connected to the circular list.
        Node(T newValue) {
            value = newValue;
            next = nullptr;
            prev = nullptr;
        }
    };

    // Points to the first node in the circular linked list.
    Node* head;

    // Points to the current node in the list.
    // In the music player, this represents the currently selected song.
    Node* cursor;

    // Stores the total number of nodes currently in the list.
    int count;

public:

    // Constructs an empty circular linked list.
    // Both pointers start as nullptr because no nodes exist yet.
    CircularLinkedList() {
        head = nullptr;
        cursor = nullptr;
        count = 0;
    }

    // Destructor that deletes every dynamically allocated node
    // and releases the memory used by the circular linked list.
    ~CircularLinkedList() {

        // If the list is empty, there is no memory to release.
        if (head == nullptr) {
            return;
        }

        // Begin at the node immediately after the head.
        Node* currentNode = head->next;

        // Continue deleting nodes until the traversal returns to head.
        while (currentNode != head) {
            Node* nodeToDelete = currentNode;

            // Move forward before deleting the current node so that
            // the next node can still be accessed safely.
            currentNode = currentNode->next;

            delete nodeToDelete;
        }

        // Delete the head node after every other node has been deleted.
        delete head;

        // Reset the data members to represent an empty list.
        head = nullptr;
        cursor = nullptr;
        count = 0;
    }

    // Inserts a new value at the end of the circular linked list.
    void insertEnd(T value) {

        // Dynamically create a new node containing the given value.
        Node* newNode = new Node(value);

        // If the list is empty, the new node becomes both
        // the first node and the current node.
        if (head == nullptr) {
            head = newNode;
            cursor = newNode;

            // A one-node circular doubly linked list points
            // back to itself in both directions.
            newNode->next = head;
            newNode->prev = head;

            count++;
            return;
        }

        // Begin at the head and search for the current last node.
        Node* currentNode = head;

        // The last node is the node whose next pointer points back to head.
        while (currentNode->next != head) {
            currentNode = currentNode->next;
        }

        // Connect the old last node to the new node.
        currentNode->next = newNode;

        // Connect the new node to the previous last node
        // and back to the head.
        newNode->prev = currentNode;
        newNode->next = head;

        // Since the list is doubly linked and circular,
        // the head's previous pointer must point to the new last node.
        head->prev = newNode;

        // Increase the number of nodes stored in the list.
        count++;
    }

    // Prints the value stored in every node exactly once,
    // starting from the head of the circular linked list.
    void printValues() {

        // If the list is empty, there are no values to print.
        if (head == nullptr) {
            return;
        }

        Node* currentNode = head;

        // Visit each node once.
        // The traversal stops when it reaches the head again.
        do {
            cout << currentNode->value << endl;
            currentNode = currentNode->next;

        } while (currentNode != head);
    }
};

