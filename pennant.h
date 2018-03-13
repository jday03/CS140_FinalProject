

struct node
{
int from, to;
    node *left;
    node *right;
};

class pennant {
public:
    pennant();
    ~pennant();
    pennant pennantUnion(pennant x, pennant y);
    pennant pennantSplit(pennant& x);
    pennant pennantSplit();


private:
    node *root;


};


