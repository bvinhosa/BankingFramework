#ifndef ZEROINTELDEPOSITOR_HPP
#define ZEROINTELDEPOSITOR_HPP

#include "../Strategies/RandomAgent.hpp"
#include "ConcreteDepositor.hpp"
#include "../Strategies/StrategyDistribution.hpp"

class ZeroIntelDepositor : public ConcreteDepositor,
                           public RandomAgent {
public:
    ZeroIntelDepositor(double withdrawalProbability,
                        const std::string & givenName,
                        int agentId,
                        int depositorId);
/*
    virtual bool reasonsCounterfactually(void) const;
    virtual void learnFromExperience(void);
    virtual void resetExperience(void);
    virtual void observePayoff(void);
    virtual bool isFactual(Strategy* givenStrategy) const;
    virtual void revertToFactual(void);
    virtual void setUpStrategy(Strategy* newStrategy);
    virtual void setUpForSimulation(void);

protected:
    Strategy* currentStrategy;
    StrategyDistribution distribution;*/

};


#endif //ZEROINTELDEPOSITOR_HPP
