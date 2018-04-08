#include "Analyzer.hpp"

#include <sstream>
#include <iostream>
#include "../Economy/BankingSystem.hpp"
#include "SampleStatistics.hpp"

using std::string;
using std::stringstream;

string Analyzer::toString() {
    //return (string("Analyzer's counter: ") + std::to_string(numReps));

    stringstream analysis;

    double insolvencyFrequency =
            ((double) totalInsolvencies) /
            ((double)numBanksTimesReps);

    double bankRunFrequency =
            ((double)totalBankRuns) /
            ((double)numDeposRelatTimesReps);

    analysis << "Number of Repetitions: " << numReps << std::endl;
    analysis << "Number of Banks-Reps: " << numBanksTimesReps << std::endl;
    analysis << "Number of Depositors-Reps: " << numDeposTimesReps << std::endl;
    analysis << "Number of Deposits-Reps: " << numDeposRelatTimesReps << std::endl;

    analysis << "Total insolvencies: " << totalInsolvencies << std::endl;
    analysis << "Total illiquidity events: " << totalIlliquidityEvents << std::endl;

/*
    analysis << "Regulatory insolvencies: " << regulatorylInsolvencies << std::endl;
    analysis << "Regulatory illiquidity events: " << regulatoryIlliquidityEvents << std::endl;
*/

    analysis << "Total Bank Runs: " << totalBankRuns << std::endl;

    analysis 	<< "Total insolvency frequency: "
                 << insolvencyFrequency << std::endl;
    analysis 	<< "Total bank run frequency: "
                 << bankRunFrequency << std::endl;
/*
    analysis 	<< "Depositor's effective haircut at liquidation: " <<
                 SampleStatistics::sampleMean(
                         effectiveDepositorHaircutAtLiquidation) << std::endl;
*/
    analysis 	<< "Bank capital observed over all liquidation events: " << std::endl <<
                 SampleStatistics::sampleMetricsString(observedCapitalAtLiquidation)
                 << std::endl;
    analysis	<< "Bank liquidity observed over all liquidation events: " << std::endl <<
                 SampleStatistics::sampleMetricsString(observedLiquidityAtLiquidation)
                 << std::endl;
/*
    analysis 	<< "Bank capital observed at balance sheet insolvency: " << std::endl <<
                 SampleStatistics::sampleMetricsString(observedCapitalAtBSInsolvency)
                 << std::endl;
    analysis	<< "Bank liquidity observed at balance sheet insolvency: " << std::endl <<
                 SampleStatistics::sampleMetricsString(observedLiquidityAtBSInsolvency)
                 << std::endl;

    analysis 	<< "Bank capital observed at balance sheet illiquidity: " << std::endl <<
                 SampleStatistics::sampleMetricsString(observedCapitalAtBSIlliquidity)
                 << std::endl;
    analysis	<< "Bank liquidity observed at balance sheet illiquidity: " << std::endl <<
                 SampleStatistics::sampleMetricsString(observedLiquidityAtBSIlliquidity)
                 << std::endl;

    analysis 	<< "Bank capital observed at regulatory insolvency: " << std::endl <<
                 SampleStatistics::sampleMetricsString(observedCapitalAtRegInsolvency)
                 << std::endl;
    analysis	<< "Bank liquidity observed at regulatory insolvency: " << std::endl <<
                 SampleStatistics::sampleMetricsString(observedLiquidityAtRegInsolvency)
                 << std::endl;

    analysis 	<< "Bank capital observed at regulatory illiquidity: " << std::endl <<
                 SampleStatistics::sampleMetricsString(observedCapitalAtRegIlliquidity)
                 << std::endl;
    analysis	<< "Bank liquidity observed at regulatory illiquidity: " << std::endl <<
                 SampleStatistics::sampleMetricsString(observedLiquidityAtRegIlliquidity)
                 << std::endl;
*/
    analysis 	<< "Bank capital observed by depositors at time of run: "
                 << SampleStatistics::sampleMean(observedCapitalAtRun)
                 << std::endl;
    analysis	<< "Bank liquidity observed by depositors at time of run: "
                 << SampleStatistics::sampleMean(observedLiquidityAtRun)
                 << std::endl;

    analysis 	<< "Banks' Mean Chosen Capital: " <<
                 SampleStatistics::sampleMean(chosenCapital) << std::endl;

    analysis 	<< "Depositors' Chosen Run Threshold: " <<
                 SampleStatistics::sampleMean(chosenRunThreshold) << std::endl;

    analysis 	<< "Banks' Mean Profit: " <<
                 SampleStatistics::sampleMean(bankProfit) << std::endl;
    analysis 	<< "Mean Profit of banks that were not liquidated: " <<
                 SampleStatistics::sampleMean(nonLiquidatedBankProfit) << std::endl;
    analysis 	<< "Mean Profit of banks that were liquidated: " <<
                 SampleStatistics::sampleMean(liquidatedBankProfit) << std::endl;

    analysis 	<< "Depositors' Profit: " << std::endl <<
                 SampleStatistics::sampleMetricsString(depositorProfit)
                 << std::endl;
/*
    analysis 	<< "Profit of Depositors who ran: " << std::endl <<
                 SampleStatistics::sampleMetricsString(depositorRanProfit)
                 << std::endl;

    analysis 	<< "Profit of Depositors who did not run: " << std::endl <<
                 SampleStatistics::sampleMetricsString(depositorNotRanProfit)
                 << std::endl;

    analysis 	<< "Profit of Depositors at Non-Liquidated Banks: " << std::endl <<
                 SampleStatistics::sampleMetricsString(depositorBankNotLiquidatedProfit)
                 << std::endl;

    analysis 	<< "Profit of Depositors who ran at Non-Liquidated Banks: " << std::endl <<
                 SampleStatistics::sampleMetricsString(depositorRanBankNotLiquidatedProfit) << std::endl;

    analysis 	<< "Profit of Depositors who did not run at Non-Liquidated Banks: " << std::endl <<
                 SampleStatistics::sampleMetricsString(depositorNotRanBankNotLiquidatedProfit) << std::endl;

    analysis 	<< "Depositors' Profit at Liquidated Banks: " << std::endl <<
                 SampleStatistics::sampleMetricsString(depositorBankLiquidatedProfit) << std::endl;

    analysis 	<< "Profit of Depositors who ran at Liquidated Banks: " << std::endl <<
                 SampleStatistics::sampleMetricsString(depositorRanBankLiquidatedProfit) << std::endl;

    analysis 	<< "Profit of Depositors who did not run at Liquidated Banks: " << std::endl <<
                 SampleStatistics::sampleMetricsString(depositorNotRanBankLiquidatedProfit) << std::endl;

*/
    return analysis.str();
}

void Analyzer::respondEndOfRepetition(BankingSystem &system) {

    numReps++;

    numBanksTimesReps += system.howManyBanks();
    numDeposTimesReps += system.howManyDepositors();
    numDeposRelatTimesReps += system.howManyDeposits();

    ////regulatorylInsolvencies += centralBank->getRegulatoryCapitalLiquidationCounter();
    ////totalInsolvencies += centralBank->getRegulatoryCapitalLiquidationCounter();
    totalInsolvencies += system.howManyBanksFailedSolvency();

    ////regulatoryIlliquidityEvents += centralBank->getRegulatoryLiquidityLiquidationCounter();
    ////totalIlliquidityEvents += centralBank->getRegulatoryLiquidityLiquidationCounter();
    totalIlliquidityEvents += system.howManyBanksFailedLiquidity();

    for(Bank* bank : system.getBanks()){

        double initialAssets = bank->getInitialAssetSize();
        double initialLiquidity = bank->getInitialCash() / initialAssets;
        double initialCapital  = bank->getInitialEquity() / initialAssets;

        chosenLiquidity.push_back(initialLiquidity);
        chosenCapital.push_back(initialCapital);

        bankProfit.push_back(bank->getReturnOnEquity());

        if(bank->hasFailed()){
            liquidatedBankProfit.push_back(bank->getReturnOnEquity());

            observedLiquidityAtLiquidation.push_back(bank->getLiquidityAtFailure());
            observedCapitalAtLiquidation.push_back(bank->getCapitalAtFailure());


        }
        else{
            nonLiquidatedBankProfit.push_back(bank->getReturnOnEquity());
        }
    }

    for(Depositor* depositor : system.getDepositors()){

        double currentProfit = depositor->getReturnOnDeposit();

        chosenRunThreshold.push_back(depositor->getThreshold());
        depositorProfit.push_back(currentProfit);

        for(auto & bankRunInfo: depositor->getBankRuns()){
            totalBankRuns++;

            observedCapitalAtRun.push_back(bankRunInfo.capitalAtRun);
            observedLiquidityAtRun.push_back(bankRunInfo.liquidityAtRun);
        }
    }
}
