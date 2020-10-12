#include "Forest.h"

Forest::Forest(int rows, int cols, double minCoordY, double minCoordX, double maxCoordY, double maxCoordX)
{
    *forest = new QuadTree[rows * cols];
    this->rows = rows;
    this->cols = cols;
    this->minCoordX = minCoordX;
    this->minCoordY = minCoordY;
    this->maxCoordX = maxCoordX;
    this->maxCoordY = maxCoordY;
    double width = (maxCoordX - minCoordX) / cols;
    double height = (maxCoordY - minCoordY) / rows;
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
            Rectangle *temp = new Rectangle(Forest::getCoordX(c), Forest::getCoordY(r), width, height);
            forest[index(r, c)] = new QuadTree(temp);
            //double x, double y, double width, double height
        }
    }
}
int Forest::index(int row, int col)
{
    return row * col + col;
}

QuadTree *Forest::get(int r, int c)
{
    return this->forest[index(r, c)];
}

Point *Forest::getXYCoord(int r, int c)
{
    double x = Forest::getCoordX(c);
    double y = Forest::getCoordY(r);
    Point *temp = new Point(x, y);
    return temp;
}

double Forest::getCoordX(int c)
{
    return c * width + this->minCoordX;
}

//double check!
double Forest::getCoordY(int r)
{
    int totalHeight = maxCoordY - minCoordY;
    return (totalHeight - r) * height + this->minCoordY;
}

void Forest::divide(void *F)
{
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
            forest[index(r, c)]->divide(F);
        }
    }
}

int Forest::numMinCols()
{
    return cols;
}

int Forest::numMinRows()
{
    return rows;
}

//NOTE: IT RETURNS A POINT, BUT THE "POINT" CONTAINS INFORMATION ABOUT THE ROW AND COLUMN
Point *Forest::getRC(double x, double y)
{
    return new Point(findC(x), findR(y));
}

int Forest::findC(double x)
{
    return binarySearchX(x, 0, cols);
}
int Forest::findR(double y)
{
    return binarySearchY(y, 0, rows);
}

bool Forest::inRangeY(double y, int r)
{
    return y >= Forest::getCoordY(r) - height && y <= Forest::getCoordY(r) ? true : false;
}

int Forest::inRangeX(double x, int c)
{
    if (x <= Forest::getCoordX(c) + width && x >= Forest::getCoordX(c))

    {
        return 0;
    }
    else if (x > Forest::getCoordX(c) + width)
    {
        return 1;
    }
    else
    {
        return -1;
    }
}

int Forest::binarySearchX(double x, int lower, int upper)
{
    int mid = (lower / 2 + upper / 2);
    int temp = inRangeX(x, mid);
    switch (temp)
    {
    case 1:
    {
        return binarySearchX(x, mid, upper);
    }
    case 0:
    {
        return mid;
    }
    case -1:
    {
        return binarySearchX(x, lower, mid);
    }
    }
}

int Forest::binarySearchY(double y, int lower, int upper)
{
    int mid = (lower / 2 + upper / 2);
    int temp = inRangeY(y, mid);
    switch (temp)
    {
    case 1:
    {
        return binarySearchY(y, lower, mid);
    }
    case 0:
    {
        return mid;
    }
    case -1:
    {
        return binarySearchY(y, mid, upper);
    }
    }
}

    twoVects* Forest::getAllBoxes(void *F, double cutoff)
    {
        vector<Rectangle*> v1;
        vector<Rectangle*> v2;
        twoVects* temp=new twoVects(v1,v2);
        for(int r=0;r<rows;r++)
        {
            for(int c=0;c<cols;c++)
            {
                twoVects* t=this->forest[index(r,c)]->getAllBoxes(this->forest[index(r,c)]->getRoot(),F, cutoff);
                temp->append(t);
            }
        }
        return temp;
    }
