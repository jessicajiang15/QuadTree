#ifndef _POINT_H
#define _POINT_H 1
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
};
#endif