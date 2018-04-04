#ifndef ZEROINTELFIRM_HPP
#define ZEROINTELFIRM_HPP

#include "ConcreteFirm.hpp"
#include "../Strategies/RandomAgent.hpp"
#include "../Strategies/FirmStrategy.hpp"

class ZeroIntelFirm : public ConcreteFirm,
                      public RandomAgent {
public:
    ZeroIntelFirm(double probabilityOfDefault,
                    const std::string & givenName,
                    int agentId,
                    int firmId);
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

#endif //ZEROINTELFIRM_HPP
