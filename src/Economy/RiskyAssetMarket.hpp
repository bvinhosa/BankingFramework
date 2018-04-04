#ifndef RISKYASSETMARKET_HPP
#define RISKYASSETMARKET_HPP

#include <vector>
#include <limits>
#include "../Agents/Bank.hpp"
#include "BankRegulator.hpp"

class RiskyAssetMarket{
public:

    explicit RiskyAssetMarket(BankRegulator& myRegulator);

    //For the time being, all methods are -> class is stateless

    //These first two are the only ones I'm totally sure wil remain public

    double negotiate(BankPointerVector &banks);

    double getRiskyAssetPrice(BankPointerVector& banks);

    double getLatestPrice(void) const;

//These might become private

    void sellToOutsideInvestors(BankPointerVector & banks,
                                NonBankInvestor* investor,
                                double reservationPrice);

    void transact(BankPointerVector buyers,
                  BankPointerVector sellers,
                  double pctSystemWideBought,
                  double pctSystemWideSold,
                  double marketPrice,
                  double marketVolume);

    void transactOrderBySize(BankPointerVector buyers,
                             BankPointerVector sellers,
                             double pctSystemWideBought,
                             double pctSystemWideSold,
                             double marketPrice,
                             double marketVolume);

    //bool sortByIncreasingSupply(Bank * bankA, Bank * bankB);
    //bool sortByDecreasingDemand(Bank * bankA, Bank * bankB);

private:

    BankRegulator& regulator;

    double latestPrice=std::numeric_limits<double>::quiet_NaN();

    void negotiateAmongBanks(BankPointerVector &banks);

    void sellToOutsideInvestors(BankPointerVector & banks,
                                double reservationPrice);

    double mustSell(BankPointerVector & banks, double price);
    double canBuy(BankPointerVector & banks,
                  double price);

    double getIndividualSurplus(Bank* bank);
    double getIndividualDeficit(Bank* bank);

    double getAggregateSurplus(BankPointerVector& banks);
    double getAggregateDeficit(BankPointerVector& banks);

//private:

    double getSolvencySurplus(Bank* bank);
    double getLiquiditySurplus(Bank* bank);

    double mustSell(Bank* bank, double price);
    double canBuy(Bank* bank, double price);


};

#endif //RISKYASSETMARKET_HPP
