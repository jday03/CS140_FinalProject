

#include "pennant.h"

pennant:: pennant(){
    root = new node;
    size = 0;
}


// Makes the left branch of root rootStart. Useful when initializing the pennant with a node.
// Assumed that the node has no children.
pennant:: pennant(node* rootStart){
    root = new node (rootStart);
    size = 1;
}

pennant* pennant::pennantUnion(pennant* x, pennant* y){
    if(x->size ==1 && y->size == 1){
        x->size++;
        x->root->left = y->root;

    } else{
    x->size = x->size + y->size;
    y->root->right = x->root->left;
    x->root->left = y->root;}
    return x;
}

pennant pennant::pennantSplit(pennant& x) {
    pennant y ;
    y.root = x.root->left;
    x.root->left = y.root->right;
    y.root->right = NULL;
    x.size = x.size /2;
    y.size = x.size;
    return y;
}

pennant pennant::pennantSplit() {
    pennant y ;
    y.root = root->left;
    root->left = y.root->right;
    y.root->right = NULL;
    y.size = size /2;
    size = y.size;
    return y;
}

node* pennant::getRoot() {
    return root;
}

node pennant::getIndex(int index) {
    if (index == 0) {
        return *(root);
    } else if (index == 1) {
        return *(root->left);
    }

    int sizeOfRemainingTree = size-1;
    node *parser = root->left;


    int currentIndex = 1;
    do {
        sizeOfRemainingTree--;
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
    node * spot = root;

    if(spot->left != NULL)
            deleteBelowLeft(spot);

    if(spot->right != NULL)
        deleteBelowRight(spot);
    delete root;
}

void pennant::deleteBelowLeft(node* spot){

    if(spot->left != NULL)
        deleteBelowLeft(spot->left);

    if(spot->right != NULL)
        deleteBelowRight(spot->right);
    delete spot;
}


void pennant::deleteBelowRight(node* spot){

    if(spot->left != NULL)
        deleteBelowLeft(spot->left);

    if(spot->right != NULL)
        deleteBelowRight(spot->right);
    delete spot;
}