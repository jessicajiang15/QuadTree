#include "Square.h"
//rectangle

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
    this->height=width;
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

//integrate the function
double Rectangle::integrate(Function *F)
{
    return 0;
}

//gives a mid point riemann sum approximation of F on this interval
double Rectangle::approx(Function *F)
{
    return getArea()*F->value(point->getX()+width/2,point->getY()-height/2);
}

std::string Rectangle::toStringCoord()
{
    return "("+std::to_string(getCenterX())+", "+std::to_string(getCenterY())+")";
}