#ifndef BANKSTRATEGY_HPP
#define BANKSTRATEGY_HPP

#include "Strategy.hpp"

class BankStrategy : public Strategy{
public:
    BankStrategy(double givenCapital, double givenLiquidity);
    virtual void configure(StrategicAgent* theAgent) override;
    virtual double getPayoff(StrategicAgent* theAgent) const override;
    virtual std::string toString(void) const;
private:
    double capital, liquidity;
};

#endif //BANKSTRATEGY_HPP
