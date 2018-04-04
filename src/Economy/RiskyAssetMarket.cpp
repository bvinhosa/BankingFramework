#include "RiskyAssetMarket.hpp"

#include <cmath>
#include <iostream>
#include <algorithm>

#include "MacroFinancialFactors.hpp"

RiskyAssetMarket::RiskyAssetMarket(BankRegulator& myRegulator)
        : regulator(myRegulator){}

double RiskyAssetMarket::getSolvencySurplus(Bank* bank){

    double currentLoans = bank->getLoansToFirms();

    double maxLoansSolvReq = (bank->getCapital()
                              / (regulator.getCapitalRequirement()));

    return (std::max(0.0, (maxLoansSolvReq - currentLoans)));
}

double RiskyAssetMarket::getLiquiditySurplus(Bank* bank){

    double requiredLiquidAssets = regulator.getLiquidityRequirement() *
                                  bank->getTotalAssets();

    //ALTERNATIVE POLICY
    //double requiredLiquidAssets = liquidityRequirement *
    //bank->getDeposits();

    return (std::max (0.0, (bank->getLiquidAssets() - requiredLiquidAssets)));
}


double RiskyAssetMarket::getIndividualSurplus(Bank* bank){
    return std::min (getSolvencySurplus(bank),
                     getLiquiditySurplus(bank));
}

double RiskyAssetMarket::canBuy(Bank* bank, double price){

    double liquidityRequirement = regulator.getLiquidityRequirement();

    //at least for asset requirement
    double factor = (1.0 - price) * liquidityRequirement + price;

    //for deposit-based requirement
    //double factor = price;

    double liqDeficit = getLiquiditySurplus(bank);

    double limitDueToLiquidity = liqDeficit / factor;

    double limitDueToSolvency = getSolvencySurplus(bank);

    return std::min(limitDueToLiquidity,limitDueToSolvency);
}

double RiskyAssetMarket::canBuy(BankPointerVector & banks, double price){

    double howMuch = 0.0;

    for (Bank* bank: banks)
        howMuch += canBuy(bank, price);

    return howMuch;
}


double RiskyAssetMarket::getIndividualDeficit(Bank* bank){

    //When addressing liquidity problems the liquidity needs are those
    // necessary to settle any pending withdrawals in addition to returning
    // to compliance with prudential requirements

    double requiredLiquidAssets =   regulator.getLiquidityRequirement() *
                                    bank->getTotalAssets();

    //ALTERNATIVE POLICY
    //double requiredLiquidAssets = liquidityRequirement *
    //bank->getDeposits();

    double netLiquidAssets =    (bank->getLiquidAssets() -
                                 bank->getPendingWithdrawals());
    double liqDeficit = std::max (0.0,
                                  (requiredLiquidAssets - netLiquidAssets));

    return liqDeficit;
}

double RiskyAssetMarket::mustSell(Bank* bank, double price){

    //at least for asset requirement
    double factor = (1.0 - price) *
                    regulator.getLiquidityRequirement() + price;

    //for deposit-based requirement
    //double factor = price;

    double liqDeficit = getIndividualDeficit(bank);

    return liqDeficit / factor;
}

double RiskyAssetMarket::mustSell(BankPointerVector & banks, double price){
    double howMuch = 0.0;

    for (Bank* bank: banks)
        howMuch += mustSell(bank, price);

    return howMuch;
}

double RiskyAssetMarket::getAggregateSurplus(BankPointerVector& banks){

    double aggregateSurplus = 0.0;

    for (Bank* bank: banks)
        aggregateSurplus += getIndividualSurplus(bank);

    return aggregateSurplus;
}

double RiskyAssetMarket::getAggregateDeficit(BankPointerVector& banks){

    double aggregateDeficit = 0.0;

    for (Bank* bank: banks)
        aggregateDeficit += getIndividualDeficit(bank);

    return aggregateDeficit;
}

double RiskyAssetMarket::getRiskyAssetPrice(BankPointerVector& banks){

    double deficit = getAggregateDeficit(banks);

    //if there is no deficit, then price = 1
    //(just a convention, inconsequential because no transactions take place)

    if (deficit == 0.0){
        return 1.0;
    }
    else {
        double surplus = getAggregateSurplus(banks);
        double capacity =  surplus / deficit;
        return (capacity/(capacity+1));
        //return pow((capacity/(capacity+1)),2.0);
    }

}

void RiskyAssetMarket::sellToOutsideInvestors(BankPointerVector & banks,
                                              double reservationPrice){

    for (Bank* bank: banks){
        if(getIndividualDeficit(bank) > 0.0)
            bank->sellRiskyAssetsToRepay(reservationPrice,
                                         mustSell(bank,
                                                  reservationPrice));
    }
}

void RiskyAssetMarket::sellToOutsideInvestors(BankPointerVector & banks,
                                              NonBankInvestor* investor,
                                              double reservationPrice){

    for (Bank* bank: banks){
        if(getIndividualDeficit(bank) > 0.0){
            /*
            std::cout << "Reservation price: " << reservationPrice << std::endl;
            std::cout << "Individual deficit: " << getIndividualDeficit(bank) << std::endl;
            std::cout << "Must sell: " << mustSell(bank, reservationPrice) << std::endl;
            */
            bank->sellRiskyAssetsToInvestor(investor,
                                            reservationPrice,
                                            mustSell(bank,
                                                     reservationPrice));
        }
    }
}

void RiskyAssetMarket::negotiateAmongBanks(BankPointerVector &banks){

    double marketPrice, marketVolume;

    BankPointerVector buyers, sellers;

    for	(Bank * bank : banks){
        if(getIndividualDeficit(bank) > 0.0)
            sellers.push_back(bank);
        else if(getIndividualSurplus(bank) > 0.0)
            buyers.push_back(bank);
    }

    marketPrice = getRiskyAssetPrice(banks);

    double supplyAtMarketPrice = mustSell(sellers,
                                          marketPrice);

    double demandAtMarketPrice = canBuy(buyers, marketPrice);

    if(supplyAtMarketPrice <= demandAtMarketPrice){

        marketVolume = supplyAtMarketPrice; //all sellers sell
        // some buyers buy
    }
    else {

        marketVolume = demandAtMarketPrice; //all buyers buy,
        // some sellers sell
    }

    double pctSystemWideBought = marketVolume / demandAtMarketPrice;
    double pctSystemWideSold = marketVolume / supplyAtMarketPrice;

    /*
    transact(buyers,
             sellers,
             pctSystemWideBought,
             pctSystemWideSold,
             marketPrice,
             marketVolume);
    */

    for (Bank * bank: sellers){
        bank->sellRiskyAssetsToRepay( marketPrice,
                                      pctSystemWideSold *
                                      mustSell(bank,
                                               marketPrice));
    }

    for (Bank * bank: buyers){
        bank->buyAssetsFromOtherBanks( marketPrice,
                                       pctSystemWideBought *
                                       canBuy(bank,
                                              marketPrice));

    }
}

double RiskyAssetMarket::negotiate(BankPointerVector& banks) {
    double marketPrice, reservationPrice;

    marketPrice = getRiskyAssetPrice(banks);
    reservationPrice = MacroFinancialFactors::getAssetReservationPrice();

    if (marketPrice > reservationPrice){
        negotiateAmongBanks(banks);
        latestPrice = marketPrice;
    }
    else{
        sellToOutsideInvestors(banks, reservationPrice);
        latestPrice = reservationPrice;
    }

    return latestPrice;

}

double RiskyAssetMarket::getLatestPrice(void) const{
    return latestPrice;
}

/*
bool sortByDecreasingDemand(Bank * bankA, Bank * bankB) {
    const double dummyPrice = 0.9999; //price changes absolute but not relative value

    return (bankA->getTotalAssets() > bankB->getTotalAssets());

    //return (canBuy(bankA,dummyPrice) < canBuy(bankB,dummyPrice));
}

bool sortByIncreasingSupply(Bank * bankA, Bank * bankB) {
    const double dummyPrice = 0.9999; //price changes absolute but not relative value
    //return (mustSell(bankA,dummyPrice) > mustSell(bankB,dummyPrice));

    return (bankA->getTotalAssets() > bankB->getTotalAssets());
}
*/

void RiskyAssetMarket::transact(BankPointerVector buyers,
                                BankPointerVector sellers,
                                double pctSystemWideBought,
                                double pctSystemWideSold,
                                double marketPrice,
                                double marketVolume){

    double transferredVolume = 0.0;

    std::random_shuffle(buyers.begin(), buyers.end());
    std::random_shuffle(sellers.begin(), sellers.end());

    std::vector<Bank*>::iterator iteratorBuyers = buyers.begin();
    std::vector<Bank*>::iterator iteratorSellers = sellers.begin();

    std::vector<Bank*>::iterator endIteratorBuyers = buyers.end();
    std::vector<Bank*>::iterator endIteratorSellers = sellers.begin();

    while((iteratorBuyers != endIteratorBuyers) &&
          (iteratorSellers != endIteratorSellers)){

        Bank * currentBuyer = *iteratorBuyers;
        Bank * currentSeller = *iteratorSellers;

        double howMuchToBuy = pctSystemWideBought *
                              canBuy(currentBuyer, marketPrice);
        double howMuchToSell = pctSystemWideSold *
                               mustSell(currentSeller, marketPrice);

        double transactionSize = std::min(howMuchToBuy,howMuchToSell);

        howMuchToBuy -= transactionSize;
        howMuchToSell -= transactionSize;

        currentSeller->sellRiskyAssets(currentBuyer,
                                       marketPrice,
                                       transactionSize);

        const double roundingError = 0.0000001;

        if (howMuchToBuy <= (0.0 + roundingError)) {
            iteratorBuyers++;
        }

        if (howMuchToSell <= (0.0 + roundingError)) {
            iteratorSellers++;
        }

    }
}


bool sortByDecreasingDemand(std::pair<Bank*,double> pair1, std::pair<Bank*,double> pair2) {
    Bank* bank1 = pair1.first;
    Bank* bank2 = pair2.first;

    double surplus1 = pair1.second;
    double surplus2 = pair2.second;

    return (surplus1 > surplus2);
}

bool sortByIncreasingSupply(std::pair<Bank*,double> pair1, std::pair<Bank*,double> pair2) {
    Bank* bank1 = pair1.first;
    Bank* bank2 = pair2.first;

    double deficit1 = pair1.second;
    double deficit2 = pair2.second;

    return (deficit1 < deficit2);
}


void RiskyAssetMarket::transactOrderBySize(BankPointerVector buyers,
                                           BankPointerVector sellers,
                                           double pctSystemWideBought,
                                           double pctSystemWideSold,
                                           double marketPrice,
                                           double marketVolume){

    double transferredVolume = 0.0;

    std::vector< std::pair <Bank*,double> > sellerDeficits, buyerSurpluses;

    for(Bank* bank: buyers)
        buyerSurpluses.push_back(std::make_pair(bank,canBuy(bank,marketPrice)));

    for(Bank* bank: sellers)
        sellerDeficits.push_back(std::make_pair(bank,mustSell(bank,marketPrice)));

    std::sort(buyerSurpluses.begin(), buyerSurpluses.end(), sortByDecreasingDemand);
    std::sort(sellerDeficits.begin(), sellerDeficits.end(), sortByIncreasingSupply);

    //std::random_shuffle(buyers.begin(), buyers.end());
    //std::random_shuffle(sellers.begin(), sellers.end());

    std::vector< std::pair <Bank*,double> >::iterator iteratorBuyers = buyerSurpluses.begin();
    std::vector< std::pair <Bank*,double> >::iterator iteratorSellers = sellerDeficits.begin();

    std::vector< std::pair <Bank*,double> >::iterator endIteratorBuyers = buyerSurpluses.end();
    std::vector< std::pair <Bank*,double> >::iterator endIteratorSellers = sellerDeficits.begin();

    while((iteratorBuyers != endIteratorBuyers) &&
          (iteratorSellers != endIteratorSellers)){

        Bank * currentBuyer = (*iteratorBuyers).first;
        Bank * currentSeller = (*iteratorSellers).first;

        double howMuchToBuy = pctSystemWideBought *
                              canBuy(currentBuyer, marketPrice);
        double howMuchToSell = pctSystemWideSold *
                               mustSell(currentSeller, marketPrice);

        double transactionSize = std::min(howMuchToBuy,howMuchToSell);

        howMuchToBuy -= transactionSize;
        howMuchToSell -= transactionSize;

        currentSeller->sellRiskyAssets(currentBuyer,
                                       marketPrice,
                                       transactionSize);

        const double roundingError = 0.0000001;

        if (howMuchToBuy <= (0.0 + roundingError)) {
            iteratorBuyers++;
        }

        if (howMuchToSell <= (0.0 + roundingError)) {
            iteratorSellers++;
        }
    }
}