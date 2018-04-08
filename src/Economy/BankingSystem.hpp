#ifndef BANKINGSYSTEM_HPP
#define BANKINGSYSTEM_HPP

#include "../Agents/Firm.hpp"
#include "../Agents/Depositor.hpp"
#include "../Agents/Bank.hpp"

class RiskyAssetMarket;

class BankingSystem {
public:
    virtual std::string toString() = 0;
    virtual BankPointerVector& getBanks(void) = 0;
    virtual DepositorPointerVector& getDepositors(void) = 0;
    virtual FirmPointerVector& getFirms(void) = 0;
    virtual RiskyAssetMarket& getAssetMarket(void) = 0;
    virtual void operationalReset(void) = 0;

    virtual void reactivateBanks(void) = 0;
    virtual void deactivateBank(int bankId) = 0;
    virtual BankPointerVector& getActiveBanks(void) = 0;

    virtual int howManyBanks() = 0;
    virtual int howManyDepositors() = 0;
    virtual int howManyBanksFailedSolvency(void) = 0;
    virtual int howManyBanksFailedLiquidity(void) = 0;
    virtual int howManyDeposits(void) = 0; // number of distinct bank-depositor
                                           // pairs in the banking system
};

#endif //BANKINGSYSTEM_HPP
