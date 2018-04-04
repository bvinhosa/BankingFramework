#ifndef THRESHOLDDEPOSITOR_HPP
#define THRESHOLDDEPOSITOR_HPP

#include "ConcreteDepositor.hpp"
#include "../Strategies/EWAAgent.hpp"
#include "../Strategies/StrategyExperience.hpp"

#include <set>
#include <string>

class ThresholdDepositor : public ConcreteDepositor,
                           public EWAAgent {
public:
    ThresholdDepositor(std::set<Strategy*> strategySet,
                       const std::string & givenName,
                       int agentId,
                       int depositorId);
/*
    virtual std::string toString(void);

    virtual bool reasonsCounterfactually(void) const;
    virtual void learnFromExperience(void);
    virtual void observePayoff(void);
    virtual void resetExperience(void);
    virtual bool isFactual(Strategy* givenStrategy) const;
    virtual void revertToFactual(void);

    virtual void setUpStrategy(Strategy* newStrategy);
    virtual void setUpForSimulation(void);

    virtual void suspendLearning(void);
    virtual void resumeLearning(void);

    virtual void forceStrategy(Strategy* forcedStrategy);
    virtual void freeStrategies();

protected:
    bool learningSuspended=false;
    bool forcingStrategy=false;
    Strategy* currentFactual;
    Strategy* currentStrategy;
    StrategyExperience myExperience;*/
};


#endif //THRESHOLDDEPOSITOR_HPP
