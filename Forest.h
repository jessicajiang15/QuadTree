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
    Forest(int row, int col, double minCoordX, double maxCoordX, double minCoordY, double maxCoordY);
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
    void draw(sf::RenderWindow *);
    QuadTree **getForest();
    /**
     * Helper function intended to help access a cell at index r, c in the forest, as the forest
     * is allocated as a single 1D array.
     **/
    int index(int row, int col);
    //void divideTreeNTimes(double minX, double maxX, double minY, double maxY, Node *n, int level);
    void divideNthTimes(double minX, double maxX, double minY, double maxY, int level);
    /**
     * Divides the tree using the less accurate approx() in Rectangle and the volume comparison method
     * @param tol the maximum allowed difference between the sum of the midpoint riemann rectangular prism 
     * volumes of the subdivided rectangles and the mid point riemann rectangular prism volume
     * @param F the function we are dividing the grid based on
     * @param level the maximum level that we are dividing to
     * */
    void divideComp(double tol, Function *F, int level);
    /**
     * Appends both inboxes and outboxes to two files. Note that this method is currently unused, but if
     * for some reason you ONLY want the inboxes and outboxes, then inboxes -> file1 outboxes->file2
     * @param file the inboxes file
     * @param file the outboxes file
     * @param cutoff the minimum allowed amount of sand for the box to be kept
     * @param F the function we are dividing the forest over
     * */
    void appendAllBoxesToTwoFiles(ofstream *file, ofstream *file2, double cutoff, Function *F);
    /**
     * Appends the diffaray to a single file, which is an appended list of both supply and demand. 
     * Note that this method is currently unused
     * @param file the inboxes file
     * @param file the outboxes file
     * @param cutoff the minimum allowed amount of sand for the box to be kept
     * @param F the function we are dividing the forest over
     * */
    void appendDiffarrayToFile(ofstream *file, Function *F, double cutoff);
    /**
     * Obtains the "difference array", which contains a list of the amount of sand in each cell.
     * This method is currently unused.
     * @param F the function we are dividing over
     * @param cutoff the minimum allowed amount of sand for us to keep the box
     * */
    std::vector<double> getDifArray(Function *F, double cutoff);
    /**
     * Obtains a twoVectsDoub object where v1 is the supply amount and v2 is the demand amount.
     * @param F the function that we are considering
     * @param cutoff the minimum amount of sand that a box needs for us to keep it
     * */
    twoVectsDoub *getSupplyDemandAmt(Function *F, double cutoff);
    /**
     * Appends the supply and demand amounts to two different file. Appends supply->file and demand->file2
     * Note that this method is currently unused.
     * @param file the inboxes file
     * @param file the outboxes file
     * @param cutoff the minimum allowed amount of sand for the box to be kept
     * @param F the function we are dividing the forest over
     * */
    void appendSuppDemandAmt(ofstream *file, ofstream *file2, Function *F, double cutoff);
    /**
     * Appends inboxes, outboxes supply, and demand into their corresponding separate files.
     * Note that this method is unused in favor of a method that combines outboxes and supply,
     * demand and inboxes. 
     * */
    void appendAllFiles(ofstream *outxboes, ofstream *inboxes, ofstream *supply, ofstream *demand, Function *F, double cutoff);
    /**
     * Appends inboxes and demand to inbox, outboxes and supply to outbox.
     * Note that this method is currently unused because it uses the less accurate approx method.
     * However, it is kept here in case we need to revert back.
     * @param file the inboxes file
     * @param file the outboxes file
     * @param cutoff the minimum allowed amount of sand for the box to be kept
     * @param F the function we are dividing the forest over
     * */
    void appendEverythingToTwoFiles(ofstream *outbox, ofstream *inbox, Function *F, double cutoff);
    /**
     * Obtains lists of inboxes, outboxes, supply, and demand, and places them into a tripleVect object,
     * which stores 4 vectors. This method obtains everything in a single iteration.
     * Currently unused, as it uses the less accurate approx.
     * @param cutoff the minimum allowed amount of sand for the box to be kept
     * @param F the function we are dividing the forest over
     * @return a tripleVect object containing a twoVects and twoVectsDoub object, where v1 corresponds to
     * supply and outboxes, and v2 corresponds to inboxes and demand
     * */
    tripleVect *getAllRelevantVects(Function *F, double cutoff);
    /**
     * Normalizes the function using this forest grid by setting the normConst of the parameter F
     * @param the function to be normalized
     * */
    void normalize(Function *F);
    /**
     * Divides the tree using the more accurate getAccurateApprox() in Rectangle and the volume comparison 
     * method.
     * @param tol the maximum allowed difference between the sum of the midpoint riemann rectangular prism 
     * volumes of the subdivided rectangles and the mid point riemann rectangular prism volume
     * @param F the function we are dividing the grid based on
     * @param level the maximum level that we are dividing to
     * @param accuracy the accuracy of the integral that we are using for comparison. 
     * TODO: delete the accuracy parameter
     * */
    void divideCompAcc(double tol, Function *F, int level, int accuracy);
    /**
     * Appends inboxes and demand to inbox, outboxes and supply to outbox.
     * This method uses the more accurate getAccurateApprox method to obtain the supply and demand amounts.
     * @param file the inboxes file
     * @param file the outboxes file
     * @param cutoff the minimum allowed amount of sand for the box to be kept
     * @param F the function we are dividing the forest over
     * @param accuracy the accuracy of the integral we use to get the supply and demand amounts.
     * */
    void appendEverythingToTwoFilesAcc(ofstream *outbox, ofstream *inbox, Function *F, double cutoff, int accuracy, int cutoffAcc);
    /**
     * Obtains lists of inboxes, outboxes, supply, and demand, and places them into a tripleVect object,
     * which stores 4 vectors. This method obtains everything in a single iteration.
     * This uses the more accurate getAccurateApprox method
     * @param cutoff the minimum allowed amount of sand for the box to be kept
     * @param F the function we are dividing the forest over
     * @return a tripleVect object containing a twoVects and twoVectsDoub object, where v1 corresponds to
     * supply and outboxes, and v2 corresponds to inboxes and demand
     * @param accuracy the accuracy of the integral used to obtain supply and demand amounts.
     * */
    tripleVect *getAllRelevantVectsAcc(Function *F, double cutoff, int accuracy, int cutoffAcc);
    void normalizeAcc(Function *F, int accuracy);
    //get cutoff relative to a 20x20 grid, which corresponds to a cutoff of 0.0001
    double getScaledCutoff(double cutoff);
    double getScaledCutOffMinSizeDif(int NBOXES, double cutoff);

    tripleVect* getAllRelevantVectsGaussQuad(Function *F, double cutoff, int MAX_ITERATIONS, double acc, int m);

    void appendEverythingToTwoFilesGaussQuad(ofstream *outbox, ofstream *inbox, Function *F, double cutoff, int MAX_ITERATIONS, double acc, int m, int PRECISION);
    void appendCoordsCellsToFiles(ofstream *coords, int PRECISION);
    vector<std::string> getAllCoords();


};
#endif