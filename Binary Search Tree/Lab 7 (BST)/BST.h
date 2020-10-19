#pragma once

#include "BSTInterface.h"
#include "NodeInterface.h"
#include "Node.h"
#include <iostream>

using namespace std;

class BST : public BSTInterface{
    
private:
    
    Node* root;
    bool findValue(Node* currentRoot, int value);
    bool addValue(Node*& currentRoot, int value);
    bool removeValue(Node*& currentRoot, int value);
    void replaceParent(Node*& parent, Node*& child);
    void clearNode(Node*& currentNode);
    
public:
    
    BST(){
        root = NULL;
    }
    ~BST(){
        clear();
    }
    
    NodeInterface* getRootNode() const;
    bool add(int data);
    bool remove(int data);
    void clear();
};

