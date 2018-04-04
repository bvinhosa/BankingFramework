#ifndef STRATEGY_HPP
#define STRATEGY_HPP

#include <string>
#include <set>
#include <vector>

class StrategicAgent;

class Strategy {
public:
    virtual void configure(StrategicAgent* theAgent) = 0;
    virtual double getPayoff(StrategicAgent* theAgent) const = 0;
    virtual std::string toString(void) const = 0;
};

typedef std::vector<Strategy*> StrategyPointerVector;
typedef std::set<Strategy*> StrategyPointerSet;

#endif //STRATEGY_HPP
