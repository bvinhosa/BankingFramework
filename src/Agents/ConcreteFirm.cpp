#include <iostream>
#include "ConcreteFirm.hpp"


#include "Bank.hpp"
#include "NonBankInvestor.hpp"
#include "../Economy/MacroFinancialFactors.hpp"

ConcreteFirm::ConcreteFirm(const std::string & givenName, int agentId, int firmId) {
    reset();
    name.assign(givenName);
    this->agentId = agentId;
    this->firmId = firmId;
}

/*
ConcreteFirm::ConcreteFirm(const std::string & givenName) {
    reset();
    name.assign(givenName);
}
*/

int ConcreteFirm::getId(void) const{
    return agentId;
}

std::string ConcreteFirm::getName(void) const{
    return name;
}

std::string ConcreteFirm::toString(void) const{

    if(willDefault)
        return std::string("Delinquent");
    else
        return std::string("Non-Delinquent");
}

void ConcreteFirm::reset(void){
    loanMatured = false;
    willDefault = false;
    isDelinquent = false;
    amountBorrowed = 0.0;
    amountRepaid = 0.0;
    amountOutstanding = 0.0;
    loansFromBanks.clear();
    loansFromNonBanks = 0.0;
}

int ConcreteFirm::getFirmId(void) const{
    return firmId;
}

bool ConcreteFirm::getWhetherDefaults(void) const{
    return willDefault;
}

void ConcreteFirm::setDefault(bool whetherDefaults){
    willDefault = whetherDefaults;
}

void ConcreteFirm::getLoan(Bank *lender, double amount){
    loansFromBanks[lender] += amount;
    amountBorrowed += amount;
    amountOutstanding += amount;
}

void ConcreteFirm::transferLoan(Bank* seller,
                                Bank* buyer,
                                double amount,
                                double pricePctFaceValue){
    loansFromBanks[seller] -= amount;
    loansFromBanks[buyer] += amount;
    buyer->buyLoans(this, amount, pricePctFaceValue);
}

void ConcreteFirm::transferLoan(Bank* seller,
                                NonBankInvestor* investor,
                                double amount) {
    loansFromBanks[seller] -= amount;
    loansFromNonBanks += amount;
    investor->buyLoan(this,amount);
}

double ConcreteFirm::repayLoan(double interestRate){

    if(loanMatured)
        return amountRepaid;

    double repaidPrincipal;

    if(willDefault){
        double loss = amountBorrowed *
                      MacroFinancialFactors::getLossGivenDefault();
        repaidPrincipal = amountBorrowed - loss;
        amountRepaid = repaidPrincipal;
        isDelinquent = true;
    }
    else {
        repaidPrincipal = amountBorrowed;
        amountRepaid = repaidPrincipal * (1.0 + interestRate);
    }

    loanMatured = true;
    amountOutstanding -= repaidPrincipal;
    return amountRepaid;

}

double ConcreteFirm::repayLoan(Bank* lender, double interestRate){
    return (loansFromBanks[lender] / amountBorrowed) *
           repayLoan(interestRate);
}

double ConcreteFirm::repayLoan(NonBankInvestor* investor,
                               double interestRate) {
    return (loansFromNonBanks / amountBorrowed) *
           repayLoan(interestRate);
}

double ConcreteFirm::getOutstandingDebt(void) const{
    return amountOutstanding;
}

// bool ConcreteFirm::isDelinquent(void) const{
// return isDelinquent;
// }

