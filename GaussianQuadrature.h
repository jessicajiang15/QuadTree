#ifndef _GAUSSIAN_QUADRATURE_H
#define _GAUSSIAN_QUADRATURE_H 1
#include "twoVectsDoub.h"
#include "LegendrePolynomial.h"
#include "Function.h"
#include "OneDFunction.h"
#include <iostream>
#include <fstream>
#include <iomanip>

class GaussianQuadrature
{
private:
    //how many degrees of freedom you have
    int n;
    int m;
    double acc;
    twoVectsDoub *NWeightsAndAbscissae;
    twoVectsDoub *MWeightsAndAbscissae;

    twoVectsDoub *getNWeightsAndAbscissae();
    twoVectsDoub *getMWeightsAndAbscissae();

    twoVectsDoub *initializeWeightsAndAbscissae(int MAX_ITERATIONS, int n);
    

public:
    GaussianQuadrature(int n, double acc, int MAX_ITERATIONS);
    GaussianQuadrature(int n, int m, double acc,int MAX_ITERATIONS);
    virtual ~GaussianQuadrature()
    {
    }
    double getOneDIntegral(double xi, double xf, OneDFunction *F, int);
    double getTwoDIntegral(double xi, double xf, double yi, double yf, Function *F, int MAX_ITERATIONS);
    //double xi, double xf, double yi, double yf, Function *F, int MAX_ITERATIONS
    void setAcc(double acc);
    void appendZerosToFiles(int MAX_ITERATIONS, std::ofstream *file);
    double getOneDIntegralFromFile(std::ifstream *weights, std::ifstream *nodes, double xi, double xf, OneDFunction *F);
    double getTwoDIntegralFromFile(std::ifstream *weights2, std::ifstream *nodes2, std::ifstream *weights1, std::ifstream *nodes1, double xi, double xf, double yi, double yf, Function *F);
    void initializeFromFile(std::ifstream *weights1, std::ifstream *nodes1, std::ifstream *weights2, std::ifstream *nodes2, double xi, double xf, double yi, double yf, Function *F);
};

#endif