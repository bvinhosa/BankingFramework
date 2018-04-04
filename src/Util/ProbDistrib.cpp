#include "ProbDistrib.hpp"

#include "ProbDistrib.hpp"
#include <chrono>
#include <cmath>
#include <algorithm>
#include <vector>
#include <random>

//initialization of static variables
bool ProbDistrib::active = false;
int ProbDistrib::seed=0;
std::mt19937 ProbDistrib::generator;
ProbDistrib* ProbDistrib::theInstance;

ProbDistrib::ProbDistrib(){
    active = true;
    initRandomNumberGenerator();
}

ProbDistrib::ProbDistrib(int seed){
    active = true;
    initRandomNumberGenerator(seed);
}

ProbDistrib& ProbDistrib::instance(void){
    if(!active){
        theInstance = (new ProbDistrib);
    }

    return *theInstance;
}

ProbDistrib& ProbDistrib::instance(int seed){
    if(!active){
        theInstance = new ProbDistrib(seed);
    }

    return *theInstance;
}

void ProbDistrib::initRandomNumberGenerator(void){
    std::random_device rd;
    seed = rd();
    //seed = std::chrono::system_clock::now().time_since_epoch().count();
    generator.seed(seed);
}

void ProbDistrib::initRandomNumberGenerator(int seed){
    generator.seed(seed);
}

int ProbDistrib::getSeed(void){
    return seed;
}

int ProbDistrib::drawBinomial(int count, double singleEventProb) {

    std::binomial_distribution<int> distribution(count, singleEventProb);

    int random;

    random = distribution(generator);

    return random;
}

double ProbDistrib::drawUniformContinuous(double lowerBound, double upperBound){

    std::uniform_real_distribution<double> distribution(lowerBound,upperBound);

    double random;

    random = distribution(generator);

    return random;
}

int ProbDistrib::drawUniformDiscrete(int minimum, int maximum) {

    std::uniform_int_distribution<int> distribution(minimum,maximum);

    int random;

    random = distribution(generator);

    return random;
}

double ProbDistrib::drawLogNormal(double mu, double sigma){

    std::lognormal_distribution<double> distribution(mu,sigma);

    double random;

    random = distribution(generator);

    return random;
}

double ProbDistrib::drawTriangular(double lowerBound,
                                   double mode,
                                   double upperBound){

    //references used for aliasing, in order to keep calculations concise
    double & a = lowerBound;
    double & b = upperBound;
    double & c = mode;

    double triangularRandom;

    double u = drawUniformContinuous(0.0, 1.0);
    double f_c = (c-a)/(b-a);

    if (u < f_c)
        triangularRandom = a + std::sqrt(u*(b-a)*(c-a));
    else
        triangularRandom = b - std::sqrt((1.0-u)*(b-a)*(b-c));

    return triangularRandom;
}

std::vector<double> ProbDistrib::getNormalizedLogNormal(int howMany,
                                                        double mu,
                                                        double sigma){

    double totalActualSize = 0.0;
    std::vector<double> sizes;

    for (int i = 0; i<howMany; i++) {
        double size = drawLogNormal(mu, sigma);
        sizes.push_back(size);
        totalActualSize += size;
    }

    double scalingFactor = howMany / totalActualSize;

    // Change each bank's size but preserve relative sizes
    for (int i = 0; i<howMany; i++)
        sizes[i] *= scalingFactor;

    return sizes;
}

std::mt19937 & ProbDistrib::getGenerator(void) {
    return generator;
}

std::vector<int> ProbDistrib::multipleDrawDistinct(int elementsToDraw,
                                                   int  totalElements){

    std::vector<int> initial, final;

    for (int i = 0; i < totalElements; i++){
        initial.push_back(i);
    }

    for (int j = 0; j < elementsToDraw; j++){
        int indexToDraw = drawUniformDiscrete(0,(totalElements-j));
        int elementToRemove = initial[indexToDraw];

        initial.erase(
                std::remove(
                        initial.begin(),
                        initial.end(),
                        elementToRemove),
                initial.end());

        //remove from initial
        final.push_back(elementToRemove);
    }

    return final;
}