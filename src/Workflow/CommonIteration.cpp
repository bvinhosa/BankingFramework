#include "CommonIteration.hpp"

#include <iostream>

#include "../Economy/BankingSystem.hpp"
#include "../Agents/NonBankInvestor.hpp"
#include "../Economy/RiskyAssetMarket.hpp"
#include "../Economy/MacroFinancialFactors.hpp"

void CommonIteration::iterate(BankingSystem& system){
    //std::cout << "CommonIteration::iterate" << std::endl;

    BankPointerVector banks = system.getBanks();
    DepositorPointerVector depositors = system.getDepositors();
    FirmPointerVector firms = system.getFirms();
    NonBankInvestor outsideInvestor;

    RiskyAssetMarket assetMarket = system.getAssetMarket();

    for (Depositor* depositor: depositors)
        depositor->assessWithdrawal();

    for (Bank* bank: banks)
        bank->payOutEarlyWithdrawals();

    double assetPricePct =
            MacroFinancialFactors::getAssetReservationPrice();

    assetMarket.sellToOutsideInvestors(banks,
                                       &outsideInvestor,
                                       assetPricePct);

    for (Bank* bank: banks)
        bank->payOutEarlyWithdrawals();

    for (Bank* bank : banks) {
        if(bank->isIlliquid())
            bank->declareIlliquid();
    }

    for (Bank* bank : banks){

        if(bank->isBeingLiquidated()){
            bank->finishLiquidation(&outsideInvestor);
            continue;
        }

        bank->collectLoansFromFirms();

        if(bank->isInsolvent()){
            bank->declareInsolvent();
            bank->finishLiquidation(&outsideInvestor);
            continue;
        }
        bank->accrueInterestToDepositors();
        bank->payOutMaturingDeposits();
    }

    outsideInvestor.collectLoansFromFirms();
}