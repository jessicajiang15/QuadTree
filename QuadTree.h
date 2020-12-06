#ifndef _QUADTREE_H
#define _QUADTREE_H 1
#include "Node.h"
#include <unordered_map>
#include "twoVects.h"
#include <math.h>
#include "twoVectsDoub.h"
#include "tripleVect.h"

//A class representing a tree where each node has 4 children. Each node represents a single cell in the
//adaptive grid.
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
    /**
     * Draws the QuadTree out onto the screen. Unimportant graphics- related method.
     * */
    void draw(sf::RenderWindow*);
    /**
     * Draws the grid that stems from the Node passed in as a parameter. Main utility is 
     * @param Node* the node at where we want to start drawing the tree.
     * */
    void drawRoot(Node*, sf::RenderWindow*);
    /** method that has the main purpose of debugging. It a tree, starting from node n, level times.
     * @param minX maxX minY maxY parameters that define the boundaries of the forest that the QuadTree
     * lies in. This determines the width and height of each "cell", which in turn helps us create the
     * graphics rectangle needed to draw out the tree.
     * **/
    void divideTreeNTimes(double minX, double maxX, double minY, double maxY, Node *n, int level);
    /**
     * Divides the current tree by the criteria that the difference between the midpoint approximation on 
     * the node n and the sum of the riemann approximations of all its children is greater than tol.
     * @param tol gives how precisely you want your tree to be divided. It determines the maximum allowed
     * difference between the midpoint riemann sum of the current node and the sum of the midpoint sums of
     * its children, if it were to be divided further.
     * @param maximumLevel gives the maximum level that we want our tree to be divided to to avoid potential infinite
     * loops.
     * @param F is the function we are dividing our tree based on.
     * @param n is the node we are starting the division from.
     * */
    void divideCompMid(double minX, double maxX, double minY, double maxY, Node *n, Function *F, double tol, int maximumLevel);
    /**
     * Gives the array of the values of the integral apprximation of all the cells in this QuadTree,
     * where supply and demand can be extracted from this array.
     * It is currently unused in favor of directly obtaining supply and demand after looping through
     * the tree to get inboxes and outboxes. 
     * */
    vector<double> getDifArray(Node *n, Function *F, double cutoff);
    //currently unused in favor of the accurate version. Originally returned outboxes, inboxes, supply, demand
    //in lists stored in a tripleVects object.
    tripleVect *getAllRelevantVects(Node *n, Function *F, double cutoff);
    /**
     * returns the total integral of the cell represented by this QuadTree. 
     * Currently is using the inaccurate midPoint riemann sum for each cell.
     * */
    double normalize(Node *n, Function *F);
    /**
     * Same as divideCompMid, but instead uses the more accurate getAccurateApprox to calcualte the criteria
     * for division.
     * */
    void divideCompMidAcc(double minX, double maxX, double minY, double maxY, Node *n, Function *F, double tol, int maximumLevel, int accuracy);
    /**
     * Same as getAllRelevantVects, but uses the more accurate integral approximation.
     * */
    tripleVect* getAllRelevantVectsAcc(Node *n, Function *F, double cutoff, int accuracy);
    //unused
    twoVectsDoub getSupplyDemandAmt(Function *F, double cutoff);

};

#endif