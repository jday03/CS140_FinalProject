#include <iostream>
#include<cilk/hyperobject_base.h>
#include <vector>
#include <map>
#include <cilk/reducer.h>
#include "pennant.h"
#include "bag.h"
#include <fstream>
#include <numeric>
#include <cmath>
#include "example_util_gettime.h"

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






void insertEdge(std::vector<node> graph, int to, int from ){
    node* first = &graph[to];
    node* second = &graph[from];
    (first->adjacencies).insert(first->adjacencies.end(),second );
    second->adjacencies.insert(second->adjacencies.end(), first);
}




void manageDepthCounter(int depthCount, std::vector<node> graph,std::map<int, std::vector<int>> depthMap){
    for(int count = 0; count <= depthCount; ++count){
        std::vector<int> values;
        std::pair <int,std::vector<int>> newDepth (count,values);
        depthMap.insert (newDepth);
    }

    for(int count = 0; count < graph.size(); ++count){
        node temp = graph[count];
        if(temp.depth >= 0){
            auto iter = depthMap.find(temp.depth);
            iter->second.insert(iter->second.end(),temp.number);
        }
    }

}



void printDepthCounter(std::map<int, std::vector<int>> depthMap ){
    auto iter = depthMap.find(0);
    while (iter != depthMap.end()){
        auto vec = iter->second;
        std::cout<< "Nodes at depth: ";
        for(int count = 0; count < vec.size();++count){
            std::cout<< " " << vec[count] << " ,";

        }
        std::cout << std::endl;
    }
}






std::map<int, std::vector<int> > BFS(std::vector<node> graph, node root)
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
        cilk::reducer<BagMonoid> succbag;

        frontier.size = 4;
        for (int i=0; i< frontier.size; i++){
            std::vector<node*> adjacents = frontier.getItem(i).getAdjacents();
            for (int adjCount = 0; adjCount < adjacents.size(); ++ adjCount) {
                if (adjacents[adjCount]->visited == false) {
                    adjacents[adjCount]->depth = depthCounter;
                    succbag. (adjacents[adjCount]);
                }
            }

        }
        frontier = succbag.get_value();

    }

    manageDepthCounter(depthCounter,graph,depthMap);
    return depthMap;
}








int main(int argc, char **argv) {
    long t1, t2;
    //cilk::hyperobject< Bag<int> > succbag();
    if(argc < 2)
    {
        printf("Usage : ./pbfs <graphinputfile> \n");
        exit(-1);
    }
    std::vector<node> graph;
    bag Bag;

    std::ifstream inFile;
    inFile.open(argv[1], std::ifstream::in);

    int temp1,  temp2;
    while(inFile.good()){
        temp1 = inFile.get();
        temp2 = inFile.get();
        //add vertexes to graph
        insertEdge(graph,temp2,temp1);
    }

    std::map<int, std::vector<int> > depthMap;

    srand(time(NULL));
    t1 = example_get_time();

    depthMap = BFS(graph, *Bag.data[0]->root);

    t2 = example_get_time();
    printDepthCounter(depthMap);

    std::cout << "Time: " << t2 - t1 << std::endl;
    return 0;


}



