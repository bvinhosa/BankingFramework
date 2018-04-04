#ifndef CONCRETEBANK_HPP
#define CONCRETEBANK_HPP

#include "Bank.hpp"
#include "BankBalanceSheet.hpp"

#include <string>
#include <set>
#include <map>

class Depositor;
class Firm;
class NonBankInvestor;



class ConcreteBank : public Bank{
public:
    //ConcreteBank(const std::string & givenName);
    ConcreteBank(const std::string & givenName, int agentId, int bankId);
    virtual std::string getName(void) const;

    virtual int getId(void) const;
    virtual int getBankId(void) const;

    virtual void setUpBalanceSheet(double equityRatio,
                                   double liqAssetProportion);

    virtual void setInitialAssetSize(double size);
    virtual double getInitialAssetSize(void) const;
    virtual double getInitialEquity(void) const;
    virtual double getInitialDeposits(void) const;
    virtual double getInitialLoans(void) const;
    virtual double getInitialCash(void) const;

    virtual void reset(void);

    virtual void raiseCapital(double amount);

    virtual void grantLoanToFirm(Firm* borrower,
                                 double amount);

    virtual double getLeverage(void) const;
    virtual void payOutWithdrawals(void);
    virtual void collectLoansFromFirms(void);
    virtual void accrueInterestToDepositors(void);

    virtual void requestWithdrawal(Depositor* depositor,
                                   double amount);

    virtual double getLoansToFirms(void) const;

    virtual void receiveDeposit(Depositor* depositor,
                                double amount);

    virtual double getDeposits(void) const;

    virtual double getLiquidAssets (void)const;
    virtual double getTotalAssets(void)const;
    virtual double getCapital (void)const;
    virtual double getLoansToBanks (void)const;
    virtual double getOtherAssets (void)const;

    virtual double getPendingWithdrawals(void) const;

    virtual void lendTo(Bank* borrower, double amount);
    virtual void acceptLoan(Bank* lender, double amount);
    virtual void repayLoansFromBanks(void);
    virtual void collectLoan(Bank* borrower, double repaidAmount,
                             double dueAmount);

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

    virtual double getReturnOnEquity(void);

    virtual void payOutMaturingDeposits(void);

    virtual void payOutEarlyWithdrawals(void);

    virtual void sellRiskyAssetsToInvestor(NonBankInvestor* investor,
                                           double pricePctFaceValue,
                                           double amount);

    virtual bool isBeingLiquidated(void);
    virtual bool hasFailed(void);
    virtual bool isInsolvent(void) const;
    virtual bool isIlliquid(void) const;
    virtual void declareInsolvent(void);
    virtual void declareIlliquid(void);
    virtual void finishLiquidation(NonBankInvestor* investor);

    virtual double getCapitalAtFailure(void);
    virtual double getLiquidityAtFailure(void);

    virtual BankFailureCause getFailureCause(void);

    virtual std::string toString() const;

    virtual std::string listDeposits(void) const;
    virtual std::string listPendingWithdrawals(void) const;


    //~ConcreteBank(){}
protected:

    virtual void collectLoan(Firm* firm);

    double initialAssetSize = 0.0;
    double initialEquity = 0.0;
    double initialDeposits = 0.0;
    double initialCash = 0.0;
    double initialLoans = 0.0;

    double capitalAtFailure = 0.0;
    double liquidityAtFailure = 0.0;

    BankFailureCause failureCause = BankFailureCause::none;

    std::string name;
    int agentId;
    int bankId;
    BankBalanceSheet balanceSheet;
    bool active=true;
    bool beingLiquidated=false;
    bool failedBank=false;

    double totalPendingWithdrawals = 0.0;
    double totalUnpaidLoans = 0.0;

    //BankBalanceSheet & getBalanceSheet();
    //std::set<Depositor*> depositors;
    std::set<Firm*> borrowers;
    std::map<Firm*,double> loans;
    std::map<Depositor*,double> deposits;
    std::map<Depositor*,double> pendingWithdrawals;
    std::map<Bank*, double> bankLoansDue;
    std::map<Bank*, double> bankLoansOwed;
};

#endif //CONCRETEBANK_HPP
