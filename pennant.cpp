

#include <cmath>
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

pennant::pennant(const pennant & other) {
    size = other.size;
    if (other.size != 0) {

        int layers = log2(other.size);
        root = new node(other.root);
        if (layers != 0) {
            addBelowLeft(root->left, layers - 1, other.root->left);
        }
    }
}



void pennant::addBelowLeft(node*& spot, int layersLeft, node* ref){
    spot= new node(*ref);
    if(layersLeft != 0) {
        addBelowLeft(spot->left,layersLeft-1, ref->left);
        addBelowRight(spot->right, layersLeft-1, ref->right);

    }

}




void pennant::addBelowRight(node*& spot, int layersLeft, node* ref) {
    spot= new node(*ref);
    if(layersLeft != 0) {
        addBelowLeft(spot->left,layersLeft-1, ref->left);
        addBelowRight(spot->right, layersLeft-1, ref->right);

    }

}







pennant* pennant::pennantUnion(pennant*& x, pennant*& y){
   pennant *temp1;
    pennant *temp2;
    if(x->size >0) {
       temp1 = new pennant(*x);
   if(y->size > 0){
        temp2 = new pennant(*y);

   } else {
       return temp1;
   }
   } else if(y->size > 0){
       temp2 = new pennant(*y);
        return temp2;

   }




    if(temp1->size ==1 && temp2->size == 1){
        temp1->size++;
        temp1->root->left = temp2->root;

    } else{

        temp1->size = temp1->size + temp2->size;
        temp2->root->right = temp1->root->left;
        temp1->root->left = temp2->root;

    }

    return temp1;
}

pennant pennant::pennantSplit(pennant& x) {
    pennant y ;
    y.root = x.root->left-> left;

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
    int layers = log2(size);
    node* ptr = root;
    if(layers >= 1)
    deleteBelowLeft(ptr->left,layers-1);
    delete ptr;
}

void pennant::deleteBelowLeft(node* spot, int layersLeft){
if(layersLeft == 0) {
    delete spot;
}else {
        deleteBelowLeft(spot->left,layersLeft-1);
        deleteBelowRight(spot->right,layersLeft-1);
        delete spot;
    }
}




void pennant::deleteBelowRight(node* spot, int layersLeft){
    if(layersLeft == 0) {
        delete spot;
    }else {
        deleteBelowLeft(spot->left,layersLeft-1);
        deleteBelowRight(spot->right,layersLeft-1);
        delete spot;
    }
}