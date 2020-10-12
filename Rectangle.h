#ifndef _RECTANGLE_H
#define _RECTANGLE_H 1
#include "Point.h"
#include <vector>
#include "Function.h"
//rectangle

class Rectangle
{
    private:
    Point *point;
    double width;
    double height;

    public:
    Rectangle(double x, double y, double width, double height);
    Rectangle(Point *p, double width, double height);
    virtual ~Rectangle()
    {
        delete point;
    }
     double getArea();
    double getXInterval();
    double getYInterval();
    double getWidth();
    double getHeight();
    int getLayer();
    double getX();
    double getY();
    double getCenterX();
    double getCenterY();
    double integrate(Function *F);
    double approx(Function *F);
    double area();

};
#endif