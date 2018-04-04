#ifndef FIRMSTRATEGY_HPP
#define FIRMSTRATEGY_HPP

#include "Strategy.hpp"

class FirmStrategy : public Strategy {
public:
    FirmStrategy(bool willDefault);
    virtual void configure(StrategicAgent* theAgent) override;
    virtual double getPayoff(StrategicAgent* theAgent) const override;
    virtual std::string toString(void) const;
private:
    bool hasDefaulted;
};


#endif //FIRMSTRATEGY_HPP
