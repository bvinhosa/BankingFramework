#include "ConcreteBank.hpp"
#include "Depositor.hpp"
#include "Firm.hpp"
#include "../Economy/MacroFinancialFactors.hpp"

#include <algorithm>
#include <sstream>
#include <iostream>

ConcreteBank::ConcreteBank(const std::string & givenName, int agentId, int bankId) {
    reset();
    name.assign(givenName);
    this->agentId = agentId;
    this->bankId = bankId;
}

int ConcreteBank::getId(void) const{
    return agentId;
}

int ConcreteBank::getBankId(void) const{
    return bankId;
}

void ConcreteBank::reset(void){
    balanceSheet.reset();
    //initialAssetSize = 0.0;
    initialEquity = 0.0;
    initialDeposits = 0.0;
    initialCash = 0.0;
    initialLoans = 0.0;

    capitalAtFailure = std::numeric_limits<double>::quiet_NaN();
    liquidityAtFailure = std::numeric_limits<double>::quiet_NaN();
    failureCause = BankFailureCause::none;

    active=true;
    beingLiquidated=false;
    failedBank=false;

    totalPendingWithdrawals = 0.0;
    totalUnpaidLoans = 0.0;

    borrowers.clear();
    loans.clear();
    deposits.clear();
    pendingWithdrawals.clear();
    bankLoansDue.clear();
    bankLoansOwed.clear();


}

/*
ConcreteBank::ConcreteBank(const std::string & givenName) {
    reset();
    name.assign(givenName);
}*/

void ConcreteBank::setInitialAssetSize(double size){
    initialAssetSize = size;
}

std::string ConcreteBank::getName(void) const {
    return name;
}

double ConcreteBank::getInitialAssetSize(void) const{
    return initialAssetSize;
}

void ConcreteBank::setUpBalanceSheet(double equityRatio,
                                     double liqAssetProportion){

    initialEquity = initialAssetSize * equityRatio;
    initialDeposits = initialAssetSize - initialEquity;
    initialCash = initialAssetSize * liqAssetProportion;
    initialLoans = initialAssetSize - initialCash;
}

double ConcreteBank::getInitialEquity(void) const{
    return initialEquity;
}

double ConcreteBank::getInitialDeposits(void) const{
    return initialDeposits;
}

double ConcreteBank::getInitialLoans(void) const{
    return initialLoans;
}

double ConcreteBank::getInitialCash(void) const{
    return initialCash;
}

double ConcreteBank::getLiquidAssets(void) const{
    return balanceSheet.getLiquidAssets();
}

void ConcreteBank::lendTo(Bank* borrower, double amount){
    bankLoansDue[borrower] += amount;
    borrower->acceptLoan(this, amount);
    balanceSheet.grantLoanToBank(amount);
}

void ConcreteBank::acceptLoan(Bank* lender, double amount){
    bankLoansOwed[lender] += amount;
    balanceSheet.receiveLoanFromBank(amount);
}

void ConcreteBank::repayLoansFromBanks(void) {

    const double roundingError = 0.000001;

    double bankLoansPayable = balanceSheet.getBankLoansPayable();

    if (bankLoansPayable <= 0.0)
        return;

    double interestOwed = bankLoansPayable *
                          MacroFinancialFactors::getInterestRateBanks();

    double pctToPayOut = std::min(getLiquidAssets(),
                                  (bankLoansPayable + interestOwed)) /
                         bankLoansPayable;

    for(auto & currentLoan: bankLoansOwed ){
        Bank * currentLender = currentLoan.first;
        double loanValue = currentLoan.second;
        currentLender->collectLoan(this,(pctToPayOut * loanValue),
                                   loanValue);
        double principalRepaid = std::min((pctToPayOut * loanValue),
                                          loanValue);
        bankLoansOwed[currentLender] -= principalRepaid;
    }

    if (pctToPayOut >= (1.0 - roundingError)) {
        bankLoansOwed.clear();
    }

    balanceSheet.repayLoanToBank(pctToPayOut * bankLoansPayable,
                                 bankLoansPayable);
}

void ConcreteBank::collectLoan(Bank* borrower, double repaidAmount,
                               double dueAmount){
    bankLoansDue[borrower] -= repaidAmount;
    balanceSheet.collectLoanFromBank(repaidAmount,dueAmount);
}

void ConcreteBank::collectLoan(Firm* borrower){

    double interestRate =
            MacroFinancialFactors::getInterestRateLoans();

    double loanDue = loans[borrower];

    double repaidAmount = borrower->repayLoan(this,interestRate);
    loans[borrower] -= std::min(repaidAmount,loanDue);
    totalUnpaidLoans += std::max(0.0,(loanDue - repaidAmount));

    balanceSheet.collectLoansFromFirms(repaidAmount, loanDue);
}

double ConcreteBank::getDeposits(void) const{
    return balanceSheet.getDeposits();
}

void ConcreteBank::collectLoansFromFirms(void){

    for(Firm* borrower: borrowers){
        collectLoan(borrower);
    }

    balanceSheet.writeOffLoansToFirms();
}

//simultaneous service
void ConcreteBank::requestWithdrawal(Depositor* depositor,
                                     double amount){

    //only existing depositors can withdraw
    auto depositorElement = deposits.find(depositor);
    if(depositorElement == deposits.end())
        return;

    //depositors cant't withdraw more than what they have
    double amountToWithdraw = std::min(amount,
                                       depositorElement->second);
    pendingWithdrawals[depositor] += amountToWithdraw;
    totalPendingWithdrawals += amountToWithdraw;
}

// simultaneous service (all withdrawals),
// or also sequential service
// (if there are pending withdrawals upon first request)
void ConcreteBank::payOutWithdrawals(void){

    double pctToPayOut = std::min(getLiquidAssets(),
                                  totalPendingWithdrawals) /
                         totalPendingWithdrawals;

    for(auto & currentDeposit: deposits ){
        Depositor * currentDepositor = currentDeposit.first;
        double depositValue = currentDeposit.second;
        currentDepositor->receiveWithdrawal(this,
                                            pctToPayOut *
                                            depositValue);
        deposits[currentDepositor] -= pctToPayOut *
                                      depositValue;
        pendingWithdrawals[currentDepositor] -= pctToPayOut *
                                                depositValue;
    }

    if (pctToPayOut == 1.0) {
        pendingWithdrawals.clear();
    }
    balanceSheet.repayDeposit(pctToPayOut * totalPendingWithdrawals);
    totalPendingWithdrawals -= (pctToPayOut * totalPendingWithdrawals);

}

void ConcreteBank::payOutEarlyWithdrawals(void){

    if (totalPendingWithdrawals > 0.0){

        const double roundingError = 0.000001;

        double pctToPayOut = std::min(getLiquidAssets(),
                                      totalPendingWithdrawals) /
                             totalPendingWithdrawals;

        for(auto & currentDeposit: pendingWithdrawals ){
            Depositor * currentDepositor = currentDeposit.first;
            double depositValue = currentDeposit.second;
            currentDepositor->receiveWithdrawal(this,
                                                pctToPayOut *
                                                depositValue);
            deposits[currentDepositor] -= pctToPayOut *
                                          depositValue;
            pendingWithdrawals[currentDepositor] -= pctToPayOut *
                                                    depositValue;
        }

        if (pctToPayOut >= (1.0 - roundingError)) {
            pendingWithdrawals.clear();
        }
        balanceSheet.repayDeposit(pctToPayOut * totalPendingWithdrawals);
        totalPendingWithdrawals -= (pctToPayOut * totalPendingWithdrawals);
    }
}

void ConcreteBank::payOutMaturingDeposits(void){

    double totalDeposits = getDeposits();

    if (totalDeposits > 0.0){
        const double roundingError = 0.000001;



        double pctToPayOut = std::min(getLiquidAssets(),
                                      totalDeposits) /
                             totalDeposits;

        double interestOnDeposits = 0.0;

        for(auto & currentDeposit: deposits ){
            Depositor * currentDepositor = currentDeposit.first;
            double depositValue = currentDeposit.second;
            currentDepositor->receiveWithdrawal(this,
                                                pctToPayOut *
                                                depositValue);
            deposits[currentDepositor] -= pctToPayOut *
                                          depositValue;
            if(pendingWithdrawals.find(currentDepositor) !=
               pendingWithdrawals.end()){
                pendingWithdrawals[currentDepositor] -= pctToPayOut *
                                                        depositValue;
                totalPendingWithdrawals -= (pctToPayOut * depositValue);
            }
        }

        if (pctToPayOut >= (1.0 - roundingError)) {
            double owedInterest = totalDeposits *
                                  MacroFinancialFactors::getInterestRateDeposits();
            interestOnDeposits = std::min(owedInterest,
                                          (getLiquidAssets() -
                                           totalDeposits));
            deposits.clear();
            pendingWithdrawals.clear();
        }

        balanceSheet.repayDeposit(pctToPayOut * totalDeposits,interestOnDeposits);
    }
}

double ConcreteBank::getTotalAssets(void) const{
    return balanceSheet.getTotalAssets();
}

double ConcreteBank::getLeverage(void) const{
    return (getCapital()/getTotalAssets());
}

double ConcreteBank::getCapital(void) const {
    return balanceSheet.getTotalEquity();
}

double ConcreteBank::getLoansToFirms(void) const{
    return balanceSheet.getLoansToFirms();
}

double ConcreteBank::getLoansToBanks(void)const {
    return balanceSheet.getLoansToBanks();
}

double ConcreteBank::getOtherAssets(void)const {
    return balanceSheet.getOtherAssets();
}

double ConcreteBank::getPendingWithdrawals(void) const{
    return totalPendingWithdrawals;
}

void ConcreteBank::sellRiskyAssetsToRepay(double pricePctFaceValue,
                                          double quantity){
    double proceeds = pricePctFaceValue * quantity;

    balanceSheet.sellLoan(quantity, proceeds);

    totalPendingWithdrawals -= std::min (proceeds,
                                         totalPendingWithdrawals);
}

void ConcreteBank::sellRiskyAssets(Bank* buyer,
                                   double pricePctFaceValue,
                                   double amount) {
    double totalLoans = balanceSheet.getLoansToFirms();

    if((totalLoans == 0.0) || (amount == 0.0))
        return;

    double proceeds = pricePctFaceValue * amount;

    double pctSold = amount / totalLoans;

    for(auto currentBorrower : borrowers){
        double balanceSold = loans[currentBorrower] * pctSold;
        loans[currentBorrower] -= balanceSold;
        currentBorrower->transferLoan(this,
                                      buyer,
                                      balanceSold,
                                      pricePctFaceValue);
        //tranferLoan will subsequently call the buyer's buyLoan function
    }

    balanceSheet.sellLoan(amount, proceeds);
}

void ConcreteBank::accrueInterestToDepositors(void){

    double totalDeposits = getDeposits();

    if(getLiquidAssets() < totalDeposits)
        return;

    double interestRate =
            MacroFinancialFactors::getInterestRateDeposits();
    double totalAccrualBasis = totalDeposits - totalPendingWithdrawals;
    double totalInterestOwed = interestRate * totalAccrualBasis;

    double effectiveRate = std::max(interestRate,
                                    (totalInterestOwed
                                     /totalAccrualBasis));

    for(auto& deposit: deposits){
        double pendingPortion = 0.0;
        if(pendingWithdrawals.find(deposit.first) !=
           pendingWithdrawals.end()){
            pendingPortion = pendingWithdrawals[deposit.first];
        }
        double accrualBasis = (deposit.second - pendingPortion);
        double totalInterestOnDeposit = effectiveRate * accrualBasis;
        deposit.second += totalInterestOnDeposit;
        deposit.first->accrueInterest(this, totalInterestOnDeposit);
    }
}

void ConcreteBank::buyLoans(Firm* borrower,
                            double quantity,
                            double pricePctFaceValue) {

    //in accounting terms, loans are valued at acquisition price
    borrowers.insert(borrower);
    // loans[borrower] += quantity;
    loans[borrower] += pricePctFaceValue * quantity;
    balanceSheet.buyLoan(pricePctFaceValue * quantity);
}

void ConcreteBank::buyAssetsFromOtherBanks(double pricePctFaceValue,
                                           double quantity){

    //in accounting terms, loans are valued at acquisition price
    balanceSheet.buyLoan(pricePctFaceValue * quantity);
}

void ConcreteBank::receiveDeposit(Depositor* depositor,
                                  double amount){
    //std::map will create an entry for the given depositor
    // automatically if it does not exists. This suits our needs.
    deposits[depositor] += amount;
    balanceSheet.receiveDeposit(amount);
}

void ConcreteBank::grantLoanToFirm(Firm* borrower,
                                   double amount){
    borrowers.insert(borrower);
    loans[borrower] += amount;
    borrower->getLoan(this,amount);
    balanceSheet.grantLoanToFirm(amount);
}


void ConcreteBank::raiseCapital(double amount){
    balanceSheet.raiseCapital(amount);
}

double ConcreteBank::getReturnOnEquity(void){
    double profit = balanceSheet.getProfit();
    double roe = (profit/initialEquity);
    //limited liability: can't lose more than original equity
    return std::max(-1.0,roe);
}

bool ConcreteBank::isInsolvent(void) const{
    return (getCapital() < 0.0);
}

bool ConcreteBank::isIlliquid(void) const{
    return (totalPendingWithdrawals > balanceSheet.getLiquidAssets());
}

std::string ConcreteBank::toString() const{
    std::stringstream result;
    result << getName() << std::endl << balanceSheet.toString();
    result << "Depositors: "<< std::endl << listDeposits()
           << "Pending withdrawals: " << std::endl
           << listPendingWithdrawals() << std::endl;
    return result.str();
}

std::string ConcreteBank::listDeposits(void) const {
    std::stringstream descriptor;

    for(auto deposit: deposits){
        descriptor << deposit.first->getName() << ": ";
        descriptor << deposit.second << std::endl;
    }

    return descriptor.str();
}

std::string ConcreteBank::listPendingWithdrawals(void) const {
    std::stringstream descriptor;

    for(auto withdrawal: pendingWithdrawals){
        descriptor << withdrawal.first->getName() << ": ";
        descriptor << withdrawal.second << std::endl;
    }

    return descriptor.str();
}
//virtual Bank::LiquidationCause getLiquidationCause(void) const;

void ConcreteBank::sellRiskyAssetsToInvestor(NonBankInvestor* investor,
                                             double pricePctFaceValue,
                                             double amount){
    double totalLoans = balanceSheet.getLoansToFirms();

    if((totalLoans == 0.0) || (amount == 0.0))
        return;

    double proceeds = pricePctFaceValue * amount;

    double pctSold = amount / totalLoans;

    for(auto currentBorrower : borrowers){
        double balanceSold = loans[currentBorrower] * pctSold;
        loans[currentBorrower] -= balanceSold;
        currentBorrower->transferLoan(this,
                                      investor,
                                      balanceSold);
    }

    balanceSheet.sellLoan(amount, proceeds);
}

bool ConcreteBank::isBeingLiquidated(void){
    return beingLiquidated;
}


void ConcreteBank::declareInsolvent(void){
    if((!beingLiquidated) && (!failedBank)){
        failureCause = BankFailureCause::solvency;
        capitalAtFailure = (getCapital() / getTotalAssets());
        liquidityAtFailure = (getLiquidAssets() / getTotalAssets());
        beingLiquidated = true;
        failedBank = true;
    }
}
void ConcreteBank::declareIlliquid(void){
    if((!beingLiquidated) && (!failedBank)){
        failureCause = BankFailureCause::liquidity;
        capitalAtFailure = (getCapital() / getTotalAssets());
        liquidityAtFailure = (getLiquidAssets() / getTotalAssets());
        beingLiquidated = true;
        failedBank = true;
    }
}

void ConcreteBank::finishLiquidation(NonBankInvestor* investor) {

    if (!beingLiquidated)
        return;

    double remainingProceeds = 0.0;
    remainingProceeds += balanceSheet.getLiquidAssets();
    remainingProceeds += ((balanceSheet.getTotalAssets() -
                           balanceSheet.getLiquidAssets() +
                           totalUnpaidLoans) *
                          (1.0 - MacroFinancialFactors::getInsolvencyHaircut()));

    //std::cout << "Insolv. HC: " << MacroFinancialFactors::getInsolvencyHaircut() << std::endl;

    // We will now resolve liabilities in order of subordination

    //first, legal, administrative costs
    remainingProceeds -= (initialAssetSize *
                          MacroFinancialFactors::getBankruptcyCosts());
    if(remainingProceeds < 0.0)
        remainingProceeds = 0.0;

    //std::cout << "Remaining Proceeds: " << remainingProceeds << std::endl;

    //TODO
    // ... then, discountWindowLoan...

    //TODO
    // ... aftwerwards, interbank loans..

    // ... finally, if there is any money left, it is
    // proportionally divided among depositors.

    double depositMass = balanceSheet.getDeposits();
    double depositorPayout = std::min(remainingProceeds, depositMass);
    //double depositorPayout = std::max(0.0,std::min(remainingProceeds, depositMass));
    remainingProceeds -= depositorPayout;
    double pctRepaid = depositorPayout / depositMass;

    for(auto currentDeposit : deposits){
        double individualClaim = currentDeposit.second;
        currentDeposit.first->receiveWithdrawal(this,
                                                pctRepaid *
                                                individualClaim);
    }

    for(auto currentBorrower : borrowers){
        //in this case I don't need to do anything!
        currentBorrower->transferLoan(this,
                                      investor,
                                      loans[currentBorrower]);
    }

    beingLiquidated = false;
    //balanceSheet.reset();
}

bool ConcreteBank::hasFailed(void) {
    return failedBank;
}

double ConcreteBank::getCapitalAtFailure(void) {
    return capitalAtFailure;
}

double ConcreteBank::getLiquidityAtFailure(void) {
    return liquidityAtFailure;
}

BankFailureCause ConcreteBank::getFailureCause(void) {
    return failureCause;
}

/*
Bank::LiquidationCause ConcreteBank::getLiquidationCause(void) const{
    return liquidationCause;
}*/
