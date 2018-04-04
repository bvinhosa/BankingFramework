#ifndef ZEROINTELSTRATEGY_HPP
#define ZEROINTELSTRATEGY_HPP


#include "Strategy.hpp"

class ZeroIntelStrategy : public Strategy{
public:
    ZeroIntelStrategy(double proportionToWithdraw);
    virtual void configure(StrategicAgent* theAgent);
    virtual double getPayoff(StrategicAgent* theAgent) const;
    virtual std::string toString(void) const;
private:
    double proportionToWithdraw;
};


#endif //ZEROINTELSTRATEGY_HPP
