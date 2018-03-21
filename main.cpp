#include <iostream>
#include<cilk/hyperobject_base.h>
#include <vector>
#include <map>
#include <cilk/reducer.h>
#include <cilk/cilk.h>
#include "pennant.h"
#include "bag.h"
#include <fstream>
#include <numeric>
#include <cmath>
#include "example_util_gettime.h"


// forward declaration
//  View class.
//



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

        this->item.bagUnion(item,right->item);
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

        left->bagUnion(*left,*right);
        std::cout << "I have " << left->size << std::endl;

        // right->item.eraseAll();
    }

};


typedef cilk::monoid_with_view<BagView> BagMonoid;


// Monoid class.







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





std::map<int, std::vector<int> > BFS(std::vector<node*> graph,node* root) {
    std::map<int, std::vector<int> > depthMap;
    root->visited = true;
    node *ptr = root;
    ptr->depth = 0;


    bag frontier;
    frontier.insertNode(ptr);



    // frontier.bagUnion(frontier,frontier2);

    int depthCounter = 0;

    while (!frontier.isEmpty()) {
        depthCounter++;
      //  bag_reducer succbag;
        //bag newFrontier;

       cilk::reducer<BagMonoid> succbag;

        bag oneBag;
        bag twoBag;
        bag threeBag;

        std::cout << "Frontier size is: " << frontier.size << std::endl;
        cilk_for (int i = 0; i < frontier.size; i++) {

            std::vector<int> adjacents = frontier.getItem(i).getAdjacents();
            for (int adjCount = 0; adjCount < adjacents.size(); ++adjCount) {
                if (!graph[adjacents[adjCount]]->visited) {
                    graph[adjacents[adjCount]]->depth = depthCounter;
                   succbag->add_value(graph[adjacents[adjCount]]);

                    if(adjCount%3 <=1) {
                        oneBag.insertNode(graph[adjacents[adjCount]]);
                    }else {
                        if(adjCount %3 == 2){
                            twoBag.insertNode(graph[adjacents[adjCount]]);
                        } else threeBag.insertNode(graph[adjacents[adjCount]]);
                    }

                    //std::cout << "item proc is: " << adjacents[adjCount]->number << std::endl;
                }
            }



 //           frontier.bagUnion(frontier, twoBag);
           // std::cout << "loop complete" << std::endl;
        }


       frontier.eraseAll();
       /*oneBag.bagUnion(oneBag,twoBag);
        twoBag.eraseAll();
         oneBag.bagUnion(oneBag,threeBag);
        frontier = oneBag; */
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
