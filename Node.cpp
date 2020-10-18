#include "Node.h"
//Node of a tree, .cpp
Node::Node(Rectangle *s)
{
    this->square = s;
    Node::allNullESq();
    level = 0;
}

Node::Node(double x, double y, Node *parent, vector<Node *> siblings, double width, double height, int orientation, int level)
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
    this->level = level;
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
    this->nw = new Node(x, y, this, temp, width / 2, height / 2, 1, this->level + 1);
    this->ne = new Node(x + width / 2, y, this, temp, width / 2, height / 2, 2, this->level + 1);
    this->se = new Node(x + height / 2, y + height / 2, this, temp, width / 2, height / 2, 3, this->level + 1);
    this->sw = new Node(x, y + height / 2, this, temp, width / 2, height / 2, 4, this->level + 1);
    this->square = nullptr;
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