#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int d) : data(d), next(nullptr) {}
};

// Recursively reverse the list, return the new head
Node* reverseRecursive(Node* head) {
    if (head == nullptr || head->next == nullptr)   // base case
        return head;

    Node* newHead = reverseRecursive(head->next);   // reverse the rest

    head->next->next = head;   // successor now points back to head
    head->next = nullptr;      // head becomes the tail

    return newHead;            // same new head bubbles up
}

void printList(Node* head) {
    for (Node* cur = head; cur != nullptr; cur = cur->next)
        cout << cur->data << " ";
    cout << "\n";
}

int main() {
    // Build: 1 -> 2 -> 3 -> 4 -> 5
    Node* head = new Node(1);
    head->next = new Node(2);
    head->next->next = new Node(3);
    head->next->next->next = new Node(4);
    head->next->next->next->next = new Node(5);

    cout << "Original: ";
    printList(head);

    head = reverseRecursive(head);

    cout << "Reversed: ";
    printList(head);

    return 0;
}

/*
Output:
Original: 1 2 3 4 5
Reversed: 5 4 3 2 1
*/