//
// Created by jday on 3/12/18.
//

#include "bag.h"
#include "pennant.h"
bag::bag(){


}
bag bag::bagSplit() {
    bag returnBag;

    pennant * newPennant1;
    returnBag.data.insert(returnBag.data.end(),newPennant1 );

    pennant * first= data[0];
    data[0] = nullptr;

    for( int i = 1; i < data.size(); ++i){
        if(data[i] != nullptr) {
            if (i >= returnBag.data.size()) {
                pennant * newPennant;
                returnBag.data.insert(returnBag.data.end(),newPennant );
            }
            pennant penn = data[i]->pennantSplit();
            *(returnBag.data[i - 1]) = penn;
            data[i - 1] = data[i];
            data[i] = nullptr;
        }

        }


    if(first != nullptr){
        insertNode(first->getRoot()); //BAG INSERT FIRST
    }

    return returnBag;
}


void bag::insertNode(node insert) {
    int count = 0;
    insert.visited = true;
    // merger must contain insert!!
    pennant merger(insert);
    while (data[count] != nullptr){
        merger = merger.pennantUnion(merger,*data[count]);
        data[count] = nullptr;
        count++;
    }

    *(data[count]) = merger;
}


bag bag::bagUnion(bag S1, bag S2) {
    pennant y;
    for (std::vector<pennant*>::size_type k = 0; k != S1.data.size(); k++){
        FA( S1.data[k], y );
    }
}

getItem(int index){
    {
    node* current;

    for(int count = 0; count < data.size();++count){
    current = data[count];
    if(current != nullptr){
        if(index >= pow(count,2)){
            index = index - pow(count,2);
        }
        else {
        return current.getIndex(index);
        }
    }

    }


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
