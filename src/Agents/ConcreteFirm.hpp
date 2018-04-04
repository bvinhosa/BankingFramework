#ifndef CONCRETEFIRM_HPP
#define CONCRETEFIRM_HPP

#include "Firm.hpp"

#include <string>
#include <map>


class ConcreteFirm : public Firm {
public:
    ConcreteFirm(const std::string & givenName, int agentId, int firmId);
    //ConcreteFirm(const std::string & givenName);
    virtual int getId(void) const;
    virtual std::string getName(void) const;
    virtual std::string toString(void) const;
    virtual void reset(void);

    virtual int getFirmId(void) const;
    virtual bool getWhetherDefaults(void) const;
    virtual void setDefault(bool whetherDefaults);
    virtual void getLoan(Bank *lender, double amount);
    virtual double repayLoan(double interestRate);
    virtual double repayLoan(Bank* lender, double interestRate);
    virtual double repayLoan(NonBankInvestor* investor,
                             double interestRate);
    virtual double getOutstandingDebt(void) const;
    virtual void transferLoan(Bank* seller,
                              NonBankInvestor* investor,
                              double amount);
    virtual void transferLoan(Bank* seller,
                              Bank* buyer,
                              double amount,
                              double pricePctFaceValue);


    //virtual bool isDelinquent(void) const;
private:
    std::string name;
    int agentId;
    int firmId;
    bool loanMatured = false;
    bool willDefault = false;
    bool isDelinquent = false;
    double amountBorrowed = 0.0;
    double amountRepaid = 0.0;
    double amountOutstanding = 0.0;

    std::map<Bank*, double> loansFromBanks;
    double loansFromNonBanks = 0.0;

};


#endif //CONCRETEFIRM_HPP
