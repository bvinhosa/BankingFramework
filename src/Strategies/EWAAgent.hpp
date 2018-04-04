#ifndef EWAAGENT_HPP
#define EWAAGENT_HPP

#include "StrategicAgent.hpp"
#include "StrategyExperience.hpp"

class EWAAgent : public StrategicAgent {
public:
    //EWAAgent(std::set<Strategy*> strategySet);

    virtual void resetStrategies(void);
    virtual bool reasonsCounterfactually(void) const;
    virtual void learnFromExperience(void);
    virtual void observePayoff(void);
    virtual void resetExperience(void);
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
    bool learningSuspended=false;
    bool forcingStrategy=false;
    Strategy* currentFactual;
    Strategy* currentStrategy;
    StrategyExperience myExperience;
};


#endif //EWAAGENT_HPP
