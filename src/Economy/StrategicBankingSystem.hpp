#ifndef STRATEGICBANKINGSYSTEM_HPP
#define STRATEGICBANKINGSYSTEM_HPP

#include "BankingSystem.hpp"
#include "../Strategies/StrategicAgent.hpp"

class StrategicBankingSystem : public BankingSystem {
public:
    virtual StrategicAgentPointerVector& getStrategicAgents(void) = 0;
    virtual void prepareForIteration(void) = 0;
    virtual void strategicReset(void) = 0;
};

#endif //STRATEGICBANKINGSYSTEM_HPP
