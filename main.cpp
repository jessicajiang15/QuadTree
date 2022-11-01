#include "Forest.h"
#include "GraphicsMechanics.h"
#include "Gaussian.h"
#include "CompTwoFunc.h"
#include "TestExponentialFunction.h"
#include <chrono>
#include "Test2DExpFcn.h"

/**
 * Parameters of the forest
 * */


#define NBOXES 40
#define MIN_Y -4
#define MAX_Y 4
#define MIN_X -8
#define MAX_X 8
/**
 * Parameters of the gaussian functions
 * Gives an initial gaussian of the form AINIT*E^[-(x-X1)^2-(y-Y1)^2/RHO^2]
 * Gives a final gaussian o the form AFIN*E^-[aa*x^2+bb*x*y+cc*y^2] where:
 * aa=(Cos[THETA]^2/P^2+(P^2)Sin[theta]^2/RHO^2)
 * bb=2 * Sin[THETA] * Cos[THETA] *(1/P^2 - P^2/RHO^2)
 * cc=Sin[THETA]^2/P^2+(P^2) (Cos[THETA]^2)/RHO^2
 *  * */
#define AUTO_NORM true
#define P 1
#define RHO 1
#define THETA 0
//note: x1 and y1 are equivalent to x2 and y2 in the mathematica notebook
#define X1 0.6
#define Y1 0
#define AINIT 1 / M_PI
#define AFIN 1 / M_PI
#define NORM_CONST_INIT 2.00000654782506394749318255732403311315
#define NORM_CONST_FIN 2.00000658749708382840650092398361064387
//determines which inboxes and outboxes to throw out
#define CUTOFF 0.001
//defines the maximum level you will allow the grid to divide to.
#define MAX_LEVEL 5
//determines how finely you divide the grid
#define TOL 1
//determines how accurate the numerical integrals are, overall. 10 means "divide the current box into 10, then
//calculate the midpoint riemann sum for all 10 mini-boxes and add them up to get my approximation."
//note that this includes the normalization accuracy.
#define ACC 1000
#define CUTOFF_ACC 10
#define READ_FILE true

/*
Gaussian Quadrature related definitions.
*/
//true if auto (generate weights with algorithm inside this program), false if read (directly take weights from file)
#define GAUSS_AUTO_OR_READ false
//Order of legendre polynomial if auto, ignored if read
#define N 10
//Maximum iterations for newton's method
#define MAX_ITERATIONS 1000
#define GAUSS_ACC 2e-20
//how many digits you want in the final value
#define PRECISION 50


int nboxes=NBOXES;
int min_y=MIN_Y;
int max_y=MAX_Y;
int min_x=MIN_X;
int max_x=MAX_X;
double cutoff=CUTOFF;
int max_level=MAX_LEVEL;
double tol=TOL;
double acc=ACC;

double p=P;
double rho=RHO;
double theta=THETA;
double x1=X1;
double y_1=Y1;


void appendDataToFile(ofstream *file);

void defineAllConstants(ifstream *file);

void defineAllConstantsNoRead();


int main()
{
    /**
     * define the files that we will put data in and also open them. Note that this will
     * override any preexisting file named "inData.csv" and "outData.csv", so make sure
     * you copy any data you want to another place from this directory.
    **/
    ofstream inData;
    ofstream outData;
    ofstream zeros;

    //first: 4 coords, xmin, xmax, ymin, ymax
    //sec: NBOXES
    //3rd: initialcutoff
    /**
 * #define P 0.25
#define RHO 0.5
#define THETA -M_PI / 4
#define X1 0
#define Y1 0
#define AINIT 1 / M_PI
#define AFIN 1 / M_PI
 * */

    ofstream appendData;

    ifstream nodes1;
    ifstream weights1;
    ifstream nodes2;
    ifstream weights2;
    ifstream params;


    ofstream cellCoords;

    cellCoords.open("cellCoords.csv");

    inData.open("inData.csv");
    outData.open("outData.csv");
    zeros.open("zeros.txt");

    appendData.open("data.csv");

    nodes1.open("nodes1.txt");
    nodes2.open("nodes2.txt");
    weights1.open("weights1.txt");
    weights2.open("weights2.txt");
    params.open("params.csv");

    if (weights2.fail())
    {
        std::cout << "fail!" << std::endl;
    }
    if (nodes2.fail())
    {
        std::cout << "fail!" << std::endl;
    }

    if (weights1.fail())
    {
        std::cout << "fail!" << std::endl;
    }
    if (nodes1.fail())
    {
        std::cout << "fail!" << std::endl;
    }
    if(params.fail())
    {
        std::cout<<"I FAILELDELDELDLE"<< std::endl;
    }

    if(READ_FILE)
    {
        cout<<"helloooo"<<endl;
        defineAllConstants(&params);
        //defineAllConstantsNoRead();

    }
    else
    {
        //defineAllConstantsNoRead();
        std::cout<< cutoff << std::endl;
        cout<<"nBOXX"<<nboxes<<endl;
        cout<<min_x<<endl;
        cout<<max_x<<endl;
        cout<<min_y<<endl;
        cout<<max_y<<endl;
        cout<<cutoff<<endl;
        cout<<tol<<endl;
        cout<<max_level<<endl;
        cout<<acc<<endl;
    }

    /**
     * The graphics is mainly here for debugging purposes.
     * */
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(GraphicsMechanics::WINDOW_WIDTH, GraphicsMechanics::WINDOW_HEIGHT), "QuadTree", sf::Style::Default, settings);
    window.setVerticalSyncEnabled(true);

    /**
     * Here we define our forest and initial and final gaussians using the constants
     * defined above. If you want to make a change to the constants, change the values after the #define
     * preprocessors.
     * */

    Forest *forest = new Forest(nboxes, nboxes, min_x, max_x, min_y, max_y);
    double cut = forest->getScaledCutOffMinSizeDif(nboxes, cutoff);
    cout << "cutoff: " << cut << endl;
    //normalization should not depend on how precise we define the grid to be, so we create
    //a second forest
    Forest *normForest = new Forest(100, 100, min_x, max_x, min_y, max_y);
    Gaussian *final = new Gaussian(AFIN, rho, p, theta,x1,y_1);
    Gaussian *initial = new Gaussian(AINIT, rho,3);

    cout << "lmaomlamo"<<final->getNormConst() << endl;

    /**
     * Normalize our initial and final functions with the normForest, which splits
     * the function into an 100x100 grid and calculates the midpoint riemann sum.
     * */
    if (AUTO_NORM)
    {
        cout<<"auto norm"<<endl;
        normForest->normalize(final);
        normForest->normalize(initial);
    }
    else
    {
        cout<<"not norm"<<endl;
        initial->normalize(NORM_CONST_INIT);
        final->normalize(NORM_CONST_FIN);
    }

    cout << final->getNormConst() << endl;
    cout << initial->getNormConst() << endl;
    CompTwoFunc *gaussian = new CompTwoFunc(initial, final);
    cout << "val"<<gaussian->value(-1, 0) << endl;

    //cout<<final->getNormConst()<<endl;
    //cout<<initial->getNormConst()<<endl;
    //if anything in this program is taking too long, feel free to use these commented out lines of code
    //to figure out how much time a portion of the code is taking.

    forest->divideComp(tol, gaussian, max_level);
    //forest->appendEverythingToTwoFilesAcc(&outData, &inData, gaussian, cutoff, ACC, CUTOFF_ACC);

    forest->appendEverythingToTwoFilesGaussQuad(&outData, &inData, gaussian, cut, MAX_ITERATIONS, acc, N, PRECISION);
    //&outData,&inData, gaussian, cutoff, MAX_ITERATIONS, ACC,N,PRECISION
    //forest->appendEverythingToTwoFilesGaussQuad(&outData,&inData, gaussian,cutoff, MAX_ITERATIONS, GAUSS_ACC, CUTOFF_ACC, N);

    forest->appendCoordsCellsToFiles(&cellCoords, PRECISION);
    appendDataToFile(&appendData);
    //  auto end = std::chrono::high_resolution_clock::now();

    //cout<<"time: "<<std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()<<endl;
/*
    sf::Music music;

    if (!music.openFromFile("../music/alarm.ogg"))
    {
        return -1;
    }
    music.setVolume(50);
    //music.play();
*/
    cout<<"HELLOOOOOOO"<<x1<<endl;
    cout << "I'm done!" << endl;
    //this while loop basically keeps the graphics up and running.
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Escape || event.key.code == sf::Keyboard::Delete))
            {
                window.close();
            }
        }

        // background color
        window.clear(sf::Color::White);

        //displays the forest on the screen
        forest->draw(&window);

        window.display();
    }
    //closes the files after writing to them.
    inData.close();
    outData.close();
    zeros.close();
    nodes1.close();
    nodes2.close();
    weights1.close();
    weights2.close();
    zeros.close();
}

void appendDataToFile(ofstream *file)
{
    /**
     * #define P 0.25
#define RHO 0.5
#define THETA -M_PI / 4
#define X1 0
#define Y1 0
     * */
    *file << nboxes <<"\t"<< 0 << "\t" << 0 << "\t" << 0 << "\t"
          << "\n";
    *file << min_y << "\t";
    *file << max_y << "\t";
    *file << min_x << "\t";
    *file << max_x << "\n";
    *file << cutoff <<"\t"<< 0 << "\t" << 0 << "\t" << 0 << "\t"
          << "\n";
    *file << p <<"\t"<< 0 << "\t" << 0 << "\t" << 0 << "\t"
          << "\n";
    *file << rho <<"\t"<< 0 << "\t" << 0 << "\t" << 0 << "\t"
          << "\n";
    *file << x1 <<"\t"<< 0 << "\t" << 0 << "\t" << 0 << "\t"
          << "\n";
    *file << y_1 <<"\t"<< 0 << "\t" << 0 << "\t" << 0 << "\t"
          << "\n";
}

void defineAllConstants(ifstream *thefile)
{
    int a=0;
    double temp;
    nboxes=NBOXES;
    min_y=MIN_Y;
    max_y=MAX_Y;
    min_x=MIN_X;
    max_x=MAX_X;
    cutoff=CUTOFF;
    max_level=MAX_LEVEL;
    acc=ACC;
        while (*thefile >> temp)
        {
            switch(a)
            {
            case 0:
            {
                nboxes=temp;
            }
            case 1:
            {
                min_y=temp;
            }
            case 2:
            {
                max_y=temp;
            }
            case 3:
            {
                min_x=temp;
            }
            case 4:
            {
                max_x=temp;
            }
            case 5:
            {
                cutoff=temp;
            }
            case 6:
            {
                max_level=temp;
            }
            case 7:
            {
                acc=temp;
            }
            case 8:
            {
                tol=temp;
            }
            case 9:
            {
                theta=temp;
            }
            case 10:
            {
                p=temp;
            }
            case 11:
            {
                rho=temp;
            }
            case 12:
            {
                x1=temp;
            }
            case 13:
            {
                y_1=temp;
            }
            
            }
        a++;
        }
        cout<<theta<<endl;
        cout<<p<<endl;
        cout<<rho<<endl;
        cout<<y_1<<endl;
        cout<<x1<<endl;
        cout<<"HEHEHEHE"<<endl;

    return;
}

void defineAllConstantsNoRead()
{
    nboxes=NBOXES;
    min_y=MIN_Y;
    max_y=MAX_Y;
    min_x=MIN_X;
    max_x=MAX_X;
    cutoff=CUTOFF;
    max_level=MAX_LEVEL;
    acc=ACC;

    theta=THETA;
    p=P;
    rho=RHO;
    x1=X1;
    y_1=Y1;
}
