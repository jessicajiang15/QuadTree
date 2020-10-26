#ifndef _NODE_H
#define _NODE_H 1
#include "Square.h"
using namespace std;
//Placeholder
class Node
{
private:
    //children
    /**
     * The children of this node. 
     * NW=North west, representing a child that is on the top left corner.
     * NE=North east, representing a child that is on the top right corner.
     * SE=South east, representing a child that is on the bottom right corner.
     * SW=South west, representing a child that is on the bottom left corner.
     * */
    Node *nw;
    Node *ne;
    Node *se;
    Node *sw;
/**
 * Parent of this node.
 * I'm also not sure if information about the parent needs to be stored, since it doesn't look
 * like we'll ever be looping backwards at any point.
 * */
    Node *p;
/**
 * The rectangle representing the region this node represents. It is a nullptr if the current node
 * is NOT a leaf.
 * */
    Rectangle *square;
    /**
     * Orientation of the current node.
     * 1-Node *nw; 2- Node *ne;3- Node *se;4-Node *sw;
     * */
    int orientation;
    /**
     * Initializes everything to be a nullptr except the Rectangle object
     * */
    void allNullESq();
    //should i have x y values for nodes until the tree is finalized, and then initialize the square?
    Point *temp;
    bool hasChildren;
    /**
     * The current layer that the node is at.
     * */
    int level;

public:
/**
 * Different constructors that take in different parameters depending on how you want to initialize
 * the node.
 * */
    Node(double x, double y, Node *parent, int orientation);
    Node(double x, double y, Node *parent, double width, double height, int orientation, int level);
    Node(double x, double y, Node *parent, Rectangle *s, int orientation);
    Node(Rectangle *s);
    /**
     * Destructor
     * */
    virtual ~Node()
    {
        delete nw;
        delete ne;
        delete sw;
        delete se;
        delete p;
        delete square;
    }
    /**
     * Returns true if the current node is a leaf, that is it doesn't have any children.
     * */
    bool isLeaf();
    /**
     * Returns the parent of this node.
     * */
    Node *getParent();
    /**
     * Subdivides the current node into 4, initializing the children and making square a nullptr
     * */
    void createChildren();
    /**
     * Returns a list of the children of this node.
     * */
    vector<Node*> getChildren();
    /**
     * Initializes the square of this node to s.
     * */
    void setSquare(Square *s);
    /**
     * Returns the relative position of this particular node.
    **/
    int getRelativeOrientation();
    /**
     * Integrates over this node IF it is a leaf.
    **/
    double integrate(Function *F);
    /**
     * Getter for the rectangle in this node.
     * */
    Rectangle* getRekt();

    int getLevel();
    vector<Node*> createFakeChildren();
    void createChildren(vector<Node*> children);
};
#endif