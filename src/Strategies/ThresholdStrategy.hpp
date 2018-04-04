#ifndef THRESHOLDSTRATEGY_HPP
#define THRESHOLDSTRATEGY_HPP

#include "Strategy.hpp"

class ThresholdStrategy : public Strategy{
public:
    ThresholdStrategy(double runThreshold);
    virtual void configure(StrategicAgent* theAgent);
    virtual double getPayoff(StrategicAgent* theAgent) const;
    virtual std::string toString(void) const;
private:
    double runThreshold;
};

#endif //THRESHOLDSTRATEGY_HPP
