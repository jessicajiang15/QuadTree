#ifndef _POINT_H
#define _POINT_H 1
#include "math.h"

//generic point class containing an x and y value pair
class Point
{
    private:
    double x;
    double y;

    public:
    Point(double x, double y);
    double getX();
    double getY();
    /**
     * Returns the euclidean distance between this point and p2.
     * */
    double distanceTo(Point *p2);
};
#endif