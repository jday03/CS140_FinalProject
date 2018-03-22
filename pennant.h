

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
        left = NULL;
        right = NULL;
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
        left = NULL;
        right = NULL;
    }


    node(const node& copy){
            number = copy.number;
            visited = copy.visited;
            depth = copy.depth;
            left = NULL;
            right = NULL;
        }


};

class pennant {
public:
    pennant();

    pennant(const pennant &other);

    ~pennant();
    pennant(node* rootStart);
    pennant pennantSplit(pennant& x);
    pennant pennantSplit();
    node* getRoot();
    node getIndex(int index);
    node *root;
    int size;


    void deleteBelowLeft(node *spot, int layersLeft);

    void deleteBelowRight(node *pNode, int i);

    void addBelowRight(node *&spot, int layersLeft, node *ref);

    void addBelowLeft(node *&spot, int layersLeft, node *ref);

    static pennant *pennantUnion(pennant *&x, pennant *&y);
};


#endif
