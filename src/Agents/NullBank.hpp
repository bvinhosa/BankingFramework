#ifndef NULLBANK_HPP
#define NULLBANK_HPP

#include "Bank.hpp"

class NullBank : public Bank {

    virtual int getId(void) const;
    virtual std::string getName(void) const;
    virtual std::string toString(void) const;
    virtual void reset(void);

    virtual int getBankId(void) const;
    virtual void setUpBalanceSheet(double equityRatio,
                                   double liqAssetProportion);

    virtual void setInitialAssetSize(double size);
    virtual double getInitialAssetSize(void) const;
    virtual double getInitialEquity(void) const;
    virtual double getInitialDeposits(void) const;
    virtual double getInitialLoans(void) const;
    virtual double getInitialCash(void) const;

    virtual void raiseCapital(double amount);

    virtual void grantLoanToFirm(Firm* borrower,
                                 double amount);

    virtual double getLeverage(void) const;
    virtual void payOutWithdrawals(void);
    virtual void collectLoansFromFirms(void);
    virtual void accrueInterestToDepositors(void);

    virtual double getLiquidAssets (void)const;
    virtual double getTotalAssets(void)const;
    virtual double getCapital (void)const;
    virtual double getLoansToFirms (void)const;
    virtual double getLoansToBanks (void)const;
    virtual double getOtherAssets (void)const;

    virtual void lendTo(Bank* borrower, double amount);
    virtual void acceptLoan(Bank* lender, double amount);
    virtual void repayLoansFromBanks(void);
    virtual void collectLoan(Bank* borrower, double repaidAmount,
                             double dueAmount);

    virtual double getPendingWithdrawals(void) const;
    virtual void sellRiskyAssetsToRepay(double pricePctFaceValue,
                                        double quantity);
    virtual void sellRiskyAssets(Bank* buyer,
                                 double pricePctFaceValue,
                                 double amount);
    virtual void buyLoans(Firm* borrower,
                          double quantity,
                          double pricePctFaceValue);
    virtual void buyAssetsFromOtherBanks(double pricePctFaceValue,
                                         double quantity);

    virtual void sellRiskyAssetsToInvestor(NonBankInvestor* investor,
                                           double pricePctFaceValue,
                                           double amount);

    virtual bool isInsolvent(void) const;
    virtual bool isIlliquid(void) const;

    virtual double getReturnOnEquity(void);

    virtual void payOutMaturingDeposits(void);

    virtual void payOutEarlyWithdrawals(void);

    virtual void requestWithdrawal(Depositor* depositor,
                                   double amount);

    virtual void receiveDeposit(Depositor* depositor,
                                double amount);

    virtual bool isBeingLiquidated();
    virtual bool hasFailed();
    virtual void declareInsolvent(void);
    virtual void declareIlliquid(void);
    virtual void finishLiquidation(NonBankInvestor* investor);
    virtual double getCapitalAtFailure(void);
    virtual double getLiquidityAtFailure(void);

    virtual BankFailureCause getFailureCause(void);
};


#endif //NULLBANK_HPP