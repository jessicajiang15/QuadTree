#ifndef _FOREST_H
#define _FOREST_H 1
#include "QuadTree.h"
#include <fstream>



class Forest
{
private:
    /**
    * A 2D array of QuadTrees allocated as a single 1D array to be more memory efficient.
    * For index access, DO NOT use double brackets– use the provided index(r, c) function
    * as it is allocated as a single array on the heap.
    **/
    QuadTree **forest;
    /**
     * Number of rows in the 2D array.
     * This is NOT the number of rows after the tree has divided–
     * this is the starting number of rows in the forest.
     **/
    int rows;
    /**
     * Starting number of columns in the 2D array.
     **/
    int cols;
    /**
     * The minimum Y coordinate this forest spans to.
    */
    double minCoordY;
    /**
     * The minimum X coordinate this forest spans to.
    */
    double minCoordX;
    /**
     * The maximum Y coordinate this forest spans to.
    */
    double maxCoordY;
    /**
     * The maximum X coordinate this forest spans to.
    */
    double maxCoordX;
    /**
     * STARTING width of each cell. Stored for convenience.
    */
    double width;
    /**
     * Starting height of each cell. Stored for convenience.
    */
    double height;
    /**
     * Helper function to determine if a given x value is covered by a cell at column c.
     * Necessary for determining which cell a given x, y coordinate falls in.
    */
    int inRangeX(double x, int c);
    /**
     * Helper function to determine if a given y value is covered by a cell at row r.
     * Necessary for determining which cell a given x, y coordinate falls in.
    */
    bool inRangeY(double y, int r);

    /**
     * Obtains the cartesian y coordinate of a given row r.
     **/
    double getCoordY(int r);
        /**
     * Obtains the cartesian x coordinate of a given col c.
     **/
    double getCoordX(int c);
     int maximumLevel;

public:
/**
 * Destructor.
 **/
    virtual ~Forest()
    {
        delete forest;
    }
    /**
     * Constructor that creates a new forest an already initialized 2D array of QuadTrees.
     * Not sure when this might be used, but it's included just in case.
     **/
    Forest(QuadTree **forest);
    /**
     * Constructor that creates a new forest from the parameters.
     **/
    Forest(int row, int col, double minCoordX,double maxCoordX, double minCoordY, double maxCoordY);
    /**
     * Retrieves the QuadTree at the given array indicies
     **/
    QuadTree *get(int r, int c);
    /**
     * Retrieves the corresponding cell given cartesian x, y coordinates
     * @return a point object containing the cell row and the cell col as its indicies
     * THIS DOES NOT RETURN A CARTESIAN POINT. IT IS JUST A WAY TO RETURN BOTH THE ROW AND COL
     * IN THE SAME FUNCTION.
     **/
    Point *getRC(double x, double y);
    /**
     * Adds a QuadTree to the cell with indicies r, c.
     * @return whether or not the QuadTree was successfully added.
     **/
    bool add(QuadTree *t, int r, int c);
    /**
     * @return starting number of rows.
     **/
    int numMinRows();
    /**
     * @return starting number of cols.
     **/
    int numMinCols();
    /**
     * @return starting total number of cells.
     **/
    int totalCells();
    /**
     * Given a cell with r, c, returns the top left corner cartesian coordinate of the square
     * this cell would correspond to.
     * @param r the row index of the cell that we want the cartesian coordinate of
     * @param c the col index of the cell we want the cartesian coordinate of
     * @return a cartesian coordinate corresponding to the cell indicies r, c
     **/
    Point *getXYCoord(int r, int c);
    /**
     * Divides each cell in this forest with an adapted Adaptive Quadrature method
     * @param F the function the forest is applied to
     * @param tol the minimum amount of absolute error where we say to, "I'll allow that."
     **/
    void divide(Function *F, double tol);
    /**
     * Given an x, find the column index in the forest 2D array that contains that x value.
     * @param x the cartesian x coordinate we want to convert into a column index
     * @return the column index containing the cartesian x coordinate we are interested in
     **/
    int findC(double x);
    /**
     * Given an y, find the row index in the forest 2D array that contains that y value.
     * @param y the cartesian y coordinate we want to convert into a row index
     * @return the row index containing the cartesian y coordinate we are interested in
     **/
    int findR(double y);
    /**
     * A binary search method to find the row indicies given a cartesian x value.
     * @param x the cartesian x coordinate we want to convert into a col index
     * @return the row index that does actually have our x value
     **/
    int binarySearchX(double x, int lower, int upper);
    /**
     * A binary search method to find a given y value.
     * @param x the cartesian y coordinate we want to convert into a row index
     * @return the row index containing the cartesian y coordinate we are interested in
     **/
    int binarySearchY(double x, int lower, int upper);
    /**
     * Returns a twoVects object with v1 being the inboxes and v2 being the outboxes
     * @param F the function we are interested in
     * @param cutoff the minimum allowed difference we will allow
     * @return a twoVects object containing vectors of inboxes and outboxes
     **/
    twoVects *getAllBoxes(Function *F, double cutoff);
    void appendOutboxesToFile(ofstream *file, double cutoff, Function *F);
    void appendInboxesToFile(ofstream *file, double cutoff, Function *F);
    void draw(sf::RenderWindow*);
    QuadTree** getForest();
        /**
     * Helper function intended to help access a cell at index r, c in the forest, as the forest
     * is allocated as a single 1D array.
     **/
    int index(int row, int col);
    //void divideTreeNTimes(double minX, double maxX, double minY, double maxY, Node *n, int level);
    void divideNthTimes(double minX, double maxX, double minY, double maxY, int level);
    void divideComp(double tol, Function *F, int level);
    void appendAllBoxesToTwoFiles(ofstream *file, ofstream *file2, double cutoff, Function *F);
    void appendDiffarrayToFile(ofstream *file, Function *F, double cutoff);
    vector<double> getDifArray(Function *F, double cutoff);
    twoVectsDoub *getSupplyDemandAmt(Function *F, double cutoff);
    void appendSuppDemandAmt(ofstream *file, ofstream *file2, Function *F, double cutoff);
    void appendAllFiles(ofstream *outxboes, ofstream *inboxes, ofstream *supply, ofstream *demand, Function *F, double cutoff);
    void appendEverythingToTwoFiles(ofstream *outbox, ofstream *inbox, Function *F, double cutoff);
    tripleVect *getAllRelevantVects(Function *F, double cutoff);
    void normalize(Function *F);
    void divideCompAcc(double tol, Function *F, int level, int accuracy);
    void appendEverythingToTwoFilesAcc(ofstream *outbox, ofstream *inbox, Function *F, double cutoff, int accuracy);
    tripleVect* getAllRelevantVectsAcc(Function *F, double cutoff, int accuracy);



};
#endif