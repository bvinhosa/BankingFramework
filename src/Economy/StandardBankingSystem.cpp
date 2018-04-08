#include "StandardBankingSystem.hpp"

#include <iostream>
#include <sstream>

#include "../Agents/ConcreteBank.hpp"
#include "../Agents/ConcreteDepositor.hpp"
#include "../Agents/ConcreteFirm.hpp"
#include "../Strategies/BankStrategy.hpp"
#include "../Strategies/ThresholdStrategy.hpp"
#include "MacroFinancialFactors.hpp"
#include "../Agents/ZeroIntelFirm.hpp"
#include "../Agents/IntelligentBank.hpp"
#include "../Agents/ThresholdDepositor.hpp"
#include "../Agents/ZeroIntelDepositor.hpp"

StandardBankingSystem::StandardBankingSystem(Parameters params,
                                             std::vector<double> sizes):
        systemParameters(params),
        assetMarket(centralBank){

    int agentIndex = 0;
    int depositorIndex = 0;
    int firmIndex = 0;

    std::cout << "numBanks: " << params.numBanks << std::endl;
    std::cout << "numDepositorsPerBank: " << params.numDepositorsPerBank << std::endl;

    double probabilityOfDefault =
            MacroFinancialFactors::getProbabilityOfDefault();
    double probabilityOfRunning =
            MacroFinancialFactors::getRunProbability();

    double depositorFraction = 1.0 / params.numDepositorsPerBank;
    double firmFraction = 1.0 / params.numFirmsPerBank;

    firmFractionMatrix.resize(params.numBanks);
    depositorFractionMatrix.resize(params.numBanks);

    std::set<Strategy*> BankStrategySet;
    std::set<Strategy*> DepositorStrategySet;

    for(int i = 0; i < 20; i++){
        for(int j = 0; j < 10; j++){
            Strategy* bankStrategy = new BankStrategy(0.01*(i+1),0.01*(j+1));
            BankStrategySet.insert(bankStrategy);

            Strategy* deposStrategy = new ThresholdStrategy(0.01*(i+1));
            DepositorStrategySet.insert(deposStrategy);
        }
    }

    for (int i = 0; i < params.numBanks; i++){

        depositorFractionMatrix[i].resize(params.numBanks *
                                          params.numDepositorsPerBank,
                                          0.0);
        firmFractionMatrix[i].resize(params.numBanks *
                                     params.numFirmsPerBank,
                                     0.0);

        std::string bankName = "Bank " +  std::to_string(i+1);
        IntelligentBank * bank = new IntelligentBank(BankStrategySet,
                                                     bankName,
                                                     agentIndex,
                                                     i);

        banks.push_back(static_cast<Bank*>(bank));
        strategicAgents.push_back(static_cast<StrategicAgent*>(bank));

        bank->setInitialAssetSize(sizes[i]);
        agentIndex++;

        for (int j = 0; j < params.numDepositorsPerBank; j++){
            std::string deposName = "Depositor " +
                    std::to_string(depositorIndex+1);
            ThresholdDepositor * depositor = new ThresholdDepositor(DepositorStrategySet,
                                                                    deposName,
                                                                    agentIndex,
                                                                    depositorIndex);
            /*
            ZeroIntelDepositor * depositor = new ZeroIntelDepositor(probabilityOfRunning,
                                               deposName,
                                               agentIndex,
                                               depositorIndex);
            */

            depositors.push_back(static_cast<Depositor*>(depositor));
            strategicAgents.push_back(static_cast<StrategicAgent*>(depositor));

            depositorFractionMatrix[i][depositorIndex] = depositorFraction;
            agentIndex++;
            depositorIndex++;
        }

        for (int k = 0; k < params.numFirmsPerBank; k++){
            std::string firmName = "Firm " +  std::to_string(firmIndex+1);
            ZeroIntelFirm * firm = new ZeroIntelFirm(probabilityOfDefault,
                                                     firmName,
                                                     agentIndex,
                                                     firmIndex);
            firms.push_back(static_cast<Firm*>(firm));
            strategicAgents.push_back(static_cast<StrategicAgent*>(firm));
            firmFractionMatrix[i][firmIndex] = firmFraction;
            agentIndex++;
            firmIndex++;
        }

    }
}

std::string StandardBankingSystem::toString(void) {
    return std::string("StandardBankingSystem::toString under construction");
}

void StandardBankingSystem::strategicReset(void){
    for(auto & agent : strategicAgents)
        agent->resetStrategies();
}

void StandardBankingSystem::operationalReset(void){
    for(auto & bank: banks)
        bank->reset();
    for(auto & depositor : depositors)
        depositor->reset();
    for(auto & firm: firms)
        firm->reset();

    activeBanks.clear();
    inactiveBanks.clear();
}

BankPointerVector&
StandardBankingSystem::getBanks(void){
    return banks;
}

DepositorPointerVector&
StandardBankingSystem::getDepositors(void){
    return depositors;
}

FirmPointerVector&
StandardBankingSystem::getFirms(void){
    return firms;
}

RiskyAssetMarket&
StandardBankingSystem::getAssetMarket(void){
    return assetMarket;
}

StrategicAgentPointerVector&
StandardBankingSystem::getStrategicAgents(void){
    return strategicAgents;
}

void
StandardBankingSystem::prepareForIteration(void) {

    numDepositRelationships = 0;

    for (Bank* bank: banks) {

        if(inactiveBanks.find(bank->getBankId()) != inactiveBanks.end())
            continue;
        activeBanks.push_back(bank);

        bank->raiseCapital(bank->getInitialEquity());

        double banksDeposits = bank->getInitialDeposits();
        if (banksDeposits > 0.0)
            createDeposits(bank,banksDeposits);

        double banksLoans = bank->getInitialLoans();
        if (banksLoans > 0.0)
            createLoans(bank,banksLoans);

    }
}

void
StandardBankingSystem::createDeposits(Bank* bank, double banksDeposits){
    int thisBanksId = bank->getBankId();

    for(Depositor* depositor: depositors){
        int thisDeposId = depositor->getDepositorId();
        double thisFraction = depositorFractionMatrix[thisBanksId][thisDeposId];
        if (thisFraction > 0.0) {
            numDepositRelationships++;
            double thisDeposit = banksDeposits * thisFraction;
            depositor->receiveMoney(thisDeposit);
            depositor->makeDeposit(bank, thisDeposit);
        }
    }
}

void
StandardBankingSystem::createLoans(Bank* bank, double banksLoans){
    int thisBanksId = bank->getBankId();

    for(Firm* firm: firms){
        int thisFirmsId = firm->getFirmId();
        double thisFraction = firmFractionMatrix[thisBanksId][thisFirmsId];
        if (thisFraction > 0.0){
            double thisLoan = banksLoans * thisFraction;
            bank->grantLoanToFirm(firm, thisLoan);
        }
    }
}

void StandardBankingSystem::reactivateBanks(void){
    inactiveBanks.clear();
}

void StandardBankingSystem::deactivateBank(int bankId){
    inactiveBanks.insert(bankId);
}

BankPointerVector& StandardBankingSystem::getActiveBanks(void){
    return activeBanks;
}


std::string StandardBankingSystem::showDepositorFractions(void){
    std::stringstream result;

    result << "Deposits as share of each banks' funds" << std::endl;
    for(int i = 0; i < systemParameters.numBanks; i++){
        result << "Bank " << i+1 << ":";
        for(int j = 0; j < (systemParameters.numBanks * systemParameters.numDepositorsPerBank); j++)
            result <<" " << depositorFractionMatrix[i][j];
        result << std::endl;
    }
    return result.str();
}

std::string StandardBankingSystem::showFirmFractions(void){
    std::stringstream result;

    result << "Loans as share of each bank's portfolio" << std::endl;
    for(int i = 0; i < systemParameters.numBanks; i++){
        result << "Bank " << i+1 << ":";
        for(int j = 0; j < (systemParameters.numBanks * systemParameters.numFirmsPerBank); j++)
            result <<" " << firmFractionMatrix[i][j];
        result << std::endl;
    }
    return result.str();
}

int StandardBankingSystem::howManyBanks() {
    return systemParameters.numBanks;
}

int StandardBankingSystem::howManyDepositors() {
    return (systemParameters.numBanks *
            systemParameters.numDepositorsPerBank);
}

int StandardBankingSystem::howManyBanksFailedLiquidity(void){
    int liquidityFailureCounter = 0;

    for(Bank* bank: banks){
        if (bank->getFailureCause() == BankFailureCause::liquidity)
            liquidityFailureCounter++;
    }
    return liquidityFailureCounter;
}

int StandardBankingSystem::howManyBanksFailedSolvency(void){
    int solvencyFailureCounter = 0;

    for(Bank* bank: banks){
        if (bank->getFailureCause() == BankFailureCause::solvency)
            solvencyFailureCounter++;
    }
    return solvencyFailureCounter;
}

int StandardBankingSystem::howManyDeposits(void) {
    return numDepositRelationships;
}
