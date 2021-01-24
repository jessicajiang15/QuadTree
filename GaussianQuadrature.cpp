#include "GaussianQuadrature.h"

GaussianQuadrature::GaussianQuadrature(int n, double acc)
{
    this->n = n;
    this->acc = acc;
    this->m = 0;
}

GaussianQuadrature::GaussianQuadrature(int n, int m, double acc)
{
    this->n = n;
    this->acc = acc;
    this->m = m;
}

twoVectsDoub *GaussianQuadrature::getNWeightsAndAbscissae(int MAX_ITERATIONS)
{
    // std::cout << "weights start" << std::endl;
    LegendrePolynomial *legpoly = new LegendrePolynomial(n);
    std::vector<double> weights;
    legpoly->initializeZeros(acc, MAX_ITERATIONS);
    // std::cout << "weights mid" << std::endl;
    std::vector<double> abscissae = legpoly->getZeros();
    // std::cout << "weights end" << std::endl;
    for (int i = 0; i < abscissae.size(); i++)
    {
        //std::cout << "xvalues"<<abscissae[i] << std::endl;
        weights.push_back(2 / ((1 - pow(abscissae[i], 2)) * pow(legpoly->derivative(abscissae[i]), 2)));
        std::cout << "weights " << weights[i] << std::endl;
    }
    twoVectsDoub *weightsAndAbscissae = new twoVectsDoub(weights, abscissae);
    std::cout << "weights done" << std::endl;
    return weightsAndAbscissae;
}

double GaussianQuadrature::getOneDIntegral(double xi, double xf, OneDFunction *F, int MAX_ITERATIONS)
{
    twoVectsDoub *weightsAndAbscissae = getNWeightsAndAbscissae(MAX_ITERATIONS);

    double integral = 0;
    for (int i = 0; i < weightsAndAbscissae->v1.size(); i++)
    {
        double temp = weightsAndAbscissae->v1[i] * F->value(((xf - xi) / 2) * (weightsAndAbscissae->v2[i]) + (xf + xi) / 2);
        integral += temp;
    }
    std::cout << "INTEGRAL: " << ((xf - xi) / 2) * integral << std::endl;

    return ((xf - xi) / 2) * integral;
}

void GaussianQuadrature::setAcc(double acc)
{
    this->acc = acc;
}

double GaussianQuadrature::getTwoDIntegral(double xi, double xf, double yi, double yf, Function *F, int MAX_ITERATIONS)
{
    twoVectsDoub *weightsAndAbscissaeN = getWeightsAndAbscissae(MAX_ITERATIONS, n);
    twoVectsDoub *weightsAndAbscissaeM = getWeightsAndAbscissae(MAX_ITERATIONS, m);
    double integral = 0;
    for (int j = 0; j < weightsAndAbscissaeM->v1.size(); j++)
    {
        for (int i = 0; i < weightsAndAbscissaeN->v1.size(); i++)
        {
            std::cout << "weights " << weightsAndAbscissaeM->v1[j] * weightsAndAbscissaeN->v1[i] << std::endl;
            //std::cout<<"value "<<weightsAndAbscissaeM->v1[j] * weightsAndAbscissaeN->v1[i]<<std::endl;

            double add = weightsAndAbscissaeM->v1[j] * weightsAndAbscissaeN->v1[i] * F->value(((xf - xi) / 2) * (weightsAndAbscissaeN->v2[i]) + (xf + xi) / 2, ((yf - yi) / 2) * (weightsAndAbscissaeM->v2[j]) + (yf + yi) / 2);
            std::cout << "add" << add << std::endl;
            integral += add;
        }
    }
    return ((yf - yi) / 2) * ((xf - xi) / 2) * integral;
}

twoVectsDoub *GaussianQuadrature::getMWeightsAndAbscissae(int MAX_ITERATIONS)
{
    LegendrePolynomial *legpoly = new LegendrePolynomial(m);
    std::vector<double> weights;
    legpoly->initializeZeros(acc, MAX_ITERATIONS);
    // std::cout << "weights mid" << std::endl;
    std::vector<double> abscissae = legpoly->getZeros();
    // std::cout << "weights end" << std::endl;
    for (int i = 0; i < abscissae.size(); i++)
    {
        //std::cout << "xvalues"<<abscissae[i] << std::endl;
        weights.push_back(2 / ((1 - pow(abscissae[i], 2)) * pow(legpoly->derivative(abscissae[i]), 2)));
        std::cout << "weights " << weights[i] << std::endl;
    }
    twoVectsDoub *weightsAndAbscissae = new twoVectsDoub(weights, abscissae);
    std::cout << "weights done" << std::endl;
    return weightsAndAbscissae;
    return weightsAndAbscissae;
}

twoVectsDoub *GaussianQuadrature::getWeightsAndAbscissae(int MAX_ITERATIONS, int n)
{
    LegendrePolynomial *legpoly = new LegendrePolynomial(n);
    std::vector<double> weights;
    legpoly->initializeZeros(acc, MAX_ITERATIONS);
    // std::cout << "weights mid" << std::endl;
    std::vector<double> abscissae = legpoly->getZeros();
    // std::cout << "weights end" << std::endl;
    for (int i = 0; i < abscissae.size(); i++)
    {
        //std::cout << "xvalues"<<abscissae[i] << std::endl;
        weights.push_back(2 / ((1 - pow(abscissae[i], 2)) * pow(legpoly->derivative(abscissae[i]), 2)));
        std::cout << "weights " << weights[i] << std::endl;
    }
    twoVectsDoub *weightsAndAbscissae = new twoVectsDoub(weights, abscissae);
    std::cout << "weights done" << std::endl;
    return weightsAndAbscissae;
    return weightsAndAbscissae;
}

void GaussianQuadrature::appendZerosToFiles(double acc, int MAX_ITERATIONS, std::ofstream *file)
{
    LegendrePolynomial *legpoly = new LegendrePolynomial(n);
    legpoly->initializeZeros(acc, MAX_ITERATIONS);
    std::vector<double> zeros = legpoly->getZeros();
    for (int i = 0; i < zeros.size(); i++)
    {
        *file << zeros[i];

        *file << "\n";
    }
}
