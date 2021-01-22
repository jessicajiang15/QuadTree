#ifndef _LEGENDREPOLYNOMIAL_H
#define _LEGENDREPOLYNOMIAL 1
#include <math.h>
#include <iostream>
#include <vector>
#include <iomanip>

class LegendrePolynomial
{
    private:
        int n;
        std::vector<double> zeros;

    public:
    LegendrePolynomial(int n);
    virtual ~LegendrePolynomial()
    {

    }
    double evaluate(double, int);
    double nderivative(double, int);
    double value(double);
    double derivative(double);
    std::vector<double> calcZeros(double, int); 
    double getGuess(int);
    double newtonRaphsonIthRoot(int, double, int);
        void initializeZeros(double, int);

    std::vector<double> getZeros();
};

#endif