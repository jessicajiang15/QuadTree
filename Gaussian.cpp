#include "Gaussian.h"


Gaussian::Gaussian(double rho, double p, double theta)
{
    type=2;
    this->aa=(pow(cos(theta),2)/pow(p,2))+(pow(p, 2)*pow(sin(theta),2)/pow(rho,2));
    this->bb=2*sin(theta)*cos(theta)*(1/pow(p,2)-pow(p,2)/pow(rho,2));
    this->cc=(pow(sin(theta),2)/pow(p,2))+(pow(p, 2)*pow(cos(theta),2)/pow(rho,2));
    /**
     * constructs a gaussian of the form A*exp(-(x-b)^2/(2c^2)+-(y-d)^2/(2e^2))
    **/


}

Gaussian::Gaussian(double a, double x1, double y1, double rho, int type)
{
    type=1;
    //constructs a gaussian of the form A*exp(-(x-b)^2/(2c^2)+-(y-d)^2/(2e^2))
    this->b=x1;
    this->d=y1;
    this->e=rho/sqrt(2);
    this->a=1/M_PI;
    this->c=1/sqrt(2);
}

Gaussian::Gaussian(double a, double b, double c, double d, double e) : Function()
{
    type=1;
    this->a=a;
    this->b=b;
    this->c=c;
    this->d=d;
    this->e=e;
}

double Gaussian::value(double x, double y)
{
    if(type==2)
    {
        return 0.6366218566*exp(-(aa*pow(x, 2)+bb*x*y+cc*pow(y,2)));
    }
    return this->a*exp(-pow(x-b,2)/(2*pow(c,2))-pow(y-d,2)/(2*pow(e,2)));
}