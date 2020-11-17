#include "twoVectsDoub.h"
//twovects

twoVectsDoub::twoVectsDoub(std::vector<double> v1, std::vector<double> v2)
{
    this->v1 = v1;
    this->v2 = v2;
}

void twoVectsDoub::appendToV1(std::vector<double> t)
{
    v1.insert(v1.end(), t.begin(), t.end());
}
void twoVectsDoub::appendToV2(std::vector<double> t)
{
    v2.insert(v2.end(), t.begin(), t.end());
}

void twoVectsDoub::setV1(std::vector<double> t)
{
    this->v1 = t;
}
void twoVectsDoub::setV2(std::vector<double> t)
{
    this->v2 = t;
}

void twoVectsDoub::append(twoVectsDoub* other)
{
    appendToV1(other->v1);
    appendToV2(other->v2);
}