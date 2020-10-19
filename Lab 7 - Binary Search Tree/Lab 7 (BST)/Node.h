#pragma once

#include "NodeInterface.h"
#include <stdio.h>
#include <iostream>

using namespace std;

class Node : public NodeInterface{

    friend class BST;
    
private:
    
    int data;
    Node* childLeft;
    Node* childRight;
    
public:
    
    Node(int dataIn, Node* childLeftIn, Node* childRightIn);
    ~Node();
    
    int getData() const;
    Node* getLeftChild() const;
    Node* getRightChild() const;
};

