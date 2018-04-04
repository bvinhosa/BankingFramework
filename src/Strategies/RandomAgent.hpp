#ifndef RANDOMAGENT_HPP
#define RANDOMAGENT_HPP

#include "StrategicAgent.hpp"
#include "StrategyExperience.hpp"

class RandomAgent : public StrategicAgent {
public:
    virtual void resetStrategies(void);
    virtual bool reasonsCounterfactually(void) const;
    virtual void learnFromExperience(void);
    virtual void resetExperience(void);
    virtual void observePayoff(void);
    virtual bool isFactual(Strategy* givenStrategy) const;
    virtual void revertToFactual(void);
    virtual void setUpStrategy(Strategy* newStrategy);
    virtual void setUpForSimulation(void);
    virtual StrategyPointerSet& getPossibleStrategies(void);
    virtual void suspendLearning(void);
    virtual void resumeLearning(void);
    virtual void forceStrategy(Strategy* forcedStrategy);
    virtual void freeStrategies();
protected:
    bool forcingStrategy=false;
    Strategy* currentStrategy;
    StrategyDistribution distribution;

};

#endif //RANDOMAGENT_HPP
