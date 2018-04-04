#ifndef INTELLIGENTBANK_HPP
#define INTELLIGENTBANK_HPP

#include "ConcreteBank.hpp"
#include "../Strategies/EWAAgent.hpp"
#include "../Strategies/StrategyExperience.hpp"

class IntelligentBank : public ConcreteBank,
                        public EWAAgent{
public:

    IntelligentBank(std::set<Strategy*> strategySet,
                    const std::string & givenName,
                    int agentId,
                    int bankId);

    virtual std::string toString(void);

};


#endif //EWABASICS_INTELLIGENTBANK_HPP
