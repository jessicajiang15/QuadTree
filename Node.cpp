#include "Node.h"

Node::Node(Rectangle *s)
{
    this->square=s;
    Node::allNullESq();
}

Node::Node(double x, double y, Node *parent, vector<Node *> siblings, double width, double height, int orientation)
{
    Rectangle *temp = new Rectangle(x, y, width, height);
    this->square = temp;
    this->siblings = siblings;
    for (int i = 0; i < siblings.size(); i++)
    {
        if (siblings[i]->getRelativeOrientation() == orientation)
        {
            continue;
        }
        switch (siblings[i]->getRelativeOrientation())
        {
        case 1:
        {
            nw = siblings[i];
            break;
        }
        case 2:
        {
            ne = siblings[i];
            break;
        }
        case 3:
        {
            se = siblings[i];
            break;
        }
        case 4:
        {
            sw = siblings[i];
            break;
        }
        }
    }
}

bool Node::isLeaf()
{
    return sw == nullptr;
}

Node *Node::getParent()
{
    return p;
}
vector<Node *> Node::getSiblings()
{
    return siblings;
}
void Node::createChildren()
{
    vector<Node *> temp;
    temp.push_back(this->nw);
    temp.push_back(this->ne);
    temp.push_back(this->se);
    temp.push_back(this->sw);

    //double x, double y, Node *parent, vector<Node *> siblings, double width, double height
    double width = square->getWidth();
    double height = square->getHeight();
    double y = square->getY();
    double x = square->getX();
    this->nw = new Node(x, y, this, temp, width / 2, height / 2, 1);
    this->ne = new Node(x + width / 2, y, this, temp, width / 2, height / 2, 2);
    this->se = new Node(x + height / 2, y + height / 2, this, temp, width / 2, height / 2, 3);
    this->sw = new Node(x, y + height / 2, this, temp, width / 2, height / 2, 4);
    this->square=nullptr;
}
Node *Node::getIndex(int i)
{
    return nullptr;
}
//1-4 in order of the instance variables above
Node *Node::getChild(int i)
{
    switch (i)
    {
    case 1:
    {
        return nw;
    }
    case 2:
    {
        return ne;
    }
    case 3:
    {
        return se;
    }
    case 4:
    {
        return sw;
    }
    }
    return nullptr;
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
        return orientation;
    }

void Node::allNullESq()
{
    this->p=nullptr;
    this->ne=nullptr;
    this->nw=nullptr;
    this->se=nullptr;
    this->sw=nullptr;
}

void Node::setSquare(Square *s)
{
    this->square=s;
}

void Node::initializeSquare(double width,double height)
{
    
}

double Node::integrate(void* F)
{
    if(square==nullptr)
    {
        return -1;
    }
    return square->integrate(F);
}

Rectangle* Node::getRekt()
{
    return square;
}