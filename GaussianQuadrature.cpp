#include "GaussianQuadrature.h"

GaussianQuadrature::GaussianQuadrature(int n, double acc, int MAX_ITERATIONS)
{
        std::cout<<"THE BAD CONSTRUCTOR IS BEING CALLED"<<std::endl;
    this->n = n;
    this->acc = acc;
    this->m = 0;
    this->NWeightsAndAbscissae = initializeWeightsAndAbscissae(MAX_ITERATIONS, n);
    this->MWeightsAndAbscissae=nullptr;
}

GaussianQuadrature::GaussianQuadrature(int n, int m, double acc, int MAX_ITERATIONS)
{
    std::cout<<"THE CORRECT CONSTRUCTOR IS BEING CALLED"<<std::endl;
    this->n = n;
    this->acc = acc;
    this->m = m;
    this->NWeightsAndAbscissae = initializeWeightsAndAbscissae(MAX_ITERATIONS, n);
    this->MWeightsAndAbscissae = initializeWeightsAndAbscissae(MAX_ITERATIONS, m);
        std::cout<<NWeightsAndAbscissae->v1.size()<<std::endl;
        std::cout<<NWeightsAndAbscissae->v2.size()<<std::endl;

}

twoVectsDoub *GaussianQuadrature::getNWeightsAndAbscissae()
{
    return NWeightsAndAbscissae;
}
twoVectsDoub *GaussianQuadrature::getMWeightsAndAbscissae()
{
    return MWeightsAndAbscissae;
}

double GaussianQuadrature::getOneDIntegral(double xi, double xf, OneDFunction *F, int MAX_ITERATIONS)
{
    twoVectsDoub *weightsAndAbscissae = getNWeightsAndAbscissae();

    double integral = 0;
    for (int i = 0; i < weightsAndAbscissae->v1.size(); i++)
    {
        double temp = weightsAndAbscissae->v1[i] * F->value(((xf - xi) / 2) * (weightsAndAbscissae->v2[i]) + (xf + xi) / 2);
        integral += temp;
        std::cout << "My add: " << temp << std::endl;
    }

    return ((xf - xi) / 2) * integral;
}

void GaussianQuadrature::setAcc(double acc)
{
    this->acc = acc;
}

double GaussianQuadrature::getTwoDIntegral(double xi, double xf, double yi, double yf, Function *F, int MAX_ITERATIONS)
{
    twoVectsDoub *NWeightsAndAbscissae = getNWeightsAndAbscissae();
    twoVectsDoub *MWeightsAndAbscissae = getMWeightsAndAbscissae();
    if(this->MWeightsAndAbscissae==nullptr)
    {
        std::cout<<"Error: not initialzied for 2D integral"<<std::endl;
        return 0;
    }
                std::cout << "HIHIHI " << std::endl;
    double integral = 0;
    for (int j = 0; j < MWeightsAndAbscissae->v1.size(); j++)
    {
        for (int i = 0; i < NWeightsAndAbscissae->v1.size(); i++)
        {
            std::cout << "weights " << MWeightsAndAbscissae->v1[j] * NWeightsAndAbscissae->v1[i] << std::endl;
            //std::cout<<"value "<<weightsAndAbscissaeM->v1[j] * weightsAndAbscissaeN->v1[i]<<std::endl;

            double add = MWeightsAndAbscissae->v1[j] * NWeightsAndAbscissae->v1[i] * F->value(((xf - xi) / 2) * (NWeightsAndAbscissae->v2[i]) + (xf + xi) / 2, ((yf - yi) / 2) * (MWeightsAndAbscissae->v2[j]) + (yf + yi) / 2);
            std::cout << "add" << add << std::endl;
            integral += add;
        }
    }
    return ((yf - yi) / 2) * ((xf - xi) / 2) * integral;
}

twoVectsDoub *GaussianQuadrature::initializeWeightsAndAbscissae(int MAX_ITERATIONS, int n)
{
    LegendrePolynomial *legpoly = new LegendrePolynomial(n, acc, MAX_ITERATIONS);
    std::vector<double> weights;
    std::vector<double> abscissae = legpoly->getZeros();
    std::cout << "abscissae size"<<abscissae.size() << std::endl;

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

void GaussianQuadrature::appendZerosToFiles(int MAX_ITERATIONS, std::ofstream *file)
{
    LegendrePolynomial *legpoly = new LegendrePolynomial(n, acc, MAX_ITERATIONS);
    std::vector<double> zeros = legpoly->getZeros();
    std::cout << "Done generating zeros..." << std::endl;
    for (int i = 0; i < zeros.size(); i++)
    {
        *file << zeros[i];

        *file << "\n";
    }
    std::cout << "Done appending zeros to file..." << std::endl;
}

double GaussianQuadrature::getOneDIntegralFromFile(std::ifstream *weights, std::ifstream *nodes, double xi, double xf, OneDFunction *F)
{
    double weight;
    double node;
    double integral = 0;
    if (weights->is_open() && nodes->is_open())
    {
        while (*weights >> weight && *nodes >> node)
        {
            double temp = weight * F->value(((xf - xi) / 2) * (node) + (xf + xi) / 2);
            integral += temp;
            std::cout << std::setprecision(20) << "File add: " << temp << std::endl;
        }
    }
    return ((xf - xi) / 2) * integral;
}
double GaussianQuadrature::getTwoDIntegralFromFile(std::ifstream *weights1, std::ifstream *nodes1, std::ifstream *weights2, std::ifstream *nodes2, double xi, double xf, double yi, double yf, Function *F)
{
    double w1;
    double n1;
    double w2;
    double n2;
    double integral = 0;

    std::vector<double> weight1;
    std::vector<double> node1;
    std::vector<double> weight2;
    std::vector<double> node2;

    if (weights1->is_open() && nodes1->is_open())
    {
        std::cout << "Weights1 is open" << std::endl;

        while (*weights1 >> w1 && *nodes1 >> n1)
        {
            std::cout << "weights1 is being read" << std::endl;
            weight1.push_back(w1);
            node1.push_back(n1);
        }
    }

    if (weights2->is_open() && nodes2->is_open())
    {
        std::cout << "Weights2 is open" << std::endl;
        while (*weights2 >> w2 && *nodes2 >> n2)
        {
            std::cout << "weights2 is being read" << std::endl;
            weight2.push_back(w2);
            node2.push_back(n2);
        }
    }

    for (int i = 0; i < weight1.size(); i++)
    {
        for (int j = 0; j < weight2.size(); j++)
        {
            double add = weight1[i] * weight2[j] * F->value(((xf - xi) / 2) * (node2[j]) + (xf + xi) / 2, ((yf - yi) / 2) * (node1[i]) + (yf + yi) / 2);

            integral += add;
        }
    }
    return ((yf - yi) / 2) * ((xf - xi) / 2) * integral;
}

void GaussianQuadrature::initializeFromFile(std::ifstream *weights1, std::ifstream *nodes1, std::ifstream *weights2, std::ifstream *nodes2, double xi, double xf, double yi, double yf, Function *F)
{
    double w1;
    double n1;
    double w2;
    double n2;
    double integral = 0;

    std::vector<double> weight1;
    std::vector<double> node1;
    std::vector<double> weight2;
    std::vector<double> node2;

    if (weights1->is_open() && nodes1->is_open())
    {
        std::cout << "Weights1 is open" << std::endl;

        while (*weights1 >> w1 && *nodes1 >> n1)
        {
            std::cout << "weights1 is being read" << std::endl;
            weight1.push_back(w1);
            node1.push_back(n1);
        }
    }

    if (weights2->is_open() && nodes2->is_open())
    {
        std::cout << "Weights2 is open" << std::endl;
        while (*weights2 >> w2 && *nodes2 >> n2)
        {
            std::cout << "weights2 is being read" << std::endl;
            weight2.push_back(w2);
            node2.push_back(n2);
        }
    }

    

}