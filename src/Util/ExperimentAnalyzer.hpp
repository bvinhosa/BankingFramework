#ifndef EXPERIMENTANALYZER_HPP
#define EXPERIMENTANALYZER_HPP

#include <string>

class BankingSystem;

class ExperimentAnalyzer {
public:
    virtual void respondLaissezFaire(BankingSystem& system);
    virtual void respondTimelyResolution(BankingSystem& system);
    virtual std::string toString();
private:
    int laissezFaireCounter = 0;
    int timelyResolutionCounter = 0;
};


#endif //EXPERIMENTANALYZER_HPP
