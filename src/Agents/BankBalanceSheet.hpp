#ifndef BANKBALANCESHEET_HPP
#define BANKBALANCESHEET_HPP

#include <string>

class BankBalanceSheet {

public:

    BankBalanceSheet(void);
    virtual ~BankBalanceSheet(void);
    virtual void reset(void);
    virtual BankBalanceSheet clone(void) const;

    virtual double getTotalAssets(void) const;
    virtual double getLiquidAssets(void) const;
    virtual double getLoansToFirms(void) const;
    virtual double getLoansToBanks(void) const;
    virtual double getOtherRiskyAssets(void) const;
    virtual double getOtherAssets(void) const;

    virtual double getLoanLossProvisions(void) const;

    virtual double getTotalLiabilities(void) const;
    virtual double getDeposits(void) const;
    virtual double getBankLoansPayable(void) const;
    virtual double getOutsandingExpenses(void) const;
    virtual double getTotalEquity(void) const;

    virtual double getIncome(void) const;
    virtual double getExpense(void) const;
    virtual double getProfit(void) const;

    virtual void raiseCapital(double amount);
    virtual void grantLoanToFirm(double amount);
    virtual void collectLoansFromFirms(double repaidAmount,
                                       double dueAmount);
    virtual void writeOffLoansToFirms(void);
    virtual void writeOffLoansToBanks(void);
    virtual void grantLoanToBank(double amount);
    virtual void collectLoanFromBank (double repaidAmount,
                                      double dueAmount);

    virtual void purchaseOtherRiskyAsset(double amount);
    virtual void matureOtherRiskyAsset(double repaidAmount,
                                       double dueAmount);
    virtual void receiveDeposit(double amount);
    virtual void repayDeposit(double amount);
    virtual void repayDeposit(double principal, double interest);
    virtual void receiveLoanFromBank(double amount);
    virtual void repayLoanToBank(double repaidAmount,
                                 double dueAmount);
    virtual void incurOutstandingExpense(double amount);
    virtual void repayOutstandingExpense(double amount);

    virtual void buyLoan(double amount);
    virtual void sellLoan(double loansSold, double pricePaid);

    virtual std::string toString(void) const;

protected:

    //assets

    double liquidAssets;
    double loansToFirms;
    double loansToBanks;
    double otherRiskyAssets;
    double otherAssets;

    // "negative assets" - asset-side provisions

    double corporateLoanProvisions;
    double bankLoanProvisions;

    //liabilities

    double deposits;
    double bankLoansPayable;
    double outsandingExpenses;

    double paidUpCapital;

    //income

    double interestFromLoansToFirms;
    double interestFromLoansToBanks;
    double otherIncome;

    //expense

    double interestToDepositors;
    double interestToBanks;
    double delinquenciesFirms;
    double delinquenciesBanks;
    double otherExpenses;
    // Notice ownership equity is not stored, it is always calculated
};

#endif //BANKBALANCESHEET_HPP
