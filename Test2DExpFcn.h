#ifndef _TEST2DEXPFCN_H
#define _TEST2DEXPFCN_H 1
#include "Function.h"
#include "math.h"

class Test2DExpFcn: public Function {
    public:
    Test2DExpFcn();
    virtual ~Test2DExpFcn()
    {
        
    }
    double value(double x, double y);
};

#endif