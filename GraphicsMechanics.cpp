#include "GraphicsMechanics.h"

Point *GraphicsMechanics::convertFromCartesian(double minX, double maxX, double minY, double maxY, Point *p)
{
    double intervalX = maxX - minX;
    double xScale = WINDOW_WIDTH / intervalX;
    double intervalY = maxY - minY;
    double yScale = WINDOW_HEIGHT / intervalY;
    double xShiftCart = intervalX / 2;
    double xShiftSf = xShiftCart * xScale;
    double yShiftCart = intervalY / 2;
    double yShiftSf = yShiftCart * yScale;
    double x = p->getX();
    double y = p->getY();
    double newX = x * xScale + xShiftSf;
    double newY = y * yScale - yShiftSf;
    return new Point(newX, newY);
}

Point *GraphicsMechanics::convertToCartesian(double minX, double maxX, double minY, double maxY, Point *p)
{
    double intervalX = maxX - minX;
    double xScale = WINDOW_WIDTH / intervalX;
    double intervalY = maxY - minY;
    double yScale = WINDOW_HEIGHT / intervalY;
    double xShiftCart = intervalX / 2;
    double xShiftSf = xShiftCart * xScale;
    double yShiftCart = intervalY / 2;
    double yShiftSf = yShiftCart * yScale;
    double x = p->getX();
    double y = p->getY();
    double newX = (x - xShiftSf) / xScale;
    double newY = (y + yShiftSf) / yScale;
    return new Point(newX, newY);
}

double GraphicsMechanics::getXScale(double minX, double maxX)
{
    double intervalX = maxX - minX;
    double xScale = WINDOW_WIDTH / intervalX;
    return xScale;
}
double GraphicsMechanics::getYScale(double minY, double maxY)
{
    double intervalY = maxY - minY;
    double yScale = WINDOW_HEIGHT / intervalY;
    return yScale;
}