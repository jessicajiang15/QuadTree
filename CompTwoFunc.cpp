#include "CompTwoFunc.h"

    CompTwoFunc::CompTwoFunc(Function *initial, Function *final)
    {
        this->initial=initial;
        this->final=final;

    }

    double CompTwoFunc::value(double x, double y)
    {
        return initial->value(x, y)-final->value(x, y);
    }