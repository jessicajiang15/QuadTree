#ifndef _TESTEXPONENTIALFUNCTION_H
#define _TESTEXPONENTIALFUNCTION_H 1
#include "OneDFunction.h"
#include "math.h"

class TestExponentialFunction: public OneDFunction {
    public:
    TestExponentialFunction();
    virtual ~TestExponentialFunction()
    {
        
    }
    double value(double x);
};

#endif