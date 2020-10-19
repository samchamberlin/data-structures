#include "Node.h"

Node::Node(int dataIn, Node* childLeftIn, Node* childRightIn){
    data = dataIn;
    childLeft = childLeftIn;
    childRight = childRightIn;
}

Node::~Node(){
    
}

//Returns the data that is stored in this node
int Node::getData() const{
    return data;
}

//Returns the left child of this node or null if it doesn't have one.
Node* Node::getLeftChild() const{
    return this->childLeft;
}

//Returns the right child of this node or null if it doesn't have one.
Node* Node::getRightChild() const{
    return this->childRight;
}
