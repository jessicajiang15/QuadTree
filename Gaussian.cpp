#include "Gaussian.h"

//Gaussian *final = new Gaussian(AFIN, RHO, P, THETA);
//Gaussian *initial = new Gaussian(AINIT, X1, Y1, RHO, 1);
Gaussian::Gaussian(double a, double rho, double p, double theta,double x1, double y1)
{
    type = 2;
    this->a = a;
    this->aa = ((cos(theta) * cos(theta)) / (p * p)) + (p * p * sin(theta) * sin(theta)) / (rho * rho);
    this->bb = 2 * sin(theta) * cos(theta) * (1 / (p * p) - p * p / (rho * rho));
    this->cc = (sin(theta) * sin(theta)) / (p * p) + (p * p * cos(theta) * cos(theta) / (rho * rho));
    /**
     * constructs a gaussian of the form A*exp(-(x-b)^2/(2c^2)+-(y-d)^2/(2e^2))
    **/
    normConst = 1;
    this->b=x1;
    this->d=y1;
}

Gaussian::Gaussian(double a, double rho, int type)
{
    type=1;
    //constructs a gaussian of the form A*exp(-(x-b)^2/(2c^2)+-(y-d)^2/(2e^2))
    this->b = 0;
    this->d = 0;
    this->e = rho / sqrt(2);
    this->a = 1 / M_PI;
    this->c = 1 / sqrt(2);
    normConst = 1;
}
Gaussian::Gaussian(double a, double b, double c, double d, double e, int type) : Function()
{
    //type = 1;
    this->a = a;
    this->b = b;
    this->c = c;
    this->d = d;
    this->e = e;
    normConst = 1;
}

double Gaussian::value(double x, double y)
{
    if (type == 2)
    {

        //std::cout << "TYPE 2" << std::endl;

        //std::cout << "cnst:" << a*normConst << std::endl;
        //std::cout << "aa:" << aa << std::endl;
        //std::cout << "bb:" << bb << std::endl;
        //std::cout << "cc:" << cc << std::endl;
        return a * normConst * exp(-(aa * (x-b) * (x-b) + bb * (x-b) * (y-d) + cc * (y-d) * (y-d)));
    }
    else if(type==1)
    {
        //std::cout << "TYPE 3" << std::endl;

        double temp=a*normConst*exp(-(x)*(x)-(y)*(y)/(rho*rho));
        return temp;
    }
                    //std::cout << "TYPE 1" << std::endl;

    //std::cout << "a*normconst:" << a * normConst << std::endl;
    //std::cout << "1/2*c*c:" << 1 / (2 * c * c) << std::endl;
    //std::cout << "1/(2*e*e):" << 1 / (2 * e * e) << std::endl;

    return this->normConst * this->a * exp(-(x) * (x) / (2 * c * c) - (y) * (y) / (2 * e * e));
}

void Gaussian::normalize(double normConst)
{
    this->normConst = normConst;
}

double Gaussian::getNormConst()
{
    return normConst;
}

double Gaussian::getOverallConst()
{
    return normConst*a;
}

    Gaussian::Gaussian(double a, double x1, double y1, double rho, std::string str)
    {
        this->type=3;
        this->a=a;
        this->b=x1;
        this->d=y1;
        this->rho=rho;
    }
