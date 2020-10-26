#include "Gaussian.h"

Gaussian::Gaussian(double a, double b, double c, double d, double e) : Function()
{
    this->a=a;
    this->b=b;
    this->c=c;
    this->d=d;
    this->e=e;
}

double Gaussian::value(double x, double y)
{
    //     * constructs a gaussian of the form A*exp(-(x-b)^2/(2c^2))
    //-(x-b)^2/(2c^2)+-(y-d)^2/(2e^2
    return this->a*exp(-pow(x-b,2)/(2*pow(c,2))-pow(y-d,2)/(2*pow(e,2)));
}