#include "Forest.h"
#include "GraphicsMechanics.h"
#include "Gaussian.h"

int main()
{
    ofstream file;
    file.open("example.txt");
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(GraphicsMechanics::WINDOW_WIDTH, GraphicsMechanics::WINDOW_HEIGHT), "QuadTree", sf::Style::Default, settings);
    window.setVerticalSyncEnabled(true);
    Forest *forest = new Forest(20, 20, -8, 8, -4, 4);

    //int row, int col, double minCoordY, double minCoordX, double maxCoordY, double maxCoordX
   Gaussian *gaussian=new Gaussian(1, 1,1,1,1);
    forest->divideComp(0.001,gaussian,3);
    forest->appendInboxesToFile(&file,0.1,gaussian);
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
    file.close();
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