#ifndef NONBANKINVESTOR_HPP
#define NONBANKINVESTOR_HPP

#include <set>
#include <map>

class Firm;
class Bank;

class NonBankInvestor {
public:
    virtual void collectLoansFromFirms(void);
    virtual void buyLoan(Firm* borrower, double amount);
    virtual std::string toString(void);

protected:
    virtual void collectLoan(Firm* firm);
    std::set<Firm*> borrowers;
    std::map<Firm*,double> loans;
    double corporateLoanPortfolio = 0.0;
};

#endif //NONBANKINVESTOR_HPP
