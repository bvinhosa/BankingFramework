#ifndef BANKREGULATOR_HPP
#define BANKREGULATOR_HPP

#include "../Agents/Bank.hpp"

class BankRegulator {
public:
    double getCapitalRequirement(void);
    double getLiquidityRequirement(void);
    bool compliesWithLiquidity(Bank* bank);
    bool compliesWithCapital(Bank* bank);
    double getRiskWeightedAssets(Bank* bank);
private:
    const double capitalRequirement = 0.05;
    const double liquidityRequirement = 0.00;
    const double RealSectorLoanRiskWeight = 1.0;
    const double BankLoanRiskWeight = 0.2;
    const double OtherAssetsRiskWeight = 1.0;
};

#endif //BANKREGULATOR_HPP
