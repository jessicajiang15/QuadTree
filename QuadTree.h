#ifndef _QUADTREE_H
#define _QUADTREE_H 1
#include "Node.h"
#include <unordered_map>
#include "twoVects.h"
#include <math.h>
#include "twoVectsDoub.h"

class QuadTree
{

private:
/**
 * The root of the tree.
 * */
    Node *root;
    double scaleCutoff(double cutoff, int level);


public:
/**
 * Constructs a quad tree with the given root.
 * */
    QuadTree(Node *root);
    /**
     * Constructs a quad tree with an empty root.
     * */
    QuadTree();
    /**
     * Constructs a QuadTree with the given rectangle s.
     * */
    QuadTree(Rectangle *s, double minX, double maxX, double minY, double maxY);
    /**
     * Constructs a QuadTree given a list of nodes.
     * */
    QuadTree(vector<Node *> nodes);
    /**
     * Destructor
     * */
    virtual ~QuadTree()
    {
        delete root;
    }
    /**
     * Returns the size of the QuadTree
     * */
    int size(Node *n);
    /**
     * Returns a list of all of the nodes inside the QuadTree (Excludes leaves)
     * */
    vector<Node *> getNodes(Node *n);
    /**
     * Returns a list of all of the leaves inside the QuadTree
     * */
    vector<Node *> getLeaves(Node *n);
    /**
     * Returns all of the nodes and leaves inside the QuadTree as an entire vector, starting
     * from node n.
     * @param n starts from this node and returns everything below this node as a vector. 
     * parameter needed for recursion purposes.
     * */
    vector<Node *> asVector(Node *n);
    /**
     * Returns all of the nodes as a map.
     * TODO: implement this.
     * */
    unordered_map<int, Node *> asMap(Node *n);
    /**
     * Returns the size of this tree. In other words, size(root);
     * */
    int thisSize();
    /**
     * Getter for the root of this QuadTree
     * */
    Node *getRoot();
    /**
     * Setter for the root of this QuadTree
     * */
    void setRoot(Rectangle *s);
    //divides the tree given a function F; void is placeholder for now
    /**
     * Applies a multivariable variant of Adaptive Quadrature on this particular tree, starting 
     * from Node n and with a tolerance of tol
     * @param F the function that we are looking at
     * @param n the node we are starting the divide from, needed for recursive algorithm
     * @param tol the maximum absolute error that we are allowing between the analytical integral
     * over a region and the approximate integral over the region.
     * */
    void divide(double minX, double maxX, double minY, double maxY, Function *F, Node *n, double tol, int maximumLevel);
    /**
     * Returns a list of all of the outboxes corresponding to the region that this QuadTree represents
     * i.e. the boxes where sand needs to be removed from.
     * @param F the function that we are looking at
     * @param n the node we are starting to get outboxes from, needed for recursion
     * @param cutoff the minimum difference there can be in the function where we will count it
     * as an outbox.
     * */
    vector<Rectangle *> getOutBoxes(Node *n, Function *F, double cutoff);
    /**
     * Returns a list of all of the inboxes corresponding to the region that this QuadTree represents
     * i.e. the boxes where sand needs to be added to.
     * @param F the function that we are looking at
     * @param n the node we are starting to get inboxes from, needed for recursion
     * @param cutoff the minimum difference there can be in the function where we will count it
     * as an inbox.
     * */
    vector<Rectangle *> getInBoxes(Node *n, Function *F, double cutoff);
    /**
     * Returns a twoVector object, where v1 is the vector with all of the outboxes and v2 is the vector
     * with all of the inboxes
     * @param F the function that we are looking at
     * @param n the node we are starting to get all of the outboxes and inboxes from
     * @param cutoff the minimum difference there can be in the function where we will count it
     * as an inbox/outbox.
     * @return a twoVector object, with v1 being the outboxes and v2 being the inboxes.
     * */
    twoVects *getAllBoxes(Node *n, Function *F, double cutoff);
    /**
     * Given a function, divides this current QuadTree until the absolute error of the approximate
     * integral on each leaf of the QuadTree is within the given tolerance tol
     * @param F the function that we are looking at
     * @param tol the maximum tolerable error between the estimated integral and the actual integral
     * */
    void divideTree(double minX, double maxX, double minY, double maxY, Function *F, double tol, int maximumLevel);

    void draw(sf::RenderWindow*);
    void drawRoot(Node*, sf::RenderWindow*);
        void divideTreeNTimes(double minX, double maxX, double minY, double maxY, Node *n, int level);
    void divideCompMid(double minX, double maxX, double minY, double maxY, Node *n, Function *F, double tol, int maximumLevel);
    vector<double> getDifArray(Node *n, Function *F, double cutoff);
    twoVectsDoub getSupplyDemandAmt(Function *F, double cutoff);

};

#endif