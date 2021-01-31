#include "Test2DExpFcn.h"
Test2DExpFcn::Test2DExpFcn()
{

}

double Test2DExpFcn::value(double x, double y)
{
    return exp(-x*x)*exp(-y*y);
}