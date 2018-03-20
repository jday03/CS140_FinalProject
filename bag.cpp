//
// Created by jday on 3/12/18.
//

#include <cmath>
#include "bag.h"
#include <map>
#include <vector>
#include <iostream>
#include "pennant.h"

bag::bag(){
    size = 0;

}

bag::bag(const bag &other){
    size = 0;
    for(int outerCount = 0; outerCount < other.data.size(); ++outerCount){
        for(int innerCount = 0; innerCount < other.data[outerCount]->size; ++innerCount){
            insertNode(new node(other.data[outerCount]->getIndex(innerCount)));
        }
    }

}

bag& bag::operator=(const bag& other){
eraseAll();
    size = 0;
    for(int outerCount = 0; outerCount < other.data.size(); ++outerCount){
        if(other.data[outerCount] != NULL) {
            for (int innerCount = 0; innerCount < other.data[outerCount]->size; ++innerCount) {
                insertNode(new node(other.data[outerCount]->getIndex(innerCount)));
            }
        }
    }
    return *this;
}

bag::~bag(){
    int size = data.size();
    for(int count = size - 1; count >= 0; -- count){

        delete data[count];
        data.erase(data.begin()+count);
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
    node* newNode = new node(insert);

    newNode ->left = NULL;
    newNode -> right = NULL;

    int count = 0;
    insert->visited = true;
    newNode->visited = true;
    // merger must contain insert!!
    pennant* merger = new pennant(newNode);

    if(data.size() == 0){
        pennant* newPennant = NULL;
        data.insert(data.end(),newPennant);
    }

    while (data[count] != NULL){
        merger = pennant::pennantUnion(merger,data[count]);
        delete (data[count]);
        data[count] = NULL;
        count++;

        if(count >= data.size()){
        pennant* newPennant = NULL;
        data.insert(data.end(),newPennant);
    }

    }

    size++;
    (data[count]) = merger;
    delete newNode;
    //delete merger;

}


bag bag::bagUnion(bag S1, bag S2) {
    pennant *y = new pennant;
    delete y->root;
    y =NULL;
    int S1_size = S1.data.size();
    int S2_size = S2.data.size();
    int max = 0;

    if(S1_size > S2_size)
        max = S1_size;
    else
        max = S2_size;

    for (std::vector<pennant*>::size_type k = 0; k <= max; k++){
        pennant *empty = new pennant;
        delete empty->root;
        empty->root =NULL;
        if (k == max){
            FA(S1.data[k], empty, y);
        }
        else if(k >= S1_size){
            FA(empty, S2.data[k], y);
        }

        else if(k >= S2_size){
            FA(S1.data[k], empty, y);

        }
        else{
        FA( S1.data[k], S2.data[k], y );
        }

    }
   // size = S1.size + S2.size;
    this->size = S1.size + S2.size;
    return S1;
}

node bag::getItem(int index){

    pennant* current;

    for(int count = 0; count < data.size();++count){
    current = data[count];
    if(current != NULL){
        if(index >= pow(2,count)){
            index = index - pow(2,count);
        }
        else {
        return current->getIndex(index);
        }
    }

    }
    //exit(1);



}

void bag::eraseAll() {
    int size = data.size();
    for(int count = size - 1; count >= 0; -- count){

        delete data[count];
        data.erase(data.begin()+count);
    }

}


void bag::FA(pennant*  S1_k, pennant* S2_k, pennant* y){
    int value = 0;
    if( S1_k != NULL)
        value += 1;
    if( S2_k != NULL)
        value += 10;
    if( y != NULL)
        value += 100;
    //(x,y,z)
    switch(value){
        case 0 : // 0,0,0
            S1_k = new pennant;

            S2_k = new pennant;
            y  = new pennant;

            S1_k->root = NULL;
            S2_k->size = 0;
            y->root = NULL;
            y->size = 0;
            break;
        case 1 : // 1,0,0
            y  = new pennant;
            S1_k->root = S1_k->root;
            y->root = NULL;
            y->size = 0;
            break;
        case 10 : //0,1,0
            S1_k  = new pennant;
            y  = new pennant;

            S1_k->root = S2_k->root;
            y->root = NULL;
            y->size = 0;
            break;
        case 100: //0,0,1
            S1_k = new pennant;
            y  = new pennant;
            S1_k->root = y->root;
            y->root = NULL;
            y->size = 0;
            break;
        case 11 : // 1,1,0
            y = new pennant;
            y->root = pennant::pennantUnion(S1_k, S2_k)->root;
            S1_k->root = NULL;
            S1_k->size = 0;
            break;
        case 101 : // 1,0,1
            y = new pennant;

            y->root = pennant::pennantUnion(S1_k, y)->root;
            S1_k->root = NULL;
            S1_k->size = 0;

            break;
        case 110 : // 0,1,1
            y = new pennant;
            S1_k = new pennant;

            y->root = pennant::pennantUnion(S2_k, y)->root;
            S1_k->root = NULL;
            S1_k->size = 0;

            break;
        case 111 : // 1,1,1
            S1_k->root = S1_k->root;
            y->root = pennant::pennantUnion(S2_k, y)->root;

    }
}
