#include "AVL.h"

bool AVL::findValue(Node* currentRoot, int value){
    
    if(currentRoot == nullptr){
        return false;
    }
    
    //check value with root and recurse left or right if neccessary
    if(currentRoot->data == value){
        return true;
    } else if(currentRoot->data > value){
        return findValue(currentRoot->childLeft, value);
    } else{
        return findValue(currentRoot->childRight, value);
    }
    
}

NodeInterface* AVL::getRootNode() const{
    return root;
}

bool AVL::addValue(Node*& currentRoot, int value){
    
    //check to see if currentRoot is empty
    if(currentRoot == nullptr){
        currentRoot = new Node(value, nullptr, nullptr, 0, 0);
        balance(currentRoot);
        return true;
    }
    
    //recurse left or right if necessary
    if(currentRoot->data > value){
        addValue(currentRoot->childLeft, value);
        balance(currentRoot);
        return true;
    } else if(currentRoot->data < value){
        addValue(currentRoot->childRight, value);
        balance(currentRoot);
        return true;
    } else {
        balance(currentRoot);
        return false;
    }
    
}

bool AVL::add(int data){
    
    //check for duplicates
    if(findValue(root, data)){
        return false;
    }
    
    return addValue(root, data);
}

void AVL::replaceParent(Node*& parent, Node*& child){
    
    //check for the largest value on the left side of parent
    if(child->childRight == nullptr){
        parent->data = child->data;
        parent = child;
        child = child->childLeft;
    } else{
        replaceParent(parent, child->childRight);
        balance(child);
    }
}

bool AVL::removeValue(Node*& currentRoot, int value){
    
    //checks if the value was not in the tree
    if(currentRoot == nullptr){
        return false;
    }
    
    //recurse left or right if necessary
    if(currentRoot->data > value){
        bool results = removeValue(currentRoot->childLeft, value);
        balance(currentRoot);
        return results;
    } else if(currentRoot->data < value){
        bool results = removeValue(currentRoot->childRight, value);
        balance(currentRoot);
        return results;
    } else {
        Node* parent = currentRoot;
        if(currentRoot->childLeft == nullptr){
            currentRoot = currentRoot->childRight;
        } else if(currentRoot->childRight == nullptr){
            currentRoot = currentRoot->childLeft;
        } else{
            replaceParent(parent, parent->childLeft);
            balance(currentRoot->childLeft);
        }
        balance(currentRoot);
        delete parent;
        return true;
    }
}

bool AVL::remove(int data){
    
    //check to see if the value is in the tree
    if(!findValue(root, data)){
        return false;
    }
    
    return removeValue(root, data);
    
    //FIXME: Still need to rebalance the tree
}

void AVL::clearNode(Node*& currentNode){
    if (currentNode != NULL){
        clearNode(currentNode->childLeft);
        clearNode(currentNode->childRight);
        delete currentNode;
    }
}

void AVL::clear(){
    clearNode(root);
    root = NULL;
}

//New AVL Functions
int AVL::getBalance(Node*& currentRoot){

    int leftHeight = 0;
    int rightHeight = 0;
    
    if(currentRoot->childLeft != nullptr){
        leftHeight = currentRoot->childLeft->getHeight();
    }
    
    if(currentRoot->childRight != nullptr){
        rightHeight = currentRoot->childRight->getHeight();
    }
    
    return leftHeight - rightHeight;
}

void AVL::balance(Node*& currentRoot){
    
    if(currentRoot == nullptr){
        return;
    }

    int currentBalance = getBalance(currentRoot);
    if(currentBalance > 1){ //Left Imbalanced
        balanceToRight(currentRoot);
    }
    if(currentBalance < -1){ //Right Imbalanced
        balanceToLeft(currentRoot);
    }
}

void AVL::balanceToRight(Node*& currentRoot){
    if(getBalance(currentRoot->childLeft) < 0){ //left-right case
        rotateLeft(currentRoot->childLeft);
    }
    rotateRight(currentRoot); //left-left case
}

void AVL::balanceToLeft(Node*& currentRoot){
    if(getBalance(currentRoot->childRight) > 0){ //right-left case
        rotateRight(currentRoot->childRight);
    }
    rotateLeft(currentRoot); //right-right case
}

void AVL::rotateRight(Node*& currentRoot){
    Node* newRoot = currentRoot->childLeft;
    currentRoot->childLeft = newRoot->childRight;
    newRoot->childRight = currentRoot;
    currentRoot = newRoot;
}

void AVL::rotateLeft(Node*& currentRoot){
    Node* newRoot = currentRoot->childRight;
    currentRoot->childRight = newRoot->childLeft;
    newRoot->childLeft = currentRoot;
    currentRoot = newRoot;
}
