#include "Square.h"
//rectangle

 Rectangle::Rectangle(double x, double y, double width, double height)
{
    Point *point=new Point(x, y);
    this->point=point;
    this->width=width;
    this->height=height;
}

Rectangle::Rectangle(Point *p, double width, double y)
{
    this->point=p;
    this->width=width;
    this->height=width;
}

double Rectangle::getArea()
{
    return width*height;
    return 0;
}
double Rectangle::getXInterval()
{
    return width;
}
double Rectangle::getYInterval()
{
    return height;
}
double Rectangle::getWidth()
{
    return width;
}

double Rectangle::getX()
{
    return this->point->getX();
}

double Rectangle::getY()
{
    return this->point->getY();
}

double Rectangle::getCenterX()
{
    return width/2+point->getX();
}

double Rectangle::getCenterY()
{
    return -height/2+point->getY();
}

double Rectangle::getHeight()
{
    return height;
}

//integrate the function
double Rectangle::integrate(Function *F)
{
    return 0;
}

//gives a mid point riemann sum approximation of F on this interval
double Rectangle::approx(Function *F)
{
    return getArea()*F->value(point->getX()+width/2,point->getY()-height/2);
}

double Rectangle::approx(double **F)
{
    return 0;
}

void Rectangle::draw(sf::RenderWindow *window)
{
    window->draw(*rect);
}
std::string Rectangle::toStringCoord()
{
    return std::to_string(getCenterX())+"\t"+std::to_string(getCenterY());
}

void Rectangle::createSfRectFromCartesian(double minX, double maxX, double minY, double maxY)
{
    Point *temp=GraphicsMechanics::convertFromCartesian(minX, maxX, minY, maxY, this->point);
    rect=new sf::RectangleShape();
    rect->setPosition(temp->getX(),temp->getY());
    
    rect->setSize(sf::Vector2f(width*GraphicsMechanics::getXScale(minX, maxX),height*GraphicsMechanics::getYScale(minY, maxY)));
    rect->setFillColor(sf::Color(100, 250, 50));
    rect->setOutlineColor(sf::Color(0, 0, 0));
    rect->setOutlineThickness(1);
}

void Rectangle::setColor(std::string s)
{
    if(s.compare("inbox")==0)
    {
        rect->setFillColor(sf::Color(169, 179, 255));
    }
    if(s.compare("outbox")==0)
    {
        rect->setFillColor(sf::Color(255, 169, 169));
    }

}

double Rectangle::getAccurateApprox(Function *F, int accuracy)
{
    if(accuracy==0)
    {
        return approx(F);
    }
    double intervalX=width/accuracy;
    double intervalY=height/accuracy;
    double total=0;
    for(int r=0;r<accuracy;r++)
    {
        for(int c=0;c<accuracy;c++)
        {
            double temp=intervalX*intervalY*F->value(c*intervalX+point->getX()+intervalX/2, point->getY()-r*intervalY-intervalY/2);
            total+=temp;
        }
    }
    return total;
}

    double Rectangle::integralGaussApprox(int MAX_ITERATIONS, Function *F, GaussianQuadrature *quadrature)
    {
        //std::cout<<"x"<<this->getX()<<std::endl;
        //std::cout<<"x"<<this->getX()+this->getWidth()<<std::endl;

        //std::cout<<"y"<<this->getY()<<std::endl;
        //std::cout<<"y"<<this->getY()-this->getHeight()<<std::endl;
        return quadrature->getTwoDIntegral(this->getX(), this->getX()+this->getWidth(), this->getY()-this->getHeight(),this->getY(),F,MAX_ITERATIONS);
    }


    std::string Rectangle::toStringCoordBottomRight()
    {
            return std::to_string(getX()+width)+"\t"+std::to_string(getY()-height);
    }


    std::string Rectangle::toStringCoordTopLeft()
    {
            return std::to_string(getX())+"\t"+std::to_string(getY());
    }

