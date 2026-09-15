#include <iostream>
#include <string>

using namespace std; 

struct Node{
    string val;
    Node* next;

    Node(string value){
        val = value;
        next = nullptr;
    }
};


class CircularLinkedList{
    private:
        Node* head;

    public:
        CircularLinkedList(){
            head = nullptr;
        }

        ~CircularLinkedList(){
            if(head == nullptr){
                return;
           } 
            Node* curr_ptr = head->next;
            
            while(curr_ptr != head){
                Node* temp = curr_ptr;
                curr_ptr = curr_ptr->next;
                delete temp;
            }

            delete head;
            return;
        }
        
        void InsertEnd(string value){
            Node* new_node = new Node(value);
            
            if (head == nullptr){
                head = new_node;
                new_node->next = head;
                return;
            }

            Node* temp = head;
            
            while(temp->next != head){
                temp = temp->next;
            }

            temp->next = new_node;
            new_node->next = head;
            return;
        }

        void PrintVal(){
            if (head == nullptr){
                return;
            }
            Node* temp = head;
            do{
                temp =  temp->next;
                cout << temp->val<< endl;
            }while(temp->next != head);
        }
        

};

