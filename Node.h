#ifndef _NODE_H
#define _NODE_H 1
#include "Square.h"
using namespace std;
//A node inside the QuadTree. Contains information about the children of this Node, the area that it represents
//on the grid (via the rectangle).
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
    Point *temp;
    //Is this node a leaf, or not?
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
    /**
     * Returns at what level we are in the tree. Here, the level refers to the depth of the node.
     * If it is the root, it is at level 0, If the node has 1 parent, it is at level 1, and so on.
     * This is important because we need to scale the cutoff to match with the depth so that
     * we don't throw out all of the precise boxes.
     * */
    int getLevel();
    /**
     * Creates the hypothetical children this node would have, but doesn't actually create children for it.
     * It is important because we want to compare the integral of the hypothetical children to the current
     * integral to determine if we want to divide this node or not.
     * */
    vector<Node*> createFakeChildren();
    /**
     * Divides the current node into 4 and gives it 4 children. It also removes its status as a leaf.
     * Assigns its NE, NW, SE, SW children from null to those in the vector.
     * @param children its to-be children.
     * */
    void createChildren(vector<Node*> children);
};
#endif