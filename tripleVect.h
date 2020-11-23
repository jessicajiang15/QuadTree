#ifndef _TRIPLEVECT_H
#define _TRIPLEVECT_H
#include <vector>
#include "Rectangle.h"
#include "twoVects.h"
#include "twoVectsDoub.h"

class tripleVect
{
    public:
    /**
     * Constructor.
     **/
    tripleVect(twoVects *rect, twoVectsDoub *doub);
    
    twoVects *rect;
    twoVectsDoub *doub;
    void appendRect(twoVects *rect);
    void appendDoub(twoVectsDoub *doub);
    void append(tripleVect* other);
    void setRect(twoVects *rect);
    void setDoub(twoVectsDoub *doub);

};

#endif