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
    for(int outerCount = 0; outerCount < other.data.size(); ++outerCount) {
        if (other.data[outerCount] != NULL) {
            for (int innerCount = 0; innerCount < other.data[outerCount]->size; ++innerCount) {
                insertNode(new node(other.data[outerCount]->getIndex(innerCount)));
            }
        }
    }
}

bag& bag::operator=(const bag& other){
    std::cout<< "equal op" << std::endl;
//eraseAll();
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


    int count = 0;
    insert->visited = true;
    // merger must contain insert!!
    pennant* merger = new pennant(insert);

    if(data.size() == 0){
        pennant* newPennant = NULL;
        data.insert(data.end(),newPennant);
    }

    while (data[count] != NULL){
        merger = pennant::pennantUnion(merger,data[count]);
        delete data[count];
        data[count] = NULL;
        count++;

        if(count >= data.size()){
        pennant* newPennant = NULL;
        data.insert(data.end(),newPennant);
    }

    }

    size++;
    (data[count]) = merger;
    //delete merger;

}


void bag::bagUnion( bag& S2) {

    pennant *y =NULL;
    long S1_size = this->data.size();
    long S2_size = S2.data.size();
    long max = 0;

    if(S1_size > S2_size)
        max = S1_size;
    else
        max = S2_size;
while(this->data.size() < max){
    this->data.insert(this->data.end(),NULL);
}
    while(S2.data.size() < max){
        S2.data.insert(S2.data.end(),NULL);
    }



    for (std::vector<pennant*>::size_type k = 0; k < max; k++){

            pennant * ptr1 =FA( this->data[k], S2.data[k], y );
            if(ptr1 != NULL){
                this->data[k]= new pennant(*ptr1);

            } else{
                this->data[k] = NULL;
            }

    }
    if(y!=NULL){
        this->data.insert(this->data.end(),new pennant(*y));
    }
   // size = S1.size + S2.size;
    this->size = this->size + S2.size;
    //return S1;
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



pennant* bag::FA(pennant*  S1_k, pennant* S2_k, pennant* &y){

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
            break;
        case 1 : // 1,0,0
           return S1_k;
            break;
        case 10 : //0,1,0
            return S2_k;
            break;
        case 100: //0,0,1
            pennant* returner;
            returner = new pennant (*y);
            delete y;
            y=NULL;
            return returner;
            break;
        case 11 : // 1,1,0
            y = pennant::pennantUnion(S1_k, S2_k);
            return NULL;
            break;
        case 101 : // 1,0,1
            y = pennant::pennantUnion(S1_k, y);
            return NULL;
            break;
        case 110 : // 0,1,1
            y= pennant::pennantUnion(S2_k, y);
            return NULL;
            break;
        case 111 : // 1,1,1

            y = pennant::pennantUnion(S2_k, y);
            return S1_k;
    }
}
