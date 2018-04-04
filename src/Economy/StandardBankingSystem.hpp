#ifndef STANDARDBANKINGSYSTEM_HPP
#define STANDARDBANKINGSYSTEM_HPP

#include <string>

#include "StrategicBankingSystem.hpp"
#include "BankRegulator.hpp"
#include "RiskyAssetMarket.hpp"

class StandardBankingSystem : public StrategicBankingSystem {
public:

    struct Parameters{
        int numBanks;
        int numDepositorsPerBank;
        int numFirmsPerBank;
    };

    StandardBankingSystem(Parameters params,
                          std::vector<double> sizes);

    virtual std::string toString(void);

    virtual BankPointerVector& getBanks(void);
    virtual DepositorPointerVector& getDepositors(void);
    virtual FirmPointerVector& getFirms(void);
    virtual RiskyAssetMarket& getAssetMarket(void);

    virtual int howManyBanks();
    virtual int howManyDepositors();
    virtual int howManyDeposits(void);

    virtual int howManyBanksFailedSolvency(void);
    virtual int howManyBanksFailedLiquidity(void);

    virtual void strategicReset(void);
    virtual void operationalReset(void);

    virtual StrategicAgentPointerVector& getStrategicAgents(void);
    virtual void prepareForIteration(void);

    virtual std::string showFirmFractions(void);
    virtual std::string showDepositorFractions(void);

private:

    virtual void createDeposits(Bank* bank, double banksDeposits);
    virtual void createLoans(Bank* bank, double banksLoans);

    Parameters systemParameters;

    std::vector<double> bankSizes;
    std::vector< std::vector<double> > depositorFractionMatrix;
    std::vector< std::vector<double> > firmFractionMatrix;
    int numDepositRelationships=0;

    BankPointerVector banks;
    DepositorPointerVector depositors;
    FirmPointerVector firms;

    BankRegulator centralBank;
    RiskyAssetMarket assetMarket;

    StrategicAgentPointerVector strategicAgents;
};

#endif //STANDARDBANKINGSYSTEM_HPP
