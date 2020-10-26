#ifndef _FUNCTION_H
#define _FUNCTION_H
#include <string>
#include <vector>
//Placeholder

class Function
{
    private:
    std::string functionStr;
    std::vector<std::string> function;
    public:
    //assumes you are a function of x and y. NO powers!!! i just want to see if this works...
    Function(std::string function);
    Function();
    virtual double value(double x, double y);
    double derivative(double x, double y);
    double integrate(double xi, double xf, double yi, double yf);

};

#endif