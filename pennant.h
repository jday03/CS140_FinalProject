

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


    node(const node& copy){
            number = copy.number;
            visited = copy.visited;
            depth = copy.depth;
            adjacencies = copy.adjacencies;

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
    pennant pennantSplit(pennant& x);
    pennant pennantSplit();
    node* getRoot();
    node getIndex(int index);
    node *root;
    int size;

static pennant *pennantUnion(pennant *x, pennant *y);

    void deleteBelowLeft(node *spot);

    void deleteBelowRight(node *spot);

    void deleteBelowLeft(node *spot, int layersLeft);

    void deleteBelowRight(node *pNode, int i);
};


#endif
