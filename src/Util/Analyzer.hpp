#ifndef ANALYZER_HPP
#define ANALYZER_HPP

#include <string>
#include <vector>

class BankingSystem;

class Analyzer {
public:
    virtual std::string toString(void);
    virtual void respondEndOfRepetition(BankingSystem& system);

private:

    unsigned int numReps=0;
    unsigned int numBanksTimesReps=0;
    unsigned int numDeposTimesReps=0;
    unsigned int numDeposRelatTimesReps = 0;

    unsigned int totalInsolvencies=0;
    unsigned int totalIlliquidityEvents=0;

    unsigned int totalBankRuns=0;

    std::vector<double> chosenLiquidity;
    std::vector<double> chosenCapital;

    std::vector<double> bankProfit;
    std::vector<double> liquidatedBankProfit;
    std::vector<double> nonLiquidatedBankProfit;

    std::vector<double> observedCapitalAtLiquidation;
    std::vector<double> observedLiquidityAtLiquidation;

    std::vector<double> observedCapitalAtRun;
    std::vector<double> observedLiquidityAtRun;

    std::vector<double> depositorProfit;
    std::vector<double> chosenRunThreshold;
};


#endif //ANALYZER_HPP
