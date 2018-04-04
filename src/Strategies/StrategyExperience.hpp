#ifndef STRATEGYEXPERIENCE_HPP
#define STRATEGYEXPERIENCE_HPP

#include <map>

#include "StrategyDistribution.hpp"
#include "StrategicAgent.hpp"

class EWAParameters{
public:
    double getDelta(void) const {return 1.0;}
    double getPhi(void) const {return 1.0;}
    double getLambda(void) const {return 1.0;}
    double getRho(void) const {return 0.0;}
};

class StrategyExperience {
public:
    //make according to pre-specified distribution
    //virtual StrategyExperience(StrategyDistribution);
    //make according to uniform
    //virtual StrategyExperience(StrategySet);
    //virtual StrategyDistribution& getDistribution(void) const;
    //virtual StrategySet& getSrategySet(void) const;

    virtual void initUniform(std::set<Strategy*> strategySet);

    virtual void reset(void);
    std::string toString(void);

    virtual StrategyPointerSet& getStrategies(void);

    virtual Strategy* drawStrategy(void);

    virtual void observePayoff(Strategy* strategy,
                               StrategicAgent* agent);

    virtual void learn(Strategy* factual,
                       StrategicAgent* agent);

private:
    double N_t = 1, N_tMinus1 = 0;

    //initial probabilities

    std::set<Strategy*> thisAgentsStrategies;
    std::map<Strategy*,double> probabilities;
    std::map<Strategy*,double> attractions;
    std::map<Strategy*,double> payoffs;

    EWAParameters localPhony;

    virtual void learn(const EWAParameters& givenParameters,
                       Strategy* factual,
                       StrategicAgent* agent);

    virtual void resetDistributionToUniform(void);
};

#endif //STRATEGYEXPERIENCE_HPP
