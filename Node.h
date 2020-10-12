#ifndef _NODE_H
#define _NODE_H 1
#include "Square.h"
using namespace std;

class Node
{
private:
    //children
    Node *nw;
    Node *ne;
    Node *se;
    Node *sw;
    //siblings?
    vector<Node*> siblings;
    //Parent
    Node *p;
    Rectangle *square;
    int orientation;
    void allNullESq();
    //should i have x y values for nodes until the tree is finalized, and then initialize the square?
    Point *temp;

public:
    Node(double x, double y, Node *parent, vector<Node *> siblings, int orientation);
    Node(double x, double y, Node *parent, vector<Node *> siblings, double width, double height, int orientation);
    Node(double x, double y, Node *parent, vector<Node *> siblings, Rectangle *s, int orientation);


    Node(Rectangle *s);
    virtual ~Node()
    {
        delete nw;
        delete ne;
        delete sw;
        delete se;
        delete p;
        delete square;
    }
    bool isLeaf();
    Node *getParent();
    vector<Node *> getSiblings();
    void createChildren();
    Node *getIndex(int i);
    //1-4 in order of the instance variables above
    Node *getChild(int i);
    vector<Node*> getChildren();
    void setSquare(Square *s);
    //1-Node *nw; 2- Node *ne;3- Node *se;4-Node *sw;
    int getRelativeOrientation();
    double integrate(Function *F);
    Rectangle* getRekt();
};
#endif