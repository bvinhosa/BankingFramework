#include "NullBank.hpp"
#include <limits>

void NullBank::setUpBalanceSheet(double equityRatio,
                                 double liqAssetProportion){}

int NullBank::getId(void) const {
    return -1;
}

int NullBank::getBankId(void) const {
    return -1;
}

void NullBank::reset(void) {
}

void NullBank::setInitialAssetSize(double size){}

double NullBank::getInitialAssetSize(void) const{
    return 0.0;
}
double NullBank::getInitialEquity(void) const{
    return 0.0;
}
double NullBank::getInitialDeposits(void) const{
    return 0.0;
}
double NullBank::getInitialLoans(void) const{
    return 0.0;
}
double NullBank::getInitialCash(void) const{
    return 0.0;
}

void NullBank::raiseCapital(double amount){}

void NullBank::grantLoanToFirm(Firm* borrower,
                               double amount){}

double NullBank::getLeverage(void) const{
    return std::numeric_limits<double>::infinity();
}

void NullBank::payOutWithdrawals(void){}
void NullBank::collectLoansFromFirms(void){}
void NullBank::accrueInterestToDepositors(void){}

double NullBank::getLiquidAssets (void)const{
    return 0.0;
}
double NullBank::getTotalAssets(void)const{
    return 0.0;
}
double NullBank::getCapital (void)const{
    return 0.0;
}
double NullBank::getLoansToFirms (void)const{
    return 0.0;
}
double NullBank::getLoansToBanks (void)const{
    return 0.0;
}
double NullBank::getOtherAssets (void)const{
    return 0.0;
}

void NullBank::lendTo(Bank* borrower, double amount){}
void NullBank::acceptLoan(Bank* lender, double amount){}
void NullBank::repayLoansFromBanks(void){}
void NullBank::collectLoan(Bank* borrower, double repaidAmount,
                           double dueAmount){}

double NullBank::getPendingWithdrawals(void) const{
    return 0.0;
}
void NullBank::sellRiskyAssetsToRepay(double pricePctFaceValue,
                                      double quantity){}
void NullBank::sellRiskyAssets(Bank* buyer,
                               double pricePctFaceValue,
                               double amount){}
void NullBank::buyLoans(Firm* borrower,
                        double quantity,
                        double pricePctFaceValue){}
void NullBank::buyAssetsFromOtherBanks(double pricePctFaceValue,
                                       double quantity){}

void NullBank::sellRiskyAssetsToInvestor(NonBankInvestor* investor,
                                         double pricePctFaceValue,
                                         double amount){}

bool NullBank::isInsolvent(void) const{
    return false;
}

bool NullBank::isIlliquid(void) const{
    return false;
}

double NullBank::getReturnOnEquity(void){
    return 0.0;
}

void NullBank::payOutMaturingDeposits(void){}

void NullBank::payOutEarlyWithdrawals(void){}

void NullBank::requestWithdrawal(Depositor* depositor,
                                 double amount){}

void NullBank::receiveDeposit(Depositor* depositor,
                              double amount){}

bool NullBank::isBeingLiquidated(){
    return false;
}
void NullBank::declareInsolvent(void){}
void NullBank::declareIlliquid(void){}
void NullBank::finishLiquidation(NonBankInvestor* investor){}

std::string NullBank::getName() const{
    return std::string("Null Bank");
}

std::string NullBank::toString() const{
    return std::string("Nothing to see here");
}

bool NullBank::hasFailed() {
    return false;
}

double NullBank::getCapitalAtFailure(void) {
    return std::numeric_limits<double>::quiet_NaN();
}

double NullBank::getLiquidityAtFailure(void) {
    return std::numeric_limits<double>::quiet_NaN();
}

BankFailureCause NullBank::getFailureCause(void) {
    return BankFailureCause::none;
}
