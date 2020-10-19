#include "Node.h"

Node::Node(int dataIn, Node* childLeftIn, Node* childRightIn, int leftHeightIn, int rightHeightIn){
    data = dataIn;
    childLeft = childLeftIn;
    childRight = childRightIn;
    leftHeight = leftHeightIn;
    rightHeight = rightHeightIn;
}

Node::~Node(){
    
}

//Returns the data that is stored in this node
int Node::getData() const{
    return this->data;
}

//Returns the left child of this node or null if it doesn't have one.
Node* Node::getLeftChild() const{
    return this->childLeft;
}

//Returns the right child of this node or null if it doesn't have one.
Node* Node::getRightChild() const{
    return this->childRight;
}

//Returns the height of any node
int Node::getHeight(){
    
    if(childLeft == nullptr && childRight == nullptr){
        return 1;
    } else if(childRight == nullptr){
        return childLeft->getHeight() + 1;
    } else if(childLeft == nullptr){
        return childRight->getHeight() + 1;
    } else{
        if(childLeft->getHeight() > childRight->getHeight()){
            return childLeft->getHeight() + 1;
        } else{
            return childRight->getHeight() + 1;
        }
    }
}
