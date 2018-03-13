//
// Created by jday on 3/12/18.
//

#include "bag.h"
#include "pennant.h"

bag bag::bagSplit() {
    bag returnBag;

    pennant * first= data[0];
    data[0] = nullptr;

    for( int i = 1; i < data.size(); ++i){
        if(data[i] != nullptr){
            *(returnBag.data[i-1]) = data[i]->pennantSplit();
            data[i-1] = data[i];
            data[i] = nullptr;
        }

    }
    if(first != nullptr){
        insert(first->root); //BAG INSERT FIRST
    }

    return ;
}

void bag::insertPennant(pennant insert) {


}

void bag::insertNode(node insert) {
    

}

bag bag::bagUnion(bag S1, bag S2) {
    pennant y;
    for (std::vector<pennant*>::size_type k = 0; k != S1.data.size(); k++){
        FA( S1.data[k], y );
    }
}

void FA(pennant&  S1_k, pennant& S2_k, pennant& y){
    int value = 0;
    if( S1_k.root != nullptr)
        value += 1;
    if( S2_k.root != nullptr)
        value += 10;
    if( y.root != nullptr)
        value += 100;
    //(x,y,z)
    switch(value){
        case 0 : // 0,0,0
            S1_k.root = nullptr;
            y.root = nullptr;
            break;
        case 1 : // 1,0,0
            S1_k.root = S1_k.root;
            y.root = nullptr;
            break;
        case 10 : //0,1,0
            S1_k.root = S2_k.root;
            y.root = nullptr;
            break;
        case 100: //0,0,1
            S1_k.root = y.root;
            y.root = nullptr;
            break;
        case 11 : // 1,1,0
            S1_k.root = nullptr;
            y.root = pennant::pennantUnion(S1_k, S2_k);
            break;
        case 101 : // 1,0,1
            S1_k.root = nullptr;
            y.root = pennant::pennantUnion(S1_k, y);
            break;
        case 110 : // 0,1,1
            S1_k.root = nullptr;
            y.root = pennant::pennantUnion(S2_k, y);
            break;
        case 111 : // 1,1,1
            S1_k.root = S1_k.root;
            y.root = pennant::pennantUnion(S2_k, y);

    }
}
