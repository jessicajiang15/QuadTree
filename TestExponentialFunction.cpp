#include "TestExponentialFunction.h"

    TestExponentialFunction::TestExponentialFunction():OneDFunction()
    {

    }


double TestExponentialFunction::value(double x)
{
    return (1/M_PI)*exp(-4*x*x);
}