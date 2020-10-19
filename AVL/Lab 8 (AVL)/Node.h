#pragma once

#include "NodeInterface.h"
#include <stdio.h>
#include <iostream>

using namespace std;

class Node : public NodeInterface{

    friend class AVL;
    
private:
    
    int data;
    int leftHeight;
    int rightHeight;
    Node* childLeft;
    Node* childRight;
    
public:
    
    Node(int dataIn, Node* childLeftIn, Node* childRightIn, int leftHeightIn, int rightHeightIn);
    ~Node();
    
    int getData() const;
    Node* getLeftChild() const;
    Node* getRightChild() const;
    int getHeight();
};

