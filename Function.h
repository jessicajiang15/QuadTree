#ifndef _FUNCTION_H
#define _FUNCTION_H
#include <string>
#include <vector>

//Placeholder class to store many differnt kinds of 3D functions later. It is currently unused outside 
//of being an interface.

class Function
{
    private:
    //unused
    std::string functionStr;
        //unused
    std::vector<std::string> function;
    public:
    //unused
    Function(std::string function);
    Function();
    virtual double value(double x, double y);
    //TODO: implement this if necessary
    double derivative(double x, double y);
    //TODO: implement this if necessary
    double integrate(double xi, double xf, double yi, double yf);
    //unused
    virtual void normalize(double normConst);

};

#endif