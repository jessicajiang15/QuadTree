#include "LegendrePolynomial.h"

LegendrePolynomial::LegendrePolynomial(int n)
{
    this->n = n;
}

double LegendrePolynomial::evaluate(double x, int n)
{
    //std::cout<<n<<std::endl;
    if (n == 0)
    {
        //   std::cout<<"zero"<<std::endl;

        return 1;
    }
    else if (n == 1)
    {
        //   std::cout<<"one"<<std::endl;
        return x;
    }
    //std::cout<<"hi"<<std::endl;
    return ((2 * n-1) * x * evaluate(x, n - 1) - (n - 1) * evaluate(x, n - 2))/n;
}

double LegendrePolynomial::value(double x)
{
    //std::cout<<"x"<<x<<std::endl;

    double value = evaluate(x, this->n);
    //std::cout<<"value"<<value<<std::endl;
    return value;
}

double LegendrePolynomial::nderivative(double x, int n)
{
    if (n == 0)
    {
        return 0;
    }
    else if (n == 1)
    {
        return 1;
    }
    //std::cout<<"hi"<<std::endl;
    //std::cout<<n / (pow(x, 2) - 1)<<std::endl;
    return (n / (x*x - 1)) * (x * LegendrePolynomial::evaluate(x, n) - LegendrePolynomial::evaluate(x, n - 1));
}

double LegendrePolynomial::derivative(double x)
{
    return nderivative(x, this->n);
}

std::vector<double> LegendrePolynomial::calcZeros(double acc, int MAX_ITERATIONS)
{
    std::vector<double> roots;
    //n=0 does not have roots, as it is a constant function
    for (int i = 1; i < n/2+1; i++)
    {
        roots.push_back(newtonRaphsonIthRoot(i, acc, MAX_ITERATIONS));
    }

//use symmetry to find remaining roots
int size=roots.size();

for(int i=0;i<size;i++)
{
    roots.push_back(-roots[i]);
}
if(this->n%2!=0)
{
    roots.push_back(0);
}
    return roots;
}

//ith root
double LegendrePolynomial::getGuess(int i)
{
    return cos(M_PI * (i - 0.25) / (n + 0.5));
}

//acc digits of precision
double LegendrePolynomial::newtonRaphsonIthRoot(int i, double acc, int MAX_ITERATIONS)
{
    double currRoot = getGuess(i);
    //std::cout<<"First guess"<<getGuess(i)<<std::endl;
    double dx;
    int iterations = 0;
    do
    {
        iterations++;
        dx = -value(currRoot) / derivative(currRoot);
        currRoot = currRoot + dx;
    } while (abs(dx) > acc&&iterations<MAX_ITERATIONS);
    return currRoot;
}

void LegendrePolynomial::initializeZeros(double acc, int MAX_ITERATIONS)
{
    this->zeros = calcZeros(acc, MAX_ITERATIONS);
}

std::vector<double> LegendrePolynomial::getZeros()
{
    return zeros;
}