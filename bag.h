//
// Created by jday on 3/12/18.
//
#include <vector>
#include <cilk/reducer.h>
#include "pennant.h"
#ifndef BAG_H
#define BAG_H

using namespace std;


    class bag{
    public:
        bag(const bag &other);

        std::vector <pennant*> data;
    int size;

    bag();
    bag bagSplit();
    void insertPennant(pennant* insert);
    void insertNode(node* insert);
    void bagUnion( bag& S1, bag& S2);
    node getItem(int index);
    bool isEmpty(){
        return size == 0;
    }
        void eraseAll();

        bag& operator=(const bag& other);


            ~bag();

        pennant* FA(pennant *S1_k, pennant *S2_k, pennant *&y);

        friend class cilk::monoid_base<bag>;

        friend class bag_reducer;
        friend class cilk::monoid_base<bag>;
    };





/*
class bag_reducer {
public:
    struct monoid: cilk::monoid_base<bag> {
        static void reduce(bag* bag1, bag* bag2) { /////#
            bag1->bagUnion(*bag1,*bag2);
        }
    };

    bag_reducer() : mon() {}
    void bagInsert(node *value){mon.view().insertNode(value);}
    //void bag_union(bag_reducer * y) {this->mon.view().bagUnion(mon.view(),y->mon.view());}
    bag get_value(){return mon.get_value();}
private:
    cilk::reducer<monoid> mon;

};


*/



#endif