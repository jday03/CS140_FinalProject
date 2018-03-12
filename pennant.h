

struct node
{
    int key_value;
    node *left;
    node *right;
};

class pennant {
public:
    pennant();
    ~pennant();
    pennant pennantUnion(pennant x, pennant y);
    pennant pennantSplit(pennant& x);


private:
    node *root;


};


