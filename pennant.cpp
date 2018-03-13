

#include "pennant.h"

pennant:: pennant(){
    root = nullptr;
}

pennant pennant::pennantUnion(pennant x, pennant y){
    y.root->right = x.root->left;
    x.root->left = y.root;
    return x;
}

pennant pennant::pennantSplit(pennant& x) {
    pennant y ;
    y.root = x.root->left;
    x.root->left = y.root->right;
    y.root->right = nullptr;
    return y;
}

pennant pennant::pennantSplit() {
    pennant y ;
    y.root = root->left;
    root->left = y.root->right;
    y.root->right = nullptr;
    return y;
}

node pennant::getRoot() {
    return *root;
}





