#ifndef BANK_HPP
#define BANK_HPP

#include <vector>
#include <string>

#include "Agent.hpp"

class Firm;
class Depositor;
class NonBankInvestor;

enum class BankFailureCause {none,
    liquidity,
    solvency};

class Bank : public Agent {
public:
    virtual int getBankId(void) const = 0;

    virtual void setUpBalanceSheet(double equityRatio,
                                   double liqAssetProportion) = 0;

    virtual void setInitialAssetSize(double size) = 0;
    virtual double getInitialAssetSize(void) const = 0;
    virtual double getInitialEquity(void) const = 0;
    virtual double getInitialDeposits(void) const = 0;
    virtual double getInitialLoans(void) const = 0;
    virtual double getInitialCash(void) const = 0;

    virtual void raiseCapital(double amount) = 0;

    virtual void grantLoanToFirm(Firm* borrower,
                                 double amount) = 0;

    virtual double getLeverage(void) const = 0;
    virtual void payOutWithdrawals(void) = 0;
    virtual void collectLoansFromFirms(void) = 0;
    virtual void accrueInterestToDepositors(void) = 0;

    virtual double getLiquidAssets (void)const = 0;
    virtual double getTotalAssets(void)const = 0;
    virtual double getCapital (void)const = 0;
    virtual double getLoansToFirms (void)const = 0;
    virtual double getLoansToBanks (void)const = 0;
    virtual double getOtherAssets (void)const = 0;

    virtual void lendTo(Bank* borrower, double amount) = 0;
    virtual void acceptLoan(Bank* lender, double amount) = 0;
    virtual void repayLoansFromBanks(void) = 0;
    virtual void collectLoan(Bank* borrower, double repaidAmount,
                             double dueAmount) = 0;

    virtual double getPendingWithdrawals(void) const = 0;
    virtual void sellRiskyAssetsToRepay(double pricePctFaceValue,
                                        double quantity) = 0;
    virtual void sellRiskyAssets(Bank* buyer,
                                 double pricePctFaceValue,
                                 double amount) = 0;
    virtual void buyLoans(Firm* borrower,
                          double quantity,
                          double pricePctFaceValue) = 0;
    virtual void buyAssetsFromOtherBanks(double pricePctFaceValue,
                                         double quantity) = 0;

    virtual void sellRiskyAssetsToInvestor(NonBankInvestor* investor,
                                           double pricePctFaceValue,
                                           double amount) = 0;

    virtual bool isInsolvent(void) const = 0;
    virtual bool isIlliquid(void) const = 0;

    virtual double getReturnOnEquity(void) = 0;

    virtual void payOutMaturingDeposits(void) = 0;

    virtual void payOutEarlyWithdrawals(void) = 0;

    virtual void requestWithdrawal(Depositor* depositor,
                                   double amount) = 0;

    virtual void receiveDeposit(Depositor* depositor,
                                double amount) = 0;

    virtual bool isBeingLiquidated() = 0;
    virtual bool hasFailed() = 0;
    virtual void declareInsolvent(void) = 0;
    virtual void declareIlliquid(void) = 0;
    virtual void finishLiquidation(NonBankInvestor* investor) = 0;
    virtual double getCapitalAtFailure(void) = 0;
    virtual double getLiquidityAtFailure(void) = 0;

    virtual BankFailureCause getFailureCause(void) = 0;

    //virtual ~Bank(void) = 0;
};

typedef std::vector<Bank*> BankPointerVector;


#endif //BANK_HPP
