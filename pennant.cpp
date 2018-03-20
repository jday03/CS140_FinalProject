

#include "pennant.h"

pennant:: pennant(){
    root = nullptr;
}


// Makes the left branch of root rootStart. Useful when initializing the pennant with a node.
// Assumed that the node has no children.
pennant:: pennant(node* rootStart){
    (root->left) = rootStart;
    size = 1;
}

pennant pennant::pennantUnion(pennant x, pennant y){
    x.size = x.size + y.size;
    y.root->right = x.root->left;
    x.root = y.root;
    return x;
}

pennant pennant::pennantSplit(pennant& x) {
    pennant y ;
    y.root = x.root->left;
    x.root->left = y.root->right;
    y.root->right = nullptr;
    x.size = x.size /2;
    y.size = x.size;
    return y;
}

pennant pennant::pennantSplit() {
    pennant y ;
    y.root = root->left;
    root->left = y.root->right;
    y.root->right = nullptr;
    y.size = size /2;
    size = y.size;
    return y;
}

node* pennant::getRoot() {
    return root;
}

node pennant::getIndex(int index) {
    if (index == 0) {
        return *(root->left);
    } else if (index == 1) {
        return *(root->left->left);
    }

    int sizeOfRemainingTree = size;
    int actualRemainingElements = size - 1;
    node *parser = root->left->left;


    int currentIndex = 1;
    do {
        actualRemainingElements--;
        if (index > currentIndex + sizeOfRemainingTree / 2) {
            parser = parser->left;
            currentIndex = currentIndex + sizeOfRemainingTree / 2 + 1;
            sizeOfRemainingTree = sizeOfRemainingTree / 2;
        } else {
            parser = parser->right;
            currentIndex++;
            sizeOfRemainingTree = sizeOfRemainingTree / 2;
        }
    } while (index != currentIndex);

    return *parser;

}

pennant::~pennant() {
    root->left = nullptr;
    root->right = nullptr;
    delete root;
}



