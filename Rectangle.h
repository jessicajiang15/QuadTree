#ifndef _RECTANGLE_H
#define _RECTANGLE_H 1
#include "Point.h"
#include <vector>
#include "Function.h"
#include <iostream>
//rectangle

class Rectangle
{
    private:
    /**
     * Cartesian coordinate of the top left corner of the rectangle.
     * */
    Point *point;
    /**
     * Width of the rectangle.
     * */
    double width;
    /**
     * Height of the rectangle.
     **/
    double height;

    public:
    /**
     * constructors
     * */
    Rectangle(double x, double y, double width, double height);
    Rectangle(Point *p, double width, double height);
    /**
     * Destructor
     * */
    virtual ~Rectangle()
    {
        delete point;
    }
    /**
     * Getter for area of rectangle. Necessary for approximate integral on rectangle region
     * */
     double getArea();
        /**
     * Gets the cartesian width of the rectangle– getter for width
     * */
    double getXInterval();
    /**
     * Gets the cartesian height of the rectangle– getter for height
     * */
    double getYInterval();
    /**
     * Okay, to be honest, I DON'T KNOW why there are two of the exact same getter methods– this 
     * is why you don't write code at 11 pm, but now I'm scared to delete them and then cause some
     * error somewhere else...
     * */
    double getWidth();
    double getHeight();
    /**
     * Gets cartesian x coordinate of the top left corner of the rectangle.
     * */
    double getX();
    /**
     * Gets cartesian y coordinate of the top left corner of the rectangle.
     * */
    double getY();
    /**
     * Gets the center x coordinate of the rectangle.
     * */
    double getCenterX();
    /**
     * Gets the center y coordinate of the rectangle.
     * */
    double getCenterY();
    /**
     * Integrates a function F over the region represented by this rectangle.
     * Dummy function– I don't actually know how to incorporate integration
     * with this code yet. Will be implemented soon.
     * */
    double integrate(Function *F);
    /**
     * Returns a midpoint rectangular prism approximation of the integral
     * of a function F over the region represented by this rectangle.
     * */
    double approx(Function *F);
    std::string toStringCoord();


};
#endif