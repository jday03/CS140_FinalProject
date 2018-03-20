

#include <vector>

struct node
{
    int number;
    node *left;
    node *right;
    bool visited;
    node(int num){
        number = num;
        visited = false;
    }
    std::vector<node*> adjacencies;

    void addAdjacency(node* adjacentNode){
        adjacencies.insert(adjacencies.end(),adjacentNode);
    }

    std::vector<node*> getAdjacencies(){
        return adjacencies;
    }

};

class pennant {
public:
    pennant();
    ~pennant();
    pennant:: pennant(node* rootStart);
    pennant pennantUnion(pennant x, pennant y);
    pennant pennantSplit(pennant& x);
    pennant pennantSplit();
    node* getRoot();
    node getIndex(int index);


private:
    node *root;
    int size;

};


