

struct node
{
int from, to;
    node *left;
    node *right;
    bool visited;
    node(int fr, int too){
        from = fr;
        to = too;
        visited = false;
    }

};

class pennant {
public:
    pennant();
    ~pennant();
    pennant pennantUnion(pennant x, pennant y);
    pennant pennantSplit(pennant& x);
    pennant pennantSplit();
    node getRoot();

private:
    node *root;
    int size;

};


