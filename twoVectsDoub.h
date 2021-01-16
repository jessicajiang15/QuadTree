#ifndef _TWOVECTSDOUB_H
#define _TWOVECTSDOUB_H 1
#include <vector>
//twovects

/**
 * A class that stores two vectors of type double. Specifically created to be able to return outboxes
 * and inboxes in one function so that the for loop+tree traversal does not need
 * to run twice for each of inboxes and outboxes.
 **/
class twoVectsDoub{

    public:
    /**
     * Constructor.
     **/
    twoVectsDoub(std::vector<double> v1, std::vector<double> v2);

    //supply. Supply is positive and corresponds to outboxes.
    std::vector<double> v1;

    //demand. Demand is negative and corresponds to inboxes.
    std::vector<double> v2;
    /**
     * Append to the first vector.
     **/
    void appendToV1(std::vector<double> t);
    /**
     * Append to the second vector.
     **/
    void appendToV2(std::vector<double> t);
    /**
     * Setter
     **/
    void setV1(std::vector<double> t);
    /**
     * Setter
     **/
    void setV2(std::vector<double> t);
    /**
     * Append one twoVectsDoub object to another. Appends v1 from other to this->v1, and appends
     * v2 from other to this->v2.
     **/
    void append(twoVectsDoub* other);



};

#endif