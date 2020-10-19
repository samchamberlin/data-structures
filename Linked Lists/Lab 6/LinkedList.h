#pragma once
#include <string>
#include "LinkedListInterface.h"
#include <sstream>
#include <stdexcept>

using namespace std;

template<typename T>
class LinkedList : public LinkedListInterface<T>{

public:
    
    class Node {
    public:
        T value;
        Node *next;
        
        Node(T valor) {
            value = valor;
            next = NULL;
        }
    };

    LinkedList(void) {
        head = tail = NULL;
        list_size = 0;
    }
    
    ~LinkedList(void) {}

    /*
     insertHead
     
     A node with the given value should be inserted at the beginning of the list.
     
     Do not allow duplicate values in the list.
     */
    void insertHead(T value){
        Node *temp = head;
        
        while (temp != NULL)
        {
            if (temp->value == value) // has a duplicate
            {
                return;
            }
            
            temp = temp->next;
        }
        
        Node* n = new Node(value);
        n->next = head;
        head = n;
        list_size++;
    }

    /*
     insertTail
     
     A node with the given value should be inserted at the end of the list.
     
     Do not allow duplicate values in the list.
     */
    void insertTail(T value){
        if (list_size > 0)
        {
            Node *temp = head;
            
            while (temp != NULL)
            {
                if (temp->value == value) // has a duplicate
                {
                    return;
                }
                
                temp = temp->next;
            }
            
            Node* n = head;
            
            while (n->next != NULL)
            {
                n = n->next;
            }
            
            n->next = new Node(value);
            list_size++;
        }
        else
        {
            insertHead(value);
        }
    }

    /*
     insertAfter
     
     A node with the given value should be inserted immediately after the
     node whose value is equal to insertionNode.
     
     A node should only be added if the node whose value is equal to
     insertionNode is in the list. Do not allow duplicate values in the list.
     */
    void insertAfter(T value, T insertionNode){
        Node *temp = head;
        
        while (temp != NULL)
        {
            if (temp->value == value) // has a duplicate
            {
                return;
            }
            
            temp = temp->next;
        }
        
        temp = head;
        
        while (temp->value != insertionNode) //??
        {
            temp = temp->next;
            
            if(temp == NULL)
            {
                return;
            }
        }
        
        Node *temp2 = temp->next;
        
        Node *new_node = new Node(value);
        
        temp->next = new_node;
        
        new_node->next = temp2;
        
        list_size++;
    }

    /*
     remove
     
     The node with the given value should be removed from the list.
     
     The list may or may not include a node with the given value.
     */
    void remove(T value){
        Node *cur = head;
        
        Node *delete_me = head;
        
        if (list_size == 0)
        {
            return;
        }
        
        if (head->value == value) //removing the head
        {
            head = cur->next;
            delete cur;
            list_size--;
            return;
        }
        
        while (cur->next != NULL)
        {
            if (cur->next->value == value)
            {
                delete_me = cur->next;
                cur->next = delete_me->next;
                delete_me->next = NULL;
                delete delete_me;
                list_size--;
                return;
            }
            
            cur = cur->next;
        }
    }

    /*
     clear
     
     Remove all nodes from the list.
     */
    void clear(){
        while (size() > 0)
        {
            Node *n = head;
            head = head->next;
            delete n;
            list_size--;
        }
        head = NULL;
    }

    /*
     at
     
     Returns the value of the node at the given index. The list begins at
     index 0.
     
     If the given index is out of range of the list, throw an out of range exception.
     */
    T at(int index){
        if (index >= size() || index < 0)
        {
            cout << "Out of range..." << endl;
//            return NULL;
            throw out_of_range("Out of range");
        }
        Node *n = head;
        
        for (int i = 0; i < index; i++) {
            n = n->next;
        }
        
        return n->value;
    }
        

    /*
     size
     
     Returns the number of nodes in the list.
     */
    int size(){
        return list_size;
    }

    /*
     toString
     
     Returns a string representation of the list, with the value of each node listed in order (Starting from the head) and separated by a single space
     There should be no trailing space at the end of the string
     
     For example, a LinkedList containing the value 1, 2, 3, 4, and 5 should return
     "1 2 3 4 5"
     */
    string toString(){
        Node* temp = head;
        
        stringstream ss;
        
        while (temp != NULL)
        {
            ss << temp->value;
            
            if(temp->next != NULL)
            {
                ss << " ";
            }
            
            temp = temp->next;
        }
        
        return ss.str();
    }
    
private:
    
    Node *head, *tail;
    int list_size;
    
};
