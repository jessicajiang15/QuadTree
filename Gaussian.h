#ifndef _GAUSSIAN_H_
#define _GAUSSIAN_H_
#include "Function.h"
#include "math.h"

class Gaussian : public Function
{
    /**
     * constructs a gaussian of the form A*exp(-(x-b)^2/(2c^2)+-(y-d)^2/(2e^2))
    **/
   private:
    double a;
    double b;
    double c;
    double d;
    double e;
    double aa;
    double cc;
    double bb;
    int type;

    public:
    Gaussian(double a, double b, double c, double d, double e);
    Gaussian(double a, double x1, double y2, double rho, int type);
    Gaussian(double rho, double p, double theta);
    double value(double x, double y) override;

};
#endif