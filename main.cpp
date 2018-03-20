#include <iostream>
//#include<cilk/hyperobject_base.h>
#include <vector>
#include <map>
//#include <cilk/reducer.h>
//#include <cilk/cilk.h>
#include "pennant.h"
#include "bag.h"
#include <fstream>
#include <numeric>
#include <cmath>
#include "example_util_gettime.h"
/*
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

    bag get_value() const {
        return item; }

    bag view_get_value () const{
        return item;

    }

};


// Monoid class.

struct BagMonoid : public cilk::monoid_base<bag, BagView> {


    // Set *view to the empty list.
    // Default values

    static void identity(BagView* view) {
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





*/
void insertEdge(std::vector<node*> &graph, int to, int from ){
    while(to >= graph.size()){
        node* newNode = new node(graph.size());
        graph.insert(graph.end(),newNode);

    }
    while(from >= graph.size()){
        node* newNode = new node(graph.size());
        graph.insert(graph.end(),newNode);

    }

   // node* newNode = new node(graph.size());
    //graph.insert(graph.end(),newNode);


    node* first = graph.at(to);
    node* second = graph.at(from);

    first->addAdjacency(second);
    second->addAdjacency(first);

}




void manageDepthCounter(int depthCount, std::vector <node*> graph,std::map < int, std::vector < int > >& depthMap){
    for(int count = 0; count <= depthCount; ++count){
        std::vector<int> values;
        std::pair <int,std::vector<int> > newDepth (count,values);
        depthMap.insert (newDepth);
    }

    for(int count = 0; count < graph.size(); ++count){
        node* temp = graph[count];
        if(temp->depth >= 0){
            std::map<int, std::vector<int> >::iterator iter = depthMap.find(temp->depth);
            iter->second.insert(iter->second.end(),temp->number);
        }
    }

}



void printDepthCounter(std::map<int, std::vector<int> > depthMap ){
    std::map<int, std::vector<int> >::iterator iter = depthMap.begin();

    while (iter != depthMap.end()){
        std::cout<< "Nodes at depth" << iter->first << ": ";
        for(int count = 0; count < iter->second.size();++count){
            std::cout<< " " << (iter->second[count]) << " ";

        }
        std::cout << std::endl;
        iter++;
    }

}





std::map<int, std::vector<int> > BFS(std::vector<node*> graph,node* root)
{
    std::map<int, std::vector<int> > depthMap;
  std::cout << "hello";
    root->visited = true;
    node* ptr = root;
    ptr->depth = 0;
    bag frontier;
    frontier.insertNode(ptr);


    bag frontier2;
    frontier2.insertNode(ptr->adjacencies[0]);

    frontier = frontier.bagUnion(frontier,frontier2);
    int depthCounter = 0;


/*
    while ( ! frontier.isEmpty() )
    {
        depthCounter++;
//        cilk::reducer<BagMonoid> succbag;
    bag newFrontier;
        for (int i=0; i< frontier.size; i++){
            std::vector<node*> adjacents = frontier.getItem(i).getAdjacents();
            std::cout<< adjacents.size() << std::endl;
            for (int adjCount = 0; adjCount < adjacents.size(); ++ adjCount) {
                if (adjacents[adjCount]->visited == false) {
                    adjacents[adjCount]->depth = depthCounter;
                    newFrontier.insertNode(adjacents[adjCount]);
                    //succbag->add_value (adjacents[adjCount]);
                }
            }

        }
        //frontier = succbag.get_value();
        frontier = newFrontier;
    }

    manageDepthCounter(depthCounter,graph,depthMap);
*/
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
    std::vector<node*> graph;

    std::ifstream inFile;
    inFile.open(argv[1]);
    if (!inFile) {
        cerr << "Unable to open file datafile.txt";
        exit(1);   // call system to stop
    }

    int temp1,  temp2;
    while(inFile >> temp1){
        inFile>>temp2;
       // std::cout << "temp1:" << temp1 << " temp2: " << temp2 << std::endl;
        insertEdge(graph,temp1,temp2);
        //std::cout << "graph.size = " << graph.size() <<std::endl;

    }
    inFile.close();
    std::cout << "graph.size = " << graph.size() << std::endl;
    //std::cout << "v 2 num: " << graph[2]->number << std::endl;
    //std::cout << "v 2 adj1: " << graph[2]->adjacencies[0]->number<< std::endl;

    for(int i = 1; i < graph.size(); ++i){
        for(int j = 0 ; j < graph[i]->adjacencies.size(); j++) {


            std::cout << i  << " adjacent to  " << graph[i]->adjacencies[j]->number << std::endl;
        }
    }

    std::map<int, std::vector<int> > depthMap;

    //srand(time(NULL));
   // t1 = example_get_time();
    node * ptr = graph[1];
     depthMap = BFS(graph,ptr );

   // t2 = example_get_time();
  // printDepthCounter(depthMap);

   // std::cout << "Time: " << t2 - t1 << std::endl;
    return 0;


}



