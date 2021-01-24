#ifndef _GAUSSIAN_QUADRATURE_H
#define _GAUSSIAN_QUADRATURE_H 1
#include "twoVectsDoub.h"
#include "LegendrePolynomial.h"
#include "Function.h"
#include "OneDFunction.h"
#include <iostream>
#include <fstream>


class GaussianQuadrature{
    private:
    //how many degrees of freedom you have
        int n;
        int m;
        double acc;
        twoVectsDoub* getNWeightsAndAbscissae(int MAX_ITERATIONS);
        twoVectsDoub* getMWeightsAndAbscissae(int MAX_ITERATIONS);
        twoVectsDoub* getWeightsAndAbscissae(int MAX_ITERATIONS, int n);
    public:
        GaussianQuadrature(int n, double acc);
        GaussianQuadrature(int n, int m, double acc);
        virtual ~GaussianQuadrature()
        {

        }
        double getOneDIntegral(double xi, double xf, OneDFunction *F, int);
        double getTwoDIntegral(double xi, double xf, double yi, double yf, Function *F, int MAX_ITERATIONS);
        //double xi, double xf, double yi, double yf, Function *F, int MAX_ITERATIONS
        void setAcc(double acc);
        void appendZerosToFiles(double acc, int MAX_ITERATIONS, std::ofstream *file);

};

#endif