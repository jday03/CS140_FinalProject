//
// Created by jday on 3/12/18.
//
#include <vector>
#include "pennant.h"
#ifndef BAG_H
#define BAG_H

using namespace std;



    class bag{
    public:
    std::vector <pennant*> data;
    int size;

    bag();
    bag bagSplit();
    void insertPennant(pennant* insert);
    void insertNode(node* insert);
    bag bagUnion( bag S1, bag S2);
    void FA(pennant&  S1_k, pennant& S2_k, pennant& y);
    node getItem(int index);
    bool isEmpty(){
        return size == 0;
    }

    ~bag();
    };

#endif