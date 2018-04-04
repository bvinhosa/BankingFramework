#include "StrategyDistribution.hpp"

#include <sstream>

#include "../Util/ProbDistrib.hpp"

Strategy* StrategyDistribution::drawStrategy(void){
    ProbDistrib& randomly = ProbDistrib::instance();

    double uniformDraw = randomly.drawUniformContinuous(0.0,1.0);

    double lowerBound = 0.0;

    for(auto element: distribution){
        double upperBound = lowerBound + element.second;

        if((uniformDraw >= lowerBound) && (uniformDraw <= upperBound)){
            return element.first;
        }
        lowerBound = upperBound;
    }
    return nullptr;
}

void StrategyDistribution::initDeterministic(Strategy* determStrategy){
    distribution.clear();
    distribution[determStrategy] = 1.0;
}

void StrategyDistribution::initSingleEvent(Strategy* presence,
                                           Strategy* absence,
                                           double p){
    distribution.clear();
    distribution[presence] = p;
    distribution[absence] = (1.0 - p);
}

void StrategyDistribution::initUniform(std::set<Strategy*> strategySet){
    int numStrategies = strategySet.size();
    double uniformProbability = 1.0 / numStrategies;

    distribution.clear();

    for(auto * element: strategySet)
        distribution[element] = uniformProbability;
}

StrategyPointerSet& StrategyDistribution::getStrategies(void){
    std::set<Strategy*> strategies;

    for(auto element: distribution)
        strategies.insert(element.first);

    return strategies;
}


std::string StrategyDistribution::toString(void){
    std::stringstream ss;

    for(auto element: distribution){
        ss << element.first->toString()
           << "; p = "
           << element.second << std::endl;
    }

    return ss.str();
}
