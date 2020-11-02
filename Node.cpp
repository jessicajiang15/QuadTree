#include "Node.h"
//Node of a tree, .cpp
Node::Node(Rectangle *s)
{
    this->orientation=0;
    this->square = s;
    Node::allNullESq();
    level = 0;
        this->hasChildren=false;
}

Node::Node(double x, double y, Node *parent, double width, double height, int orientation, int level)
{
    Rectangle *temp = new Rectangle(x, y, width, height);
    this->square = temp;
    this->orientation=orientation;
    //cout<<"orientation: "<<orientation<<endl;
    this->level = level;
    //cout<<"Rectangle x: "<<this->getRekt()->getX()<<endl;
    //cout<<"Rectangle y: "<<this->getRekt()->getY()<<endl;
    this->hasChildren=false;

}

bool Node::isLeaf()
{
    return !hasChildren;
}

Node *Node::getParent()
{
    return p;
}

void Node::createChildren()
{
    //double x, double y, Node *parent, vector<Node *> siblings, double width, double height
    double width = square->getWidth();
    double height = square->getHeight();
    double y = square->getY();
    double x = square->getX();
    this->nw = new Node(x, y, this, width / 2, height / 2, 1, this->level + 1);
    this->ne = new Node(x + width / 2, y, this, width / 2, height / 2, 2, this->level + 1);
    this->se = new Node(x + width / 2, y - height / 2, this, width / 2, height / 2, 3, this->level + 1);
    this->sw = new Node(x, y - height / 2, this, width / 2, height / 2, 4, this->level + 1);
    this->square = nullptr;
    hasChildren=true;
}

vector<Node *> Node::getChildren()
{
    vector<Node *> temp;
    temp.push_back(this->nw);
    temp.push_back(this->ne);
    temp.push_back(this->sw);
    temp.push_back(this->se);
    return temp;
}

int Node::getRelativeOrientation()
{
    cout<<"HELLO"<<this->orientation<<endl;
    return this->orientation;
}

void Node::allNullESq()
{
    this->p = nullptr;
    this->ne = nullptr;
    this->nw = nullptr;
    this->se = nullptr;
    this->sw = nullptr;
}

void Node::setSquare(Square *s)
{
    this->square = s;
}

double Node::integrate(Function *F)
{
    if (square == nullptr)
    {
        return -1;
    }
    return square->integrate(F);
}

Rectangle *Node::getRekt()
{
    return square;
}

int Node::getLevel()
{
    return level;
}

vector<Node*> Node::createFakeChildren()
{
    double width = square->getWidth();
    double height = square->getHeight();
    double y = square->getY();
    double x = square->getX();
    vector<Node*> temp;
    Node *nwt = new Node(x, y, this, width / 2, height / 2, 1, this->level + 1);
    Node *net = new Node(x + width / 2, y, this, width / 2, height / 2, 2, this->level + 1);
    Node *set = new Node(x + width / 2, y - height / 2, this, width / 2, height / 2, 3, this->level + 1);
    Node *swt = new Node(x, y - height / 2, this, width / 2, height / 2, 4, this->level + 1);
    temp.push_back(nwt);
    temp.push_back(net);
    temp.push_back(set);
    temp.push_back(swt);
    return temp;
}

//    void createChildren(vector<Node*> children);
void Node::createChildren(vector<Node*> children)
{
    this->nw=children[0];
    this->ne=children[1];
    this->se=children[2];
    this->sw=children[3];
    hasChildren=true;
    this->square=nullptr;
}