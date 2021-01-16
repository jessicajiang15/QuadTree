#ifndef _TRIPLEVECT_H
#define _TRIPLEVECT_H
#include <vector>
#include "Rectangle.h"
#include "twoVects.h"
#include "twoVectsDoub.h"

/**
 * class to store 4 vectors. This will be used as a container for the list of inboxes, outboxes, supply,
 * and demand.
 * */
class tripleVect
{
    public:
    /**
     * Constructor.
     **/
    tripleVect(twoVects *rect, twoVectsDoub *doub);
    /**
     * A twoVects object storing two vectors of rectangles representing outboxes and inboxes. The first 
     * vector is the outboxes list and the second is the inboxes.
     * */
    twoVects *rect;
    /**
     * A twoVects object storing 2 vectors of rectangles representing the supply and demand lists. The first
     * vector is the supply and the second is the demand.
    **/
    twoVectsDoub *doub;
    /**
     * Appends both of the vectors in the parameter rect to the end of the vectors in the twoVects 
     * object of this object, v1 of rect to v1 of this->rect, and likewise for v2.
     * */
    void appendRect(twoVects *rect);
        /**
     * Appends both of the vectors in the parameter doub to the end of the vectors in the twoVectsDoub 
     * object of this object, v1 of the parameter doub to v1 of this->doub, and likewise for v2.
     * */
    void appendDoub(twoVectsDoub *doub);
    /**
     * Appends the corresponding vectors in each of doub and rect in other onto the end of the current
     * tripleVects' doub and rect.
     * */
    void append(tripleVect* other);
    /**
     * setter for the twoVects object rect
     * */
    void setRect(twoVects *rect);
    /**
     * Setter for the twoVectsDoub object doub
     * */
    void setDoub(twoVectsDoub *doub);

};

#endif