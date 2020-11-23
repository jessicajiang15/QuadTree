#include "Forest.h"

Forest::Forest(int rows, int cols, double minCoordX,double maxCoordX, double minCoordY, double maxCoordY)
{
    forest = new QuadTree *[rows * cols];
    this->rows = rows;
    this->cols = cols;
    this->minCoordX = minCoordX;
    this->minCoordY = minCoordY;
    this->maxCoordX = maxCoordX;
    this->maxCoordY = maxCoordY;
    this->width = (maxCoordX - minCoordX) / cols;
    this->height = (maxCoordY - minCoordY) / rows;
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
            //cout << "c" << c << endl;
            //cout << "r" << r << endl;

            // cout << "initial x" << Forest::getCoordX(c) << endl;
            //cout << "initial y" << Forest::getCoordY(r) << endl;
            Rectangle *temp = new Rectangle(Forest::getCoordX(c), Forest::getCoordY(r), width, height);
            
            forest[index(r, c)] = new QuadTree(temp, minCoordX, maxCoordX, minCoordY, maxCoordY);
            //cout<<"R: "<<r<<endl;
            //cout<<"C: "<<c<<endl;
            //cout<<"This is what forest[0,0] is: "<<forest[index(0, 0)]->getRoot()->getRekt()->getY()<<endl;

        }
    }
        //cout<<"end"<<forest[index(0, 0)]->getRoot()->getRekt()->getY()<<endl;
}

int Forest::index(int row, int col)
{
    return row * this->cols + col;
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
    //cout<<"B: "<<c * width + this->minCoordX<<endl;
    //cout<<"width: "<<width<<endl;
    //cout<<"min coord"<<minCoordX<<endl;
    //cout<<"c "<<c<<endl;
    return (double)c * width + this->minCoordX;
}

//double check!
double Forest::getCoordY(int r)
{
    int totalHeight = maxCoordY - minCoordY;
    //if(r==0)
    //cout<<"yoi: " <<(totalHeight - r * height) + minCoordY<<endl;
    return ((totalHeight - r * height)) + minCoordY;
}

/**
 * Divides the entire forest of trees according to the function F.
 **/
void Forest::divide(Function *F, double tol)
{
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
            forest[index(r, c)]->divideTree(minCoordX, maxCoordX, minCoordY, maxCoordY, F, tol, maximumLevel);
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
        return binarySearchX(x, mid + 1, upper);
    }
    case 0:
    {
        return mid;
    }
    case -1:
    {
        return binarySearchX(x, lower - 1, mid);
    }
    }
    return 0;
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
    return 0;
}

twoVects *Forest::getAllBoxes(Function *F, double cutoff)
{
    //inboxes
    vector<Rectangle *> v1;
    vector<Rectangle *> v2;
   // vector<double> v3;
   //vector<double> difArray=getDifArray(F, cutoff);
    twoVects *temp = new twoVects(v1, v2);

    //temp->v3=v3;
    
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
            QuadTree *te=this->forest[index(r, c)];
            twoVects *t = te->getAllBoxes(te->getRoot(), F, cutoff);
            //std::cout<<"temp size: "<<t->v1.size()<<endl;
            temp->append(t);
   // temp->v3.insert(t->v3.end(), t->v3.begin(), t->v3.end());
        }
    }
    
    return temp;
}

bool Forest::add(QuadTree *t, int r, int c)
{
    if (r >= rows || r < 0 || c >= cols || c < 0 || forest[index(r, c)] != nullptr)
    {
        return false;
    }
    forest[index(r, c)] = t;
    return true;
}

void Forest::appendOutboxesToFile(ofstream *file, double cutoff, Function *F)
{
   // *file << "{";
    twoVects *temp = getAllBoxes(F, cutoff);


    for (int i = 0; i < temp->v1.size(); i++)
    {
        if (i == temp->v1.size() - 1)
        {
            *file << temp->v1[i];
        }
        else
        {
            //std::cout<<"hello"<<std::endl;
            //std::cout<<temp->v1[i]->toStringCoord()<<std::endl;
            *file << temp->v1[i]->toStringCoord() + ", ";
            *file<<"\n";
        }
    }
   // *file << "}";
    delete temp;
}

void Forest::appendInboxesToFile(ofstream *file, double cutoff, Function *F)
{
    //*file << "{";
    twoVects *temp = getAllBoxes(F, cutoff);
    std::cout<<"v1 size: "<<temp->v1.size()<<std::endl;
        std::cout<<"v2 size: "<<temp->v2.size()<<std::endl;

    for (int i = 0; i < temp->v2.size(); i++)
    {
        if (i == temp->v2.size() - 1)
        {
            *file << temp->v2[i];
        }
        else
        {
            *file << temp->v2[i]->toStringCoord();
            *file<<"\n";
        }
    }
    //*file << "}";
    delete temp;
}

void Forest::draw(sf::RenderWindow *window)
{
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
                forest[index(r, c)]->draw(window);
            
        }
    }
}

QuadTree** Forest::getForest()
{
    return forest;
}


    void Forest::divideNthTimes(double minX, double maxX, double minY, double maxY, int level)
       {
        for(int r=0;r<rows;r++)
        {
            for(int c=0;c<cols;c++)
            {
                forest[index(r, c)]->divideTreeNTimes(minX, maxX, minY, maxY, forest[index(r, c)]->getRoot(),level);
            }
        }
    }

    void Forest::divideComp(double tol, Function *F, int level)
    {
        for(int r=0;r<rows;r++)
        {
            for(int c=0;c<cols;c++)
            {
                forest[index(r, c)]->divideCompMid(minCoordX, maxCoordX, minCoordY, maxCoordY, forest[index(r, c)]->getRoot(),F, tol, level);
            }
        }
    }
    //v2 inboxes
    //v1 outboxes
    //file2 outboxes
    //file inboxes
    /**
     * first file is inboxes
     * second file is outboxes
     **/
    void Forest::appendAllBoxesToTwoFiles(ofstream *file, ofstream *file2, double cutoff, Function *F)
    {
       // *file << "{";
    twoVects *temp = getAllBoxes(F, cutoff);
    std::cout<<"v1: "<<temp->v1.size()<<endl;
    std::cout<<"v2: "<<temp->v2.size()<<endl;

    for (int i = 0; i < temp->v2.size(); i++)
    {
        if (i == temp->v2.size() - 1)
        {
            *file << temp->v2[i]->toStringCoord();
        }
        else
        {
            *file << temp->v2[i]->toStringCoord();
            *file<<"\n";
        }
    }
    //*file << "}";

    //*file2 << "{";

    for (int i = 0; i < temp->v1.size(); i++)
    {
        if (i == temp->v1.size() - 1)
        {
            *file2 << temp->v1[i]->toStringCoord();
        }
        else
        {
            //std::cout<<"hello"<<std::endl;
            //std::cout<<temp->v1[i]->toStringCoord()<<std::endl;
            *file2 << temp->v1[i]->toStringCoord();
            *file2<<"\n";
        }
    }
    //*file2 << "}";
    delete temp;
    }

 vector<double> Forest::getDifArray(Function *F, double cutoff)
 {
     vector<double> temp;
     for(int r=0;r<rows;r++)
     {
         for(int c=0;c<cols;c++)
         {
             vector<double> temp2;
             QuadTree *te=forest[index(r, c)];
             temp2=te->getDifArray(te->getRoot(),F, cutoff);
             temp.insert(temp.end(), temp2.begin(), temp2.end());
         }
     }
     return temp;
 }


    void Forest::appendDiffarrayToFile(ofstream *file, Function *F, double cutoff)
    {
        vector<double> difArray=getDifArray(F, cutoff);
        for(int i=0;i<difArray.size();i++)
        {
            *file<<difArray[i];
            *file<<"\n";
        }
    }

    twoVectsDoub *Forest::getSupplyDemandAmt(Function *F, double cutoff)
    {
        vector<double> temp=getDifArray(F, cutoff);
        //d1 supply, d2 demand
        vector<double> d1;
        vector<double> d2;
        for(int i=0;i<temp.size();i++)
        {
            if(temp[i]>0)
            {
                d1.push_back(temp[i]);
            }
            else if(temp[i]<0)
            {
                d2.push_back(temp[i]);
            }
            
        }
        twoVectsDoub *temp1=new twoVectsDoub(d1, d2);
        return temp1;
    }

/**
 * first file is supply, second is demand
 * */
        void Forest::appendSuppDemandAmt(ofstream *file, ofstream *file2, Function *F, double cutoff)
    {
        twoVectsDoub *temp=getSupplyDemandAmt(F, cutoff);
                    cout<<"size temp: "<<temp->v1.size()<<endl;
            cout<<"size temp: "<<temp->v2.size()<<endl;
        for(int i=0;i<temp->v1.size();i++)
        {
            *file<<temp->v1[i];
            *file<<"\n";
        }
        for(int i=0;i<temp->v2.size();i++)
        {
            *file2<<temp->v2[i];
            *file2<<"\n";
        }
    }

void Forest::appendAllFiles(ofstream *outboxes, ofstream *inboxes, ofstream *supply, ofstream *demand, Function *F, double cutoff)
{
    appendSuppDemandAmt(supply, demand, F,cutoff);
    appendAllBoxesToTwoFiles(inboxes, outboxes, cutoff, F);
}

void Forest::appendEverythingToTwoFiles(ofstream *outbox, ofstream *inbox, Function *F, double cutoff)
{
    tripleVect *temp=getAllRelevantVects(F, cutoff);
    vector<Rectangle*> inboxes=temp->rect->v1;
        vector<Rectangle*> outboxes=temp->rect->v2;
    vector<double> supply=temp->doub->v1;
    vector<double> demand=temp->doub->v2;
    int i=0;
    for(int i=0;i<inboxes.size();i++)
    {
        *inbox<<inboxes[i];
        *inbox<<",";
        *inbox<<supply[i];
    }
    for(int i=0;i<outboxes.size();i++)
    {
        *outbox<<outboxes[i];
        *outbox<<",";
        *outbox<<demand[i];
    }
    
}

    tripleVect *Forest::getAllRelevantVects(Function *F, double cutoff)
    {
        vector<Rectangle*> t1;
        vector<Rectangle*> t2;
        vector<double> t3;
        vector<double> t4;
        twoVects *temp1=new twoVects(t1, t2);
        twoVectsDoub *temp2=new twoVectsDoub(t3, t4);
        tripleVect *temp=new tripleVect(temp1, temp2);
        for(int r=0;r<rows;r++)
        {
            for(int c=0;c<cols;c++)
            {
                QuadTree *a=forest[index(r, c)];
                tripleVect *t=a->getAllRelevantVects(a->getRoot(), F, cutoff);
                temp->append(t);
            }
        }
        return temp;
    }

    void Forest::normalize(Function *F)
    {
        double value=0;
        for(int r=0;r<rows;r++)
        {
            for(int c=0;c<cols;c++)
            {
                value+=forest[index(r, c)]->normalize(forest[index(r, c)]->getRoot(),F);
            }
        }
        F->normalize(1/value);
    }