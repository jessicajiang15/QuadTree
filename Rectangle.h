#ifndef _RECTANGLE_H
#define _RECTANGLE_H 1
#include "Point.h"
#include <vector>
#include "Function.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "GraphicsMechanics.h"
#include "string.h"
#include <iomanip>

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
    /**
     * The SFML rectangle object for graphics.
     * */
    sf::RectangleShape* rect;

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
     * with this code yet. Will be implemented soon (if ever, currently using
     * approximation methods).
     * */
    double integrate(Function *F);
    /**
     * Returns a midpoint rectangular prism approximation of the integral
     * of a function F over the region represented by this rectangle.
     * */
    double approx(Function *F);
    std::string toStringCoord();
    //draws the rectangle
    void draw(sf::RenderWindow *window);
    /**
     * Creates a rectangle with the given boundaries. The x values that define the rectangle will lie
     * between maxX and minX (minX<x<maxX), and the y values that define the rectangle will lie
     * between minY and maxY, so minY<y<maxY.
     * Its length will be |maxX-minX| and its width will be |maxY-minY|
     * */
    void createSfRectFromCartesian(double minX, double maxX, double minY, double maxY);
    /**
     * Gives a more accurate approximation of the integral by splitting up this rectangle into an
     * accuracy x accuracy grid and evaluating the midpoint rectangular prism volume for each
     * little rectangle, then adding them up.
     * */
    double getAccurateApprox(Function *F, int accuracy);
    void setColor(std::string s);

};
#endif