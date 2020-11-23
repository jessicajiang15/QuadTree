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
    Function(std::string function);
    Function();
    virtual double value(double x, double y);
    double derivative(double x, double y);
    double integrate(double xi, double xf, double yi, double yf);
    virtual void normalize(double normConst);

};

#endif