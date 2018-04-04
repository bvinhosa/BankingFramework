#include "BankRegulator.hpp"

double BankRegulator::getCapitalRequirement(void){
    return capitalRequirement;
}

double BankRegulator::getLiquidityRequirement(void){
    return liquidityRequirement;
}

bool BankRegulator::compliesWithLiquidity(Bank* bank){
    return (bank->getLiquidAssets() >=
            (liquidityRequirement * bank->getTotalAssets()));
}

bool BankRegulator::compliesWithCapital(Bank* bank){
    return (bank->getCapital() >=
            (capitalRequirement * bank->getTotalAssets()));
}

double BankRegulator::getRiskWeightedAssets(Bank* bank){
    return (bank->getLoansToFirms() * RealSectorLoanRiskWeight +
            bank->getLoansToBanks() * BankLoanRiskWeight +
            bank->getOtherAssets() * OtherAssetsRiskWeight);
}