#include "MacroFinancialFactors.hpp"

//initialization of static variables

double MacroFinancialFactors::interestRateDeposits = 0.005;
double MacroFinancialFactors::interestRateLoans = 0.08;
double MacroFinancialFactors::interestRateBanks = 0.01;
double MacroFinancialFactors::insolvencyHaircut = 0.25;
double MacroFinancialFactors::bankruptcyCosts = 0.1;
double MacroFinancialFactors::assetReservationPrice = 0.75;
double MacroFinancialFactors::lossGivenDefault = 0.5;
double MacroFinancialFactors::probabilityOfDefault = 0.05;
double MacroFinancialFactors::liquidityShockProbability = 0.1;

double MacroFinancialFactors::getInterestRateDeposits(void){
    return interestRateDeposits;
}

double MacroFinancialFactors::getInterestRateLoans(void){
    return interestRateLoans;
}

double MacroFinancialFactors::getInterestRateBanks(void) {
    return interestRateBanks;
}

double MacroFinancialFactors::getInsolvencyHaircut(void){
    return insolvencyHaircut;
}

double MacroFinancialFactors::getBankruptcyCosts(void){
    return bankruptcyCosts;
}

double MacroFinancialFactors::getAssetReservationPrice(void){
    return assetReservationPrice;
}

double MacroFinancialFactors::getLossGivenDefault(void){
    return lossGivenDefault;
}

double MacroFinancialFactors::getProbabilityOfDefault(void){
    return probabilityOfDefault;
}

double MacroFinancialFactors::getRunProbability(void){
    return liquidityShockProbability;
}