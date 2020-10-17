#ifndef _GRAPHICSMECHANICS_H
#define _GRAPHICSMECHANICS_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Point.h"

class GraphicsMechanics
{
    public:
    static int WINDOW_HEIGHT;
    static int WINDOW_WIDTH;
    static Point* convertFromCartesian(double minX, double maxX, double minY, double maxY, Point *p);
    static Point* convertToCartesian(double minX, double maxX, double minY, double maxY, Point *p);
    static double getXScale(double minX, double maxX);
    static double getYScale(double minY, double maxY);


};

#endif