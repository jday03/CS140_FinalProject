//
// Created by jday on 3/12/18.
//

#include "bag.h"

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
