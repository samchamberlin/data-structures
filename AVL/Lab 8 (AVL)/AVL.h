#pragma once
#include "AVLInterface.h"
#include "NodeInterface.h"
#include "Node.h"
#include <stdio.h>
#include <iostream>

using namespace std;

class AVL : public AVLInterface{
    
private:
    
    Node* root;
    bool findValue(Node* currentRoot, int value);
    bool addValue(Node*& currentRoot, int value);
    bool removeValue(Node*& currentRoot, int value);
    void replaceParent(Node*& parent, Node*& child);
    void clearNode(Node*& currentNode);
    //New AVL Functions
    int getBalance(Node*& currentRoot);
    void balance(Node*& currentRoot);
    void balanceToRight(Node*& currentRoot);
    void balanceToLeft(Node*& currentRoot);
    void rotateRight(Node*& currentRoot);
    void rotateLeft(Node*& currentRoot);
    
public:

    AVL(){
        root = NULL;
    }
    ~AVL(){
        clear();
    }

    NodeInterface* getRootNode() const;
    bool add(int data);
    bool remove(int data);
    void clear();
};
