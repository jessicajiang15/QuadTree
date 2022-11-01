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
    double normConst;
    double rho;
    int type;

    public:
    /**
     * This class can store 3 different Gaussian function forms.
     * Constructor 1 forms a gaussian of the form A*exp(-(x-b)^2/(2c^2)+-(y-d)^2/(2e^2))
     * Constructor 2 forms a gaussian of the form a*E^[-(x-X1)^2-(y-Y1)^2/RHO^2]
     * * Constuctor 3 gives a gaussian of the form AFIN*E^-[aa*x^2+bb*x*y+cc*y^2] where:
 * aa=(Cos[THETA]^2/P^2+(P^2)Sin[theta]^2/RHO^2)
 * bb=2 * Sin[THETA] * Cos[THETA] *(1/P^2 - P^2/RHO^2)
 * cc=Sin[THETA]^2/P^2+(P^2) (Cos[THETA]^2)/RHO^2
     * */
    //type 0
    Gaussian(double a, double b, double c, double d, double e, int type);
    //type 1
    Gaussian(double a, double rho, int type);
    //type 2
    Gaussian(double a,double rho, double p, double theta,double x1, double y1);

    Gaussian(double a, double x1, double y1, double rho, std::string str);
    /**
     * Evaluates the function at the cartesian point (x, y)
     * */
    double value(double x, double y) override;
    /*
    * Setter for normConst which normalizes the gaussian.
    */
    void normalize(double normConst) override;
    /**
     * Getter for the normConst
     * */
    double getNormConst();
    double getOverallConst();
};
#endif