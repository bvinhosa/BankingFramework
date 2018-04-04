#ifndef STRATEGICAGENT_HPP
#define STRATEGICAGENT_HPP

#include <vector>
#include <set>
#include "Strategy.hpp"

class StrategicAgent{
public:
    virtual void resetStrategies(void) = 0;
    virtual bool reasonsCounterfactually(void) const = 0;
    virtual void learnFromExperience(void) = 0;
    virtual void resetExperience(void) = 0;
    virtual void observePayoff(void) = 0;
    virtual bool isFactual(Strategy* givenStrategy) const = 0;
    virtual void revertToFactual(void) = 0;
    virtual void setUpStrategy(Strategy* newStrategy) = 0;
    virtual void setUpForSimulation(void) = 0;
    virtual StrategyPointerSet& getPossibleStrategies(void) = 0;
    virtual void suspendLearning(void) = 0;
    virtual void resumeLearning(void) = 0;
    virtual void forceStrategy(Strategy* forcedStrategy) = 0;
    virtual void freeStrategies() = 0;
};

typedef std::vector<StrategicAgent*> StrategicAgentPointerVector;

#endif //STRATEGICAGENT_HPP
