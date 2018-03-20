//
// Created by jday on 3/12/18.
//

//
// Created by jday on 3/12/18.
//

#include <cilk/cilk.h>
#include <cilk/reducer.h>
#include <iostream>
#include "bag.h"

//  Singly-linked list.
//


class BagMonoid;

// forward declaration
//  View class.
//


class BagView {
    friend class BagMonoid; // for the identity and reduce functions
    bag item;
public:
    void add_value(node* x) {
        item.insertNode(x);
    }
    bag get_value() const { return item; }


};


// Monoid class.
//

struct BagMonoid : public cilk::monoid_base<bag, BagView> {


    // Set *view to the empty list.
    //
    static void identity(BagView* view) {
// Default values
        if(view == nullptr){
        view = new BagView;
        }

    }

    // Move the right list to the beginning of the left list.
    // Leave the right list empty.
    //
    static void reduce(BagView* left, BagView* right) {
    left->item.bagUnion(left->item,right->item);
    }
};


// Compute a value. (Probably does something more interesting in
// a real program.)
//
int compute(int i)
{
    return i;
}






// Create a list.
/*
IntListNode* make_list(int n)
{
    cilk::reducer<BagMonoid> list;
    cilk_for (int i = 0; i < n; ++i) {
        list->add_value(i);     // "list->" accesses the view
    }
    return list.get_value();   // get_value() is a reducer function
}

// Use a list. (Probably does something more interesting in a
// real program.)
//
void print_list(IntListNode* list)
{
    for (IntListNode* node = list; node; node = node->link)
        std::cout << node->data << "\n";
}
 */
