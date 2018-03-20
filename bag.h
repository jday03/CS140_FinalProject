//
// Created by jday on 3/12/18.
//

#include <vector>
#include "pennant.h"

#ifndef CS140_FINALPROJECT_BAG_H
#define CS140_FINALPROJECT_BAG_H

#endif //CS140_FINALPROJECT_BAG_H
class bag{
public:
    bag();
    std::vector <pennant*> data;
    bag bagSplit();
    void insertPennant(pennant* insert);
    void insertNode(node* insert);
    bag bagUnion( bag S1, bag S2);
    node getNode(int index);
    void FA(pennant & S1_k, pennant & S2_k, pennant y);
    node getItem(int index);
    int size;
    bool isEmpty(){
        return size == 0;
    }

    ~bag();
    };