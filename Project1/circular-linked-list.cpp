#include <iostream>
#include <string>

using namespace std; 




class CircularLinkedList{
    private:
        struct Node{
        string val;
        Node* next;
        Node* prev;

        Node(string value){
            val = value;
            next = nullptr;
            prev = nullptr;
        }
    };

        Node* head;
        Node* cursor;
        int count;

    public:
        CircularLinkedList(){
            head = nullptr;
            cursor = nullptr;
            count = 0;
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

            head = nullptr;
            cursor = nullptr;
            count = 0;
            return;
        }
        
        void InsertEnd(string value){
            Node* new_node = new Node(value);
            
            if (head == nullptr){
                head = new_node;
                cursor = new_node;

                new_node->next = head;
                new_node->prev = head;

                count += 1;
                return;
            }

            Node* temp = head;
            
            while(temp->next != head){
                temp = temp->next;
            }
            
            
            temp->next = new_node;

            new_node->next = head;
            new_node->prev = temp;

            head->prev = new_node;

            count += 1;
            return;
        }

        void PrintVal(){
            if (head == nullptr){
                return;
            }
            Node* temp = head;
            do{
                cout << temp->val<< endl;
                temp =  temp->next;
            }while(temp != head);
        }
        

};

