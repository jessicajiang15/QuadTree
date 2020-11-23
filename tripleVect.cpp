#include "tripleVect.h"
//twovects

tripleVect::tripleVect(twoVects *rect, twoVectsDoub *doub)
{
    this->doub=doub;
    this->rect=rect;
}

   void tripleVect::appendRect(twoVects *rect)
   {
       this->rect->append(rect);
   }
    void tripleVect::appendDoub(twoVectsDoub *doub)
    {
        this->doub->append(doub);
    }
    void tripleVect::append(tripleVect* other)
    {
        appendRect(other->rect);
        appendDoub(other->doub);
    }

    void tripleVect::setRect(twoVects *rect)
    {
        this->rect=rect;
    }
    void tripleVect::setDoub(twoVectsDoub *doub)
    {
        this->doub=doub;
    }