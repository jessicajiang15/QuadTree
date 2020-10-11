#include "Square.h"

 Rectangle::Rectangle(double x, double y, double width, double height)
{
    Point *point=new Point(x, y);
    this->point=point;
    this->width=width;
    this->height=height;
}

Rectangle::Rectangle(Point *p, double width, double y)
{
    this->point=p;
    this->width=width;
    this->height=height;
}

double Rectangle::getArea()
{
    return width*height;
    return 0;
}
double Rectangle::getXInterval()
{
    return width;
}
double Rectangle::getYInterval()
{
    return height;
}
double Rectangle::getWidth()
{
    return width;
}
int Rectangle::getLayer()
{
    return height;
}

double Rectangle::getX()
{
    return this->point->getX();
}

double Rectangle::getY()
{
    return this->point->getY();
}

double Rectangle::getCenterX()
{
    return width/2+point->getX();
}

double Rectangle::getCenterY()
{
    return height/2+point->getY();
}

double Rectangle::getHeight()
{
    return height;
}