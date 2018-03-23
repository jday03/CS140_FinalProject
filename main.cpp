#include <iostream>
#include<cilk/hyperobject_base.h>
#include <vector>
#include <map>
#include <cilk/reducer.h>
#include <cilk/reducer_list.h>
#include <cilk/cilk.h>
#include <cilk/reducer_string.h>
#include <cilk/reducer_list.h>
#include "pennant.h"
#include "bag.h"
#include <fstream>
#include <numeric>
#include <cmath>
#include "example_util_gettime.h"
#include <list>




/*
class bagMonoid;


class BagView {
    bag item;

public:
    typedef bag value_type;

    BagView(): item(){
    }

    void add_value(node* x) {
        item.insertNode(x);

    }


     void reduce(BagView *right){
        std::cout << "Reducer called" << item.size << std::endl;

        this->item.bagUnion(right->item);
        std::cout << "I have " << item.size << std::endl;

        // right->item.eraseAll();
    }

    value_type view_get_value() const{
        return item;
    }

};


class bagMonoid : public cilk::monoid_base<bag, BagView> {

    static void identity(BagView *view) {
        view=new BagView;
    }

    static void reduce(value_type *left, value_type *right){
        std::cout << "Reducer called " << left->size << std::endl;

        left->bagUnion(*right);
        std::cout << "I have " << left->size << std::endl;

        // right->item.eraseAll();
    }

};


typedef cilk::monoid_with_view<BagView> BagMonoid;


// Monoid class.
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


    graph.at(to)->addAdjacency(from);
    graph.at(from)->addAdjacency(to);


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
            std::cout<< " " << (iter->second[count]) << ", ";

        }
        std::cout << std::endl;
        iter++;
    }

}


/*
void BFS(Graph *G, Vertex root)
{
    list<Vertex> frontier(root);
    Vertex * parent = new Vertex[n];
    while ( ! frontier.isEmpty() ) {

        hyperobject< reducer_list_append<Vertex> > succlist();
        cilk_for (int i=0; i< frontier.size(); i++)
        {
            for( Vertex v in frontier[i].adjacency() )
            {
                if ( parent[v] == frontier[i] )
                {
                    succlist.push_back(v);
                    v.visit(); // Mark “visited”
                }
            }
        }
        frontier = succlist.getValue();
        */

std::map<int, std::vector<int> > BFS(std::vector<node*> graph,node* root) {
    std::map<int, std::vector<int> > depthMap;
    root->visited = true;
    root->depth = 0;

   // list<node *> frontier;
    list<int> frontier2(root->number);

    //frontier.push_front(root);
    int * parentArray = new int[graph.size() + 1];

    //int * parent1 = new int[graph.size()];

    int depthCounter = 0;

    while (!frontier2.empty()) {
        depthCounter++;
        std::cout << "Frontier size is: " << graph[frontier2.front()]->adjacencies.size() << std::endl;

        cilk_for(int i = 0; i < graph[frontier2.front()]->adjacencies.size(); i++ ){

            std::vector<int> adjacents = graph[frontier2.front()]->getAdjacents();

            for (int adjCount = 0; adjCount < adjacents.size(); ++adjCount) {
                if (!graph[adjacents[adjCount]]->visited) {
                    parentArray[adjacents[adjCount]]= graph[frontier2.front()]->adjacencies[i];
                }
            }
        }

        cilk::reducer< cilk::op_list_append<int> > succlist;
        cilk_for(int i = 0; i < graph[frontier2.front()]->adjacencies.size(); i ++ ){
            std::vector<int> adjacents = graph[frontier2.front()]->getAdjacents();

            for (int adjCount = 0; adjCount < adjacents.size(); ++adjCount) {
                if (parentArray[adjacents[adjCount]] == graph[frontier2.front()]->adjacencies[i]){

                    succlist->push_back(adjacents[adjCount]);
                //graph[adjacents[adjCount]]->depth = depthCounter;
                graph[adjacents[adjCount]]->visited = true;
                }
            }

            }
        frontier2 = succlist.get_value();
    }



    manageDepthCounter(depthCounter, graph, depthMap);
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

    int temp1,  temp2;
    while(inFile.good()){
        inFile>>temp1;
        inFile>>temp2;
        //temp2 = inFile.get();
        //add vertexes to graph
        insertEdge(graph,temp1,temp2);
    }


    std::map<int, std::vector<int> > depthMap;

    srand(time(NULL));
   t1 = example_get_time();
    node * ptr = graph[1];
     depthMap = BFS(graph,ptr );

    t2 = example_get_time();
  printDepthCounter(depthMap);

    std::cout << "Time: " << t2 - t1 << std::endl;
    return 0;


}


/*
 * cilk_for(int j = 0; j < 5; j++){
        succbag->add_value(ptr);
    }

    frontier = succbag.get_value();

    for (int k = 0; k < frontier.size; ++k){
        std::cout<< "thing is " << frontier.getItem(k).number << std::endl;
    }

 *
 *
 *
 */
