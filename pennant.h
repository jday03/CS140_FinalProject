

#include <map>
#include <vector>

#ifndef PENNANT_H
#define PENNANT_H
struct node
{
    int number;
    node *left;
    node *right;
    bool visited;
    int depth;
    node(int num){
        number = num;
        visited = false;
        depth = -1;
    }
    node(){
        left = NULL;
        right = NULL;
        number = -1;
    }

    node(node* copy){
        number = copy->number;
        visited = copy->visited;
        depth = copy->depth;
        adjacencies = copy->adjacencies;

    }

    std::vector<node*> adjacencies;
    void addAdjacency(node* adjacentNode){
        adjacencies.insert(adjacencies.end(),adjacentNode);
    }

    std::vector<node*> getAdjacents(){
        return adjacencies;
    }

};

class pennant {
public:
    pennant();
    ~pennant();
    pennant(node* rootStart);
    static pennant pennantUnion(pennant x, pennant y);
    pennant pennantSplit(pennant& x);
    pennant pennantSplit();
    node* getRoot();
    node getIndex(int index);
    node *root;
    int size;

};


#endif
