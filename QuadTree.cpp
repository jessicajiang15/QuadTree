#include "QuadTree.h"

QuadTree::QuadTree(Rectangle *s)
{
    this->root=new Node(s);
}

Node *QuadTree::get(int index)
{

}

QuadTree::QuadTree()
{
    root=nullptr;
}
int QuadTree::size(Node *n)
{
    int count=1;
    if (n->isLeaf())
    {
        return 1;
    }
    vector<Node *> children;
    children = n->getChildren();
   int t1 = size(children[0]);
    int t2 = size(children[1]);
    int t3 = size(children[2]);
    int t4 = size(children[3]);


    return count+t1+t2+t3+t4;
}
/*
    check for accuracy
    */
vector<Node *> QuadTree::getNodes(Node *n)
{
    vector<Node *> temp;
    if (n->isLeaf())
    {
        return temp;
    }
    else
    {
        temp.push_back(n);
    }

    vector<Node *> children;
    children = n->getChildren();
    vector<Node *> t1 = asVector(children[0]);
    vector<Node *> t2 = asVector(children[1]);
    vector<Node *> t3 = asVector(children[2]);
    vector<Node *> t4 = asVector(children[3]);

    temp.insert(temp.end(), t1.begin(), t1.end());
    temp.insert(temp.end(), t2.begin(), t2.end());
    temp.insert(temp.end(), t3.begin(), t3.end());
    temp.insert(temp.end(), t4.begin(), t4.end());

    return temp;
}
vector<Node *> QuadTree::getLeaves(Node *n)
{
    vector<Node *> temp;
    if (n->isLeaf())
    {
        temp.push_back(n);
        return temp;
    }

    vector<Node *> children;
    children = n->getChildren();
    vector<Node *> t1 = asVector(children[0]);
    vector<Node *> t2 = asVector(children[1]);
    vector<Node *> t3 = asVector(children[2]);
    vector<Node *> t4 = asVector(children[3]);

    temp.insert(temp.end(), t1.begin(), t1.end());
    temp.insert(temp.end(), t2.begin(), t2.end());
    temp.insert(temp.end(), t3.begin(), t3.end());
    temp.insert(temp.end(), t4.begin(), t4.end());

    return temp;
}
void QuadTree::traverseTree()
{
}

vector<Node *> QuadTree::asVector(Node *n)
{
    vector<Node *> temp;
    temp.push_back(n);
    if (n->isLeaf())
    {
        return temp;
    }

    vector<Node *> children;
    children = n->getChildren();
    vector<Node *> t1 = asVector(children[0]);
    vector<Node *> t2 = asVector(children[1]);
    vector<Node *> t3 = asVector(children[2]);
    vector<Node *> t4 = asVector(children[3]);

    temp.insert(temp.end(), t1.begin(), t1.end());
    temp.insert(temp.end(), t2.begin(), t2.end());
    temp.insert(temp.end(), t3.begin(), t3.end());
    temp.insert(temp.end(), t4.begin(), t4.end());

    return temp;
}

unordered_map<int, Node *> QuadTree::asMap(Node *n)
{

}
void QuadTree::draw()
{
}
void QuadTree::traverse(Node *node)
{
}

int QuadTree::thisSize()
{
    return QuadTree::size(this->getRoot());
}

Node* QuadTree::getRoot()
{
    return this->root;
}

void QuadTree::setRoot(Rectangle *s)
{
    this->root=new Node(s);
}


void QuadTree::divide(void *F)
{

}