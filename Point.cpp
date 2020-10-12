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