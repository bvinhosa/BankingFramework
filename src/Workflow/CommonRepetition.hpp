#ifndef COMMONREPETITION_HPP
#define COMMONREPETITION_HPP

#include "Repeatable.hpp"
#include "Iterable.hpp"
#include "../Util/Analyzer.hpp"

class CommonRepetition : public Repeatable {
public:
    CommonRepetition(Cyclic& givenCyclic, int cyclesPerRep);
    virtual void repeat(StrategicBankingSystem& system);
    std::string getFinalResults(void);
private:
    const int cyclesPerRepetition;
    Cyclic& myCyclic;
    Analyzer theAnalyzer;
};


#endif //COMMONREPETITION_HPP
