//
// Created by jday on 3/12/18.
//

#include <cmath>
#include "bag.h"
#include <map>
#include <vector>
#include "pennant.h"

bag::bag(){
    size = 0;

}

bag::~bag(){
    for(int count = 0; count < data.size(); ++ count){
        data[count] = NULL;
    }

}
bag bag::bagSplit() {
    bag returnBag;

    pennant * newPennant1;
    returnBag.data.insert(returnBag.data.end(),newPennant1 );

    pennant * first= data[0];
    data[0] = NULL;

    for( int i = 1; i < data.size(); ++i){
        if(data[i] != NULL) {
            if (i >= returnBag.data.size()) {
                pennant * newPennant;
                returnBag.data.insert(returnBag.data.end(),newPennant );
            }
            pennant penn = data[i]->pennantSplit();
            *(returnBag.data[i - 1]) = penn;
            data[i - 1] = data[i];
            data[i] = NULL;
        }

        }


    if(first != NULL){
        insertNode(first->getRoot()); //BAG INSERT FIRST
    }

    return returnBag;
}


void bag::insertNode(node* insert) {
    insert ->left = NULL;
    insert -> right = NULL;
    int count = 0;
    insert->visited = true;
    // merger must contain insert!!
    pennant merger(insert);
    while (data[count] != NULL){
        merger = merger.pennantUnion(merger,*data[count]);
        data[count] = NULL;
        count++;
    }
    size++;
    *(data[count]) = merger;
}


bag bag::bagUnion(bag S1, bag S2) {
    pennant y;
    for (std::vector<pennant*>::size_type k = 0; k != S1.data.size(); k++){
        FA( *S1.data[k], *S2.data[k], y );
    }
    size = S1.size + S2.size;
}

node bag::getItem(int index){
    {
    pennant* current;

    for(int count = 0; count < data.size();++count){
    current = data[count];
    if(current != NULL){
        if(index >= pow(count,2)){
            index = index - pow(count,2);
        }
        else {
        return current->getIndex(index);
        }
    }

    }


    }
}

void bag::FA(pennant&  S1_k, pennant& S2_k, pennant& y){
    int value = 0;
    if( S1_k.root != NULL)
        value += 1;
    if( S2_k.root != NULL)
        value += 10;
    if( y.root != NULL)
        value += 100;
    //(x,y,z)
    switch(value){
        case 0 : // 0,0,0
            S1_k.root = NULL;
            y.root = NULL;
            break;
        case 1 : // 1,0,0
            S1_k.root = S1_k.root;
            y.root = NULL;
            break;
        case 10 : //0,1,0
            S1_k.root = S2_k.root;
            y.root = NULL;
            break;
        case 100: //0,0,1
            S1_k.root = y.root;
            y.root = NULL;
            break;
        case 11 : // 1,1,0
            S1_k.root = NULL;
            y.root = pennant::pennantUnion(S1_k, S2_k).root;
            break;
        case 101 : // 1,0,1
            S1_k.root = NULL;
            y.root = pennant::pennantUnion(S1_k, y).root;
            break;
        case 110 : // 0,1,1
            S1_k.root = NULL;
            y.root = pennant::pennantUnion(S2_k, y).root;
            break;
        case 111 : // 1,1,1
            S1_k.root = S1_k.root;
            y.root = pennant::pennantUnion(S2_k, y).root;

    }
}
