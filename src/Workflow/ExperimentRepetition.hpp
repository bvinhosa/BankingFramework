#ifndef EXPERIMENTREPETITION_HPP
#define EXPERIMENTREPETITION_HPP

#include "Repeatable.hpp"
#include "../Util/ExperimentAnalyzer.hpp"
#include "../Util/Analyzer.hpp"
#include <string>
#include "../Agents/Bank.hpp"
#include "../Agents/IntelligentBank.hpp"

class ExperimentRepetition : public Repeatable {
public:

/*
    struct Parameters{
        int numModerates; //= 3,
        int numSeveres; //= 2;
        double capModerate; //= 0.04;
        double liqModerate; //= 0.02;
        double capSevere; //= 0.02;
        double liqSevere; //= 0.01;
    };
*/

    ExperimentRepetition(Cyclic& givenCyclic,
                         int cyclesPerRep);
    virtual void repeat(StrategicBankingSystem& system);
    virtual std::string getFinalResults(void);
private:

    const int cyclesPerRepetition;

    Cyclic& myCyclic;
    Analyzer theAnalyzer;
    ExperimentAnalyzer expAnalyzer;

    /*

    BankPointerVector getDistinct(BankPointerVector banks,
                                  int howMany);

    std::pair<BankPointerVector, BankPointerVector>
    getModerateAndSeverelyStressed(BankPointerVector banks,
                                   int howManyModerately,
                                   int howManySeverely);

     */


    std::vector<IntelligentBank*> getDistinct(BankPointerVector banks,
                                  int howMany);

    std::pair<std::vector<IntelligentBank*>,
            std::vector<IntelligentBank*> >
    getModerateAndSeverelyStressed(BankPointerVector banks,
                                   int howManyModerately,
                                   int howManySeverely);
};


#endif //EXPERIMENTREPETITION_HPP
