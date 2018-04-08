#ifndef PROBDISTRIB_HPP
#define PROBDISTRIB_HPP

#include <random>
#include <vector>

class ProbDistrib{
public:
    static ProbDistrib& instance(void);
    static ProbDistrib& instance(int seed);

    int getSeed(void);

    std::mt19937 & getGenerator(void);

    int drawBinomial(int count,
                     double singleEventProb);

    double drawUniformContinuous(double lowerBound,
                                 double upperBound);

    int drawUniformDiscrete(int minimum,
                            int maximum);

    double drawTriangular(double lowerBound,
                          double mode,
                          double upperBound);

    double drawLogNormal(double mu, double sigma);

    std::vector<double> getNormalizedLogNormal(int howMany,
                                               double mu,
                                               double sigma);

    std::vector<int> multipleDrawDistinct(int elementsToDraw,
                                          int  totalElements);
private:
    ProbDistrib();
    explicit ProbDistrib(int seed);

    static ProbDistrib* theInstance;
    static bool active;

    static int seed;

    static std::mt19937 generator;

    static void initRandomNumberGenerator(void);
    static void initRandomNumberGenerator(int seed);
};



#endif //PROBDISTRIB_HPP
