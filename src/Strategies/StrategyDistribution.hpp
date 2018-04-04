#ifndef STRATEGYDISTRIBUTION_HPP
#define STRATEGYDISTRIBUTION_HPP

#include <map>
#include <set>
#include "Strategy.hpp"

class StrategyDistribution {
public:
    virtual void initUniform(std::set<Strategy*> strategySet);
    virtual void initDeterministic(Strategy* determStrategy);
    virtual void initSingleEvent(Strategy* presence, Strategy* absence, double p);
    virtual Strategy* drawStrategy(void);
    virtual StrategyPointerSet& getStrategies(void);

    virtual std::string toString(void);
private:
    std::map<Strategy*,double> distribution;
};

#endif //STRATEGYDISTRIBUTION_HPP
