#include <iostream>
#include<cilk/hyperobject_base.h>
#include <vector>
#include <map>
#include <cilk/reducer.h>
#include <cilk/cilk.h>
#include "pennant.h"
#include "bag.h"


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

struct BagMonoid : public cilk::monoid_base<bag, BagView> {


    // Set *view to the empty list.
    //
    static void identity(BagView* view) {
// Default values
        if(view == NULL){
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






void insertEdge(std::vector<node> graph, int to, int from ){
    node* first = &graph[to];
    node* second = &graph[from];
    (first->adjacencies).insert(first->adjacencies.end(),second );
    second->adjacencies.insert(second->adjacencies.end(), first);
}




void manageDepthCounter(int depthCount, std::vector <node> graph,std::map < int, std::vector < int > > depthMap){
    for(int count = 0; count <= depthCount; ++count){
        std::vector<int> values;
        std::pair <int,std::vector<int> > newDepth (count,values);
        depthMap.insert (newDepth);
    }

    for(int count = 0; count < graph.size(); ++count){
        node temp = graph[count];
        if(temp.depth >= 0){
            std::map<int, std::vector<int> >::iterator iter = depthMap.find(temp.depth);
            iter->second.insert(iter->second.end(),temp.number);
        }
    }

}



void printDepthCounter(std::map<int, std::vector<int> > depthMap ){
    std::map<int, std::vector<int> >::iterator iter = depthMap.begin();

    while (iter != depthMap.end()){
        std::cout<< "Nodes at depth: ";
        for(int count = 0; count < iter->second.size();++count){
            std::cout<< " " << (iter->second[count]) << " ,";

        }
        std::cout << std::endl;
    }

}






/*void BFS(std::vector<node> graph, node root)
{
    root.visited = true;
    node* ptr = &root;
    bag frontier;
    frontier.insertNode(ptr);
    std::map<int, std::vector<int> > depthMap;
    int depthCounter = -1;

    while ( ! frontier.isEmpty() )
    {
        depthCounter++;

        frontier.size = 4;
        cilk::reducer<BagMonoid> succbag;
        cilk_for (int i=0; i< frontier.size; i++){
            std::vector<node*> adjacents = frontier.getItem(i).getAdjacents();
            for (int adjCount = 0; adjCount < adjacents.size(); ++ adjCount) {
                if (adjacents[adjCount]->visited == false) {
                    adjacents[adjCount]->depth = depthCounter;
                    succbag.view().add_value (adjacents[adjCount]);
                }
            }

        }
        frontier = succbag.get_value();

    }

    manageDepthCounter(depthCounter,graph,depthMap);
}

*/






int main() {
    std::cout << "Hello, BIIITCH!" << std::endl;
    std::vector

}



