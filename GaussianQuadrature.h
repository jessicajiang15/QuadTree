#ifndef _GAUSSIAN_QUADRATURE_H
#define _GAUSSIAN_QUADRATURE_H 1
#include "twoVectsDoub.h"
#include "LegendrePolynomial.h"
#include "Function.h"
#include "OneDFunction.h"


class GaussianQuadrature{
    private:
    //how many degrees of freedom you have
        int n;
        int m;
        double acc;
    public:
        GaussianQuadrature(int, double);
        GaussianQuadrature(int, int, double);
        virtual ~GaussianQuadrature()
        {

        }
        twoVectsDoub* getNWeightsAndAbscissae(int);
        double getOneDIntegral(double xi, double xf, OneDFunction *F, int);
        double getTwoDIntegral(double xi, double xf, double yi, double yf, Function *F, int);
        void setAcc(double acc);
        twoVectsDoub* getMWeightsAndAbscissae(int);


};

#endif