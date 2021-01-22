#include "TestExponentialFunction.h"

    TestExponentialFunction::TestExponentialFunction():OneDFunction()
    {

    }


double TestExponentialFunction::value(double x)
{
    return exp(x);
}