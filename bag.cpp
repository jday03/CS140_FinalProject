//
// Created by jday on 3/12/18.
//

#include "bag.h"
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
    // merger must contain insert!!
    pennant merger;
    while (data[count] != nullptr){
        merger = merger.pennantUnion(merger,*data[count]);
        data[count] = nullptr;
        count++;
    }

    *(data[count]) = merger;
}

