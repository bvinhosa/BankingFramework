#include "BankBalanceSheet.hpp"

#include <algorithm>

#include "../Util/BalanceSheetFormatter.hpp"

BankBalanceSheet::BankBalanceSheet(void){
    this->reset();
}

BankBalanceSheet::~BankBalanceSheet(void) {}


BankBalanceSheet BankBalanceSheet::clone(void) const{

    BankBalanceSheet clone;

    clone.liquidAssets = this->liquidAssets;
    clone.loansToFirms = this->loansToFirms;
    clone.loansToBanks = this->loansToBanks;
    clone.otherRiskyAssets = this->otherRiskyAssets;
    clone.otherAssets = this->otherAssets;

    clone.corporateLoanProvisions = this->corporateLoanProvisions;
    clone.bankLoanProvisions = this->corporateLoanProvisions;

//reset liabilities
    clone.deposits = this->deposits;
    clone.bankLoansPayable = this->bankLoansPayable ;
    clone.outsandingExpenses = this->outsandingExpenses ;

//reset income
    clone.interestFromLoansToFirms = this->interestFromLoansToFirms;
    clone.interestFromLoansToBanks = this->interestFromLoansToBanks;
    clone.otherIncome = this->otherIncome;

//reset expenses
    clone.interestToDepositors = this->interestToDepositors;
    clone.interestToBanks = this->interestToBanks;
    clone.delinquenciesFirms = this->delinquenciesFirms;
    clone.delinquenciesBanks = this->delinquenciesBanks;
    clone.otherExpenses = this->otherExpenses;

    return clone;
}

void BankBalanceSheet::reset(void){

//reset assets
    liquidAssets = 0.0;
    loansToFirms = 0.0;
    loansToBanks = 0.0;
    otherRiskyAssets = 0.0;
    otherAssets = 0.0;

//reset provisions
    corporateLoanProvisions = 0.0;
    bankLoanProvisions = 0.0;

//reset liabilities
    deposits = 0.0;
    bankLoansPayable = 0.0;
    outsandingExpenses = 0.0;

    paidUpCapital = 0.0;

//reset income
    interestFromLoansToFirms = 0.0;
    interestFromLoansToBanks = 0.0;
    otherIncome = 0.0;

//reset expenses
    interestToDepositors = 0.0;
    interestToBanks = 0.0;
    delinquenciesFirms = 0.0;
    delinquenciesBanks = 0.0;
    otherExpenses = 0.0;
}

double BankBalanceSheet::getTotalAssets(void) const {

    return ( getLiquidAssets() +
             getLoansToFirms() +
             getLoansToBanks() +
             getOtherRiskyAssets() +
             getOtherAssets() );

}

double BankBalanceSheet::getLiquidAssets(void) const {
    return liquidAssets;
}

double BankBalanceSheet::getLoansToFirms(void) const {
    return loansToFirms;
}

double BankBalanceSheet::getLoansToBanks(void) const {
    return loansToBanks;
}

double BankBalanceSheet::getOtherRiskyAssets(void) const {
    return otherRiskyAssets;
}

double BankBalanceSheet::getOtherAssets(void) const {
    return otherAssets;
}

double BankBalanceSheet::getLoanLossProvisions(void) const {
    return (corporateLoanProvisions + bankLoanProvisions);
}

double BankBalanceSheet::getTotalLiabilities(void) const {

    return ( getDeposits() +
             getBankLoansPayable() +
             getOutsandingExpenses() );

}

double BankBalanceSheet::getDeposits(void) const {
    return deposits;
}

double BankBalanceSheet::getBankLoansPayable(void) const {
    return bankLoansPayable;
}

double BankBalanceSheet::getOutsandingExpenses(void) const {
    return outsandingExpenses;
}

// getTotalEquity can be negative
// iff bank is currently balance-sheet insolvent
double BankBalanceSheet::getTotalEquity(void) const {
    return ( getTotalAssets() -
             getTotalLiabilities() );
}

double BankBalanceSheet::getIncome(void) const{
    return (interestFromLoansToFirms
            + interestFromLoansToBanks
            + otherIncome);
}

double BankBalanceSheet::getExpense(void) const{
    return (delinquenciesFirms +
            delinquenciesBanks +
            interestToDepositors +
            interestToBanks +
            otherExpenses);
}

double BankBalanceSheet::getProfit(void) const{
    return (getIncome() - getExpense());
}

void BankBalanceSheet::raiseCapital(double amount){

    // Capital is never really stored, only calculated.
    // Consequently, an increase in assets w/ no increase in liabilities
    // amounts to raising capítal on one side and increasing liquidity
    // on the asset side.

    liquidAssets += amount;

    // We are able to track paid up capital vs. current equity. The
    // difference should be equal to accumulated retained earnings net
    // of accumulated losses (can be positve or negative).

    paidUpCapital += amount;
}

void BankBalanceSheet::grantLoanToFirm(double amount) {
    liquidAssets -= amount;
    loansToFirms += amount;
}

void BankBalanceSheet::collectLoansFromFirms(double repaidAmount,
                                             double principalDue) {
    liquidAssets += repaidAmount;
    loansToFirms -= std::min(repaidAmount,principalDue);

    double delinquencyOrIncome = (repaidAmount - principalDue);

    if (delinquencyOrIncome > 0.0)
        interestFromLoansToFirms += delinquencyOrIncome;
    else if(delinquencyOrIncome < 0.0) {
        delinquenciesFirms -= delinquencyOrIncome;
        loansToFirms += delinquencyOrIncome;
        corporateLoanProvisions -= delinquencyOrIncome;
    }
}

/*
void BankBalanceSheet::collectLoansFromFirms2(double repaidAmount,
                                             double principalDue) {
    liquidAssets += repaidAmount;
    loansToFirms -= std::min(repaidAmount,principalDue);

    double delinquencyOrIncome = (repaidAmount - principalDue);

    if (delinquencyOrIncome > 0.0)
        interestFromLoansToFirms += delinquencyOrIncome;
    else if(delinquencyOrIncome < 0.0)
        delinquenciesFirms -= delinquencyOrIncome;
}
 */

void BankBalanceSheet::writeOffLoansToBanks(void){
    // right before the invocatio nof this function, loansToFirms will
    // ocntain the unpaid portion of loans. That also has to be writen off

    //delinquenciesFirms += loansToFirms;
    bankLoanProvisions += loansToBanks;
    loansToBanks = 0.0;
}

void BankBalanceSheet::writeOffLoansToFirms(void){
    // right before the invocation of this function, loansToFirms will
    // contain the unpaid portion of loans. That also has to be written off

    //delinquenciesFirms += loansToFirms;
    corporateLoanProvisions += loansToFirms;
    loansToFirms = 0.0;
}

void BankBalanceSheet::purchaseOtherRiskyAsset(double amount) {
    liquidAssets -= amount;
    otherRiskyAssets += amount;
}

void BankBalanceSheet::matureOtherRiskyAsset(double repaidAmount,
                                             double principalDue) {
    liquidAssets += repaidAmount;
    otherRiskyAssets -= std::min(repaidAmount,principalDue);

    double delinquencyOrIncome = (repaidAmount - principalDue);

    if (delinquencyOrIncome > 0.0)
        otherIncome += delinquencyOrIncome;
    else if(delinquencyOrIncome < 0.0)
        otherExpenses -= delinquencyOrIncome;
}

void BankBalanceSheet::grantLoanToBank(double amount) {
    liquidAssets -= amount;
    loansToBanks += amount;
}

void BankBalanceSheet::collectLoanFromBank (double repaidAmount,
                                            double principalDue) {
    liquidAssets += repaidAmount;
    loansToBanks -= std::min(repaidAmount,principalDue);

    double delinquencyOrIncome = (repaidAmount - principalDue);

    if (delinquencyOrIncome > 0.0)
        interestFromLoansToBanks += delinquencyOrIncome;
    else if(delinquencyOrIncome < 0.0) {
        delinquenciesFirms -= delinquencyOrIncome;
        loansToBanks += delinquencyOrIncome;
        bankLoanProvisions -= delinquencyOrIncome;
    }
}

void BankBalanceSheet::receiveDeposit(double amount) {
    deposits += amount;
    liquidAssets += amount;
}

void BankBalanceSheet::repayDeposit(double amount) {
    deposits -= amount;
    liquidAssets -= amount;
}

void BankBalanceSheet::repayDeposit(double principal,
                                    double interest){
    deposits -= principal;
    liquidAssets -= (principal+interest);
    interestToDepositors+=interest;
}

void BankBalanceSheet::receiveLoanFromBank(double amount) {
    bankLoansPayable += amount;
    liquidAssets += amount;
}

void BankBalanceSheet::repayLoanToBank(double repaidAmount,
                                       double dueAmount) {
    bankLoansPayable -= std::min(repaidAmount,dueAmount);
    interestToBanks += std::max(0.0, (repaidAmount-dueAmount));
    liquidAssets -= repaidAmount;
}

void BankBalanceSheet::incurOutstandingExpense(double amount) {
    outsandingExpenses += amount;
    otherExpenses += amount;
}

void BankBalanceSheet::repayOutstandingExpense(double amount) {
    outsandingExpenses -= amount;
    liquidAssets -= amount;
}

void BankBalanceSheet::buyLoan(double amount){
    liquidAssets -= amount;
    loansToFirms += amount;
}

void BankBalanceSheet::sellLoan(double loansSold, double pricePaid) {
    liquidAssets += pricePaid;
    loansToFirms -= loansSold;

    double valuationDelta = (pricePaid - loansSold);

    if (valuationDelta > 0.0)
        otherIncome += valuationDelta;
    else if(valuationDelta < 0.0)
        otherExpenses -= valuationDelta;
}

std::string BankBalanceSheet::toString(void) const {
    return BalanceSheetFormatter::format(*this);
}