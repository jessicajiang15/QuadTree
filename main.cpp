#include "Forest.h"
#include "GraphicsMechanics.h"
#include "Gaussian.h"
#include "CompTwoFunc.h"

int main()
{
    ofstream inboxes;
    ofstream outboxes;
    ofstream difArray;
    ofstream supply;
    ofstream demand;
    inboxes.open("inboxes.csv");
    outboxes.open("outboxes.csv");
    difArray.open("difArray.csv");
    supply.open("supply.csv");
    demand.open("demand.csv");
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(GraphicsMechanics::WINDOW_WIDTH, GraphicsMechanics::WINDOW_HEIGHT), "QuadTree", sf::Style::Default, settings);
    window.setVerticalSyncEnabled(true);
    Forest *forest = new Forest(20, 20, -8, 8, -4, 4);

    //int row, int col, double minCoordY, double minCoordX, double maxCoordY, double maxCoordX
    //Gaussian *gaussian=new Gaussian(-1,1,1,1,1);
    Gaussian *final=new Gaussian(0.5,0.25,-M_PI/2);
    Gaussian *initial=new Gaussian(0.6366218566,0,0,0.5,1);
    //Gaussian *final=new Gaussian(1,1,1,1,1);
    //Gaussian *initial=new Gaussian(1,0,1,0,1);
    CompTwoFunc *gaussian=new CompTwoFunc(initial, final);
    forest->divideComp(0.001,gaussian,3);
   //forest->appendInboxesToFile(&file,0.1,gaussian);
    //forest->appendOutboxesToFile(&file2,0.1,gaussian);
    forest->appendAllBoxesToTwoFiles(&inboxes, &outboxes,0.0001,gaussian);
    forest->appendDiffarrayToFile(&difArray, gaussian, 0.0001);
    forest->appendSuppDemandAmt(&supply, &demand, gaussian, 0.0001);
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
    inboxes.close();
    outboxes.close();
    /*
    ofstream file;
    file.open("example.txt");
    int *p;
    p=(int*)malloc(sizeof(int)*10);
    for(int i=0;i<10;i++)
    {
        p[i]=i;
    }
    file<<"{";
    for(int i=0;i<10;i++)
    {
        if(i==9)
        {
            file<<to_string(p[i]);
            break;
        }
        file<<to_string(p[i])+", ";
    }
    file<<"}";
    std::cout << "Quad Tree!\n"<<std::endl;
    file.close();
    return 0;
    */
}

/*
#include "Game.h"
int main()
{

    // create the window
    Game game;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(game.getGameWidth(), game.getGameWidth()), "SFMLGameStarter", sf::Style::Default, settings);

    // run the program as long as the window is open
    //window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);
    //music.setVolume(50);
    //music.play();

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

        game.draw(&window);

        window.display();
    }
}

*/