#include "Point.h"
//generic point class containing an x and y value pair

    Point::Point(double x, double y)
    {
        this->x=x;
        this->y=y;
    }


double Point::getX()
{
    return x;
}
    double Point::getY()
    {
        return y;
    }

double Point::distanceTo(Point *p2)
{
    return sqrt(pow(p2->getX()-this->getX(),2)+pow(p2->getY()-this->getY(),2));
}