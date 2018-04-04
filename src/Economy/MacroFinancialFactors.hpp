#ifndef MACROFINANCIALFACTORS_HPP
#define MACROFINANCIALFACTORS_HPP

class MacroFinancialFactors {
public:
    static double getInterestRateDeposits(void);
    static double getInterestRateLoans(void);
    static double getInterestRateBanks(void);
    static double getInsolvencyHaircut(void);
    static double getBankruptcyCosts(void);
    static double getAssetReservationPrice(void);
    static double getLossGivenDefault(void);
    static double getProbabilityOfDefault(void);
    static double getRunProbability(void);
private:
    static double interestRateDeposits;
    static double interestRateLoans;
    static double interestRateBanks;
    static double insolvencyHaircut;
    static double bankruptcyCosts;
    static double assetReservationPrice;
    static double probabilityOfDefault;
    static double lossGivenDefault;
    static double liquidityShockProbability;
};

#endif //MACROFINANCIALFACTORS_HPP
