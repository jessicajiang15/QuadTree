#include "Forest.h"
#include "GraphicsMechanics.h"
#include "Gaussian.h"
#include "CompTwoFunc.h"
#include <chrono>
/**
 * Parameters of the forest
 * */
#define MIN_SIZE 20
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
#define P 0.25
#define RHO 0.5
#define THETA -M_PI/2
#define X1 0
#define Y1 0
#define AINIT 1/M_PI
#define AFIN 1/M_PI
//determines which inboxes and outboxes to throw out
#define CUTOFF 0.0001
//defines the maximum level you will allow the grid to divide to.
#define MAX_LEVEL 4
//determines how finely you divide the grid
#define TOL 0.001
//determines how accurate the numerical integrals are, overall. 10 means "divide the current box into 10, then
//calculate the midpoint riemann sum for all 10 mini-boxes and add them up to get my approximation."
#define ACC 100


int main()
{
    /**
     * define the files that we will put data in and also open them. Note that this will
     * override any preexisting file named "inData.csv" and "outData.csv", so make sure
     * you copy any data you want to another place from this directory.
    **/
    ofstream inData;
    ofstream outData;
    inData.open("inData.csv");
    outData.open("outData.csv");

    /**
     * Unimportant graphics stuff. The graphics is mainly here for debugging purposes.
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
    Forest *forest =new Forest(MIN_SIZE, MIN_SIZE, MIN_X, MAX_X, MIN_Y, MAX_Y);
    //normalization should not depend on how precise we define the grid to be, so we create
    //a second forest
    Forest *normForest=new Forest(100,100,MIN_X, MAX_X, MIN_Y,MAX_Y);
    Gaussian *final=new Gaussian(AFIN,RHO,P,THETA);
    Gaussian *initial=new Gaussian(AINIT,X1,Y1,RHO,1);
    CompTwoFunc *gaussian=new CompTwoFunc(initial, final);

    /**
     * Normalize our initial and final functions with the normForest, which splits
     * the function into an 100x100 grid and calculates the midpoint riemann sum.
     * */
    normForest->normalize(final);
    normForest->normalize(initial);
    //cout<<final->getNormConst()<<endl;
    //cout<<initial->getNormConst()<<endl;
    //if anything in this program is taking too long, feel free to use these commented out lines of code
    //to figure out how much time a portion of the code is taking.
    //auto start = std::chrono::high_resolution_clock::now(); 
    //auto end = std::chrono::high_resolution_clock::now(); 
    //cout<<"time: "<<std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()<<endl;
    forest->divideCompAcc(TOL,gaussian,MAX_LEVEL, ACC);
    forest->appendEverythingToTwoFilesAcc(&outData,&inData, gaussian, CUTOFF, ACC);
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
        //window.draw(*rect);
        // cout << "2"<<forest->getForest()[forest->index(0, 0)]->getRoot()->getRekt()->getY() << endl;

        forest->draw(&window);
        // cout << "O3O"<<forest->getForest()[forest->index(0, 0)]->getRoot()->getRekt()->getY() << endl;

        window.display();


    }
    inData.close();
    outData.close();
}
