

struct node
{
int from, to;
    node *left;
    node *right;
    node(int fr, int too){
        from = fr;
        to = too;
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


