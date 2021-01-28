#ifndef _GRAPHICSMECHANICS_H
#define _GRAPHICSMECHANICS_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "Point.h"

class GraphicsMechanics
{
    public:
    static int const WINDOW_HEIGHT=800;
    static int const WINDOW_WIDTH=800;
    static int const MENU_HEIGHT=100;
    static Point* convertFromCartesian(double minX, double maxX, double minY, double maxY, Point *p);
    static Point* convertToCartesian(double minX, double maxX, double minY, double maxY, Point *p);
    static double getXScale(double minX, double maxX);
    static double getYScale(double minY, double maxY);

};

#endif