#include "BST.h"

bool BST::findValue(Node* currentRoot, int value){
    
    //check if there is a root
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

//Returns the root node for this tree
NodeInterface* BST::getRootNode() const{
    return root;
}

bool BST::addValue(Node*& currentRoot, int value){
    
    //check to see if currentRoot is empty
    if(currentRoot == nullptr){
        currentRoot = new Node(value, nullptr, nullptr);
        return true;
    }
    
    //recurse left or right if necessary
    if(currentRoot->data > value){
        return addValue(currentRoot->childLeft, value);
    } else if(currentRoot->data < value){
        return addValue(currentRoot->childRight, value);
    } else {
        return false;
    }
    
}

//Attempts to add the given int to the BST tree
bool BST::add(int data){
    
    //check for duplicates
    if(findValue(root, data)){
        return false;
    }
    
    return addValue(root, data);
}

void BST::replaceParent(Node*& parent, Node*& child){
    
    //check for the largest value on the left side of parent
    if(child->childRight == nullptr){
        parent->data = child->data;
        parent = child;
        child = child->childLeft;
    } else{
        replaceParent(parent, child->childRight);
    }
}

bool BST::removeValue(Node*& currentRoot, int value){
    
    //checks if the value was not in the tree
    if(currentRoot == nullptr){
        return false;
    }
    
    //recurse left or right if necessary
    if(currentRoot->data > value){
        return removeValue(currentRoot->childLeft, value);
    } else if(currentRoot->data < value){
        return removeValue(currentRoot->childRight, value);
    } else {
        Node* parent = currentRoot;
        if(currentRoot->childLeft == nullptr){
            currentRoot = currentRoot->childRight;
        } else if(currentRoot->childRight == nullptr){
            currentRoot = currentRoot->childLeft;
        } else{
            replaceParent(parent, parent->childLeft);
        }
        delete parent;
        return true;
    }
}

//Attempts to remove the given int from the BST tree
bool BST::remove(int data){
    
    //check to see if the value is in the tree
    if(!findValue(root, data)){
        return false;
    }
    
    return removeValue(root, data);
}

void BST::clearNode(Node*& currentNode){
    if (currentNode != NULL){
        clearNode(currentNode->childLeft);
        clearNode(currentNode->childRight);
        delete currentNode;
    }
}

//Removes all nodes from the tree, resulting in an empty tree.
void BST::clear(){
    clearNode(root);
    root = NULL;
}
