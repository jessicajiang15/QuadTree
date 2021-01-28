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
    std::vector<double> calcZeros(double, int);
    double getGuess(int);
    double newtonRaphsonIthRoot(int, double, int);
    void initializeZeros(double, int);
    double nderivative(double, int);
    double evaluate(double, int);

public:
    LegendrePolynomial(int n, double acc, int MAX_ITERATIONS);
    virtual ~LegendrePolynomial()
    {
    }
    double value(double);
    double derivative(double);
    std::vector<double> getZeros();
};

#endif