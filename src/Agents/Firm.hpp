#ifndef FIRM_HPP
#define FIRM_HPP

#include "Agent.hpp"

#include <vector>
#include <string>

class Bank;
class NonBankInvestor;

class Firm : public Agent {
public:
    virtual int getFirmId(void) const = 0;
    virtual void setDefault(bool whetherDefaults)=0;
    virtual void getLoan(Bank *lender, double amount)=0;
    virtual bool getWhetherDefaults(void) const = 0;
    virtual double repayLoan(double interestRate) = 0;
    virtual double repayLoan(Bank* lender, double interestRate) = 0;
    virtual double repayLoan(NonBankInvestor* investor,
                             double interestRate) = 0;
    virtual void transferLoan(Bank* seller,
                              NonBankInvestor* investor,
                              double amount) = 0;
    virtual void transferLoan(Bank* seller,
                              Bank* buyer,
                              double amount,
                              double pricePctFaceValue) = 0;
    virtual double getOutstandingDebt(void) const = 0;
};

typedef std::vector<Firm*> FirmPointerVector;

#endif //FIRM_HPP
