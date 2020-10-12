#ifndef _TWOVECTS_H
#define _TWOVECTS_H 1
#include <vector>
#include "Rectangle.h"
//twovects

class twoVects{

    public:
    twoVects(std::vector<Rectangle*> v1, std::vector<Rectangle*> v2);
    std::vector<Rectangle*> v1;
    std::vector<Rectangle*> v2;
    void appendToV1(std::vector<Rectangle*> t);
    void appendToV2(std::vector<Rectangle*> t);
    void setV1(std::vector<Rectangle*> t);
    void setV2(std::vector<Rectangle*> t);
    void append(twoVects* other);



};

#endif