#include "Node.h"
//Node of a tree, .cpp
Node::Node(Rectangle *s)
{
    this->orientation=0;
    this->square = s;
    Node::allNullESq();
    level = 0;
}

Node::Node(double x, double y, Node *parent, double width, double height, int orientation, int level)
{
    Rectangle *temp = new Rectangle(x, y, width, height);
    this->square = temp;
    this->orientation=orientation;
    cout<<"orientation: "<<orientation<<endl;
    this->level = level;
    cout<<"Rectangle x: "<<this->getRekt()->getX()<<endl;
    cout<<"Rectangle y: "<<this->getRekt()->getY()<<endl;
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