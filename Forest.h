#ifndef _FOREST_H
#define _FOREST_H 1

#include "QuadTree.h"

class Forest
{
private:
    QuadTree **forest;
    int rows;
    int cols;
    double minCoordY;
    double minCoordX;
    double maxCoordY;
    double maxCoordX;
    double width;
    double height;
    int inRangeX(double x, int c);
    bool inRangeY(double y, int r);
    int index(int row, int col);
    double getCoordY(int r);
    double getCoordX(int c);
    //need the 2 functions that it is sitting in

public:
    virtual ~Forest()
    {
        delete forest;
    }
    Forest(QuadTree **forest);
    Forest(int row, int col, double minCoordY, double minCoordX, double maxCoordY, double maxCoordX);
    QuadTree *get(int r, int c);
    Point *getRC(double x, double y);
    //adds a QuadTree to
    bool add(QuadTree *t, int r, int c);
    //returns the starting number of rows.
    int numMinRows();
    //returns the starting number of columns
    int numMinCols();
    //returns the total number of cells there are.
    int totalCells();
    Point *getXYCoord(int r, int c);

    void divide(void *F);

    int findC(double x);
    int findR(double y);
    int binarySearchX(double x, int lower, int upper);
    int binarySearchY(double x, int lower, int upper);
    //returns total number of boxes where the sand will be moved in and out from
    //vector<Square*> viableBoxes();
    twoVects *getAllBoxes(void *F, double cutoff);
};
#endif