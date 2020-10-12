#ifndef _QUADTREE_H
#define _QUADTREE_H 1
#include "Node.h"
#include <unordered_map>
#include "twoVects.h"

class QuadTree
{

private:
    Node *root;

public:
    QuadTree(Node *root);
    QuadTree();
    QuadTree(Rectangle *s);
    QuadTree(vector<Node *> nodes);
    virtual ~QuadTree()
    {
        delete root;
    }
    void draw();
    void traverse(Node *node);
    Node *get(int index);
    int size(Node *n);
    vector<Node *> getNodes(Node *n);
    vector<Node *> getLeaves(Node *n);
    void traverseTree();
    vector<Node *> asVector(Node *n);
    unordered_map<int, Node *> asMap(Node *n);
    int thisSize();
    Node *getRoot();
    void setRoot(Rectangle *s);
    //divides the tree given a function F; void is placeholder for now
    void divide(void *F);
    vector<Rectangle *> getOutBoxes(Node *n, void *F, double cutoff);
    vector<Rectangle *> getInBoxes(Node *n, void *F, double cutoff);
    twoVects *getAllBoxes(Node *n, void *F, double cutoff);


};

#endif