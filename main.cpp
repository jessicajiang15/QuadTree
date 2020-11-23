#include "Forest.h"
#include "GraphicsMechanics.h"
#include "Gaussian.h"
#include "CompTwoFunc.h"
/**
 * Parameters of the forest
 * */
#define MIN_SIZE 5
#define MIN_Y -4
#define MAX_Y 4
#define MIN_X -8
#define MAX_X 8
/**
 * Parameters of the gaussian functions
 * */
#define p 0.25
#define rho 0.5
#define theta -M_PI/2
#define x1 0
#define y1 0
#define a 1
//determines which inboxes and outboxes to throw out
#define CUTOFF 0.001
//defines the maximum level you will allow the grid to divide to.
#define MAX_LEVEL 3
//determines how finely you divide the grid
#define TOL 0.1


int main()
{
    ofstream inData;
    ofstream outData;
    inData.open("inData.csv");
    outData.open("outData.csv");
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(GraphicsMechanics::WINDOW_WIDTH, GraphicsMechanics::WINDOW_HEIGHT), "QuadTree", sf::Style::Default, settings);
    window.setVerticalSyncEnabled(true);
    Forest *forest =new Forest(MIN_SIZE, MIN_SIZE, MIN_X, MAX_X, MIN_Y, MAX_Y);
    Gaussian *final=new Gaussian(rho,p,theta);
    Gaussian *initial=new Gaussian(a,x1,y1,rho,1);
    CompTwoFunc *gaussian=new CompTwoFunc(initial, final);
    forest->normalize(final);
    forest->normalize(initial);
    cout<<final->getNormConst()<<endl;
    cout<<initial->getNormConst()<<endl;
    forest->divideComp(0.1,gaussian,3);
    forest->appendEverythingToTwoFiles(&outData,&inData, gaussian, 0.0001);
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
