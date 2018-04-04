#include "NonBankInvestor.hpp"


#include <sstream>

#include "Firm.hpp"
#include "../Economy/MacroFinancialFactors.hpp"

void NonBankInvestor::collectLoansFromFirms(void){
    for(Firm* borrower: borrowers){
        collectLoan(borrower);
    }
}

void NonBankInvestor::collectLoan(Firm* borrower){

    double interestRate =
            MacroFinancialFactors::getInterestRateLoans();
    borrower->repayLoan(this,interestRate);
}

void NonBankInvestor::buyLoan(Firm* borrower, double amount){
    borrowers.insert(borrower);
    loans[borrower] += amount;
    corporateLoanPortfolio += amount;
}

std::string NonBankInvestor::toString(void){
    std::stringstream descriptor;

    descriptor << "Corporate portfolio: "
               << corporateLoanPortfolio << std::endl;

    return descriptor.str();
}
