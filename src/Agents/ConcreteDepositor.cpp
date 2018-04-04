#include "ConcreteDepositor.hpp"

#include <set>

#include <sstream>

#include "Bank.hpp"

ConcreteDepositor::ConcreteDepositor(const std::string & givenName, int agentId, int depositorId) {
    reset();
    name.assign(givenName);
    this->agentId = agentId;
    this->depositorId = depositorId;
}

int ConcreteDepositor::getId(void) const{
    return agentId;
}

int ConcreteDepositor::getDepositorId(void) const{
    return depositorId;
}
/*
ConcreteDepositor::ConcreteDepositor(const std::string & givenName) {
    reset();
    name.assign(givenName);
}
*/
std::string ConcreteDepositor::getName(void) const{
    return name;
}
/*
ConcreteDepositor::ConcreteDepositor(void){
    reset();
}

ConcreteDepositor::ConcreteDepositor(const std::string & givenName,
                                     double initialEndowment){
    reset();
    name.assign(givenName);
    currencyInPossession = initialEndowment;
    overallEndowment = initialEndowment;
}

ConcreteDepositor::ConcreteDepositor(double initialEndowment,
                                     double initialDeposits){
    currencyInPossession = initialEndowment;
    overallEndowment = initialEndowment;
    totalDeposits = initialDeposits;
}
*/
void ConcreteDepositor::reset(void){
    totalDeposits = 0.0;
    currencyInPossession = 0.0;
    overallEndowment = 0.0;

    threshold = 0.0;
    proportionToWithdraw = 0.0;

    active=true;

    deposits.clear();
}

void ConcreteDepositor::receiveMoney(double amount) {
    currencyInPossession += amount;
    overallEndowment += amount;
}

void ConcreteDepositor::setUpThreshold(double runThreshold){
    threshold = runThreshold;
}

void ConcreteDepositor::setUpWithdrawal(double proportionToWithdraw){
    this->proportionToWithdraw = proportionToWithdraw;
}

double ConcreteDepositor::getReturnOnDeposit(void){
    return (currencyInPossession/overallEndowment);
}

void ConcreteDepositor::assessWithdrawal(void){

    std::set<Bank*> healthyBanks, allBanks;
    double withdrawnPerceivedRisk = 0.0;
    double initialDeposits = totalDeposits;

    double amountToWithdraw = proportionToWithdraw * overallEndowment;

    for(auto& deposit : deposits){
        healthyBanks.insert(deposit.first);
        allBanks.insert(deposit.first);
    }

    for(auto& bank: allBanks){
        if(shouldWithdrawFrom(bank)){
            setRun(bank);
            withdrawnPerceivedRisk += deposits[bank];
            healthyBanks.erase(bank);
            requestWithdrawal(bank);
        }
    }

    if(withdrawnPerceivedRisk >= amountToWithdraw)
        return;

    double remainingWithdrawals = amountToWithdraw - withdrawnPerceivedRisk;
    double depositsInHealthyBanks = initialDeposits - withdrawnPerceivedRisk;
    double pctWithdrawnHealthy = remainingWithdrawals / depositsInHealthyBanks;

    for(auto& healthyBank: healthyBanks)
        requestWithdrawal(healthyBank, (pctWithdrawnHealthy * deposits[healthyBank]));
}

bool ConcreteDepositor::shouldWithdrawFrom(Bank* bank){
    if(bank->getLeverage() <= threshold)
        return true;
    return false;
}

void ConcreteDepositor::accrueInterest(Bank* bank, double interestOnDeposit){
    double currentDeposit = deposits[bank];
    deposits[bank] = currentDeposit + interestOnDeposit;
    totalDeposits += interestOnDeposit;
}

double ConcreteDepositor::getDeposits(void) const{
    return totalDeposits;
}

double ConcreteDepositor::getMoney(void) const{
    return currencyInPossession;
}
void ConcreteDepositor::requestWithdrawal(Bank *bank,
                                          double amount){

    // depositors cant't withdraw more than how
    // much they have at that particular bank
    double amountToWithdraw = std::min(amount, deposits[bank]);
    bank->requestWithdrawal(this, amountToWithdraw);
}

void ConcreteDepositor::requestWithdrawal(Bank *bank){
    requestWithdrawal(bank, deposits[bank]);
}
void ConcreteDepositor::makeDeposit(Bank *bank,
                                    double amount) {

    //depositors cant't deposit more than what they possess
    double amountToDeposit = std::min(amount,currencyInPossession);
    currencyInPossession -= amountToDeposit;
    totalDeposits += amountToDeposit;

    //std::map will create an entry for the given bank automatically
    // if it does not exists. This suits our needs.
    deposits[bank] +=amountToDeposit;
    bank->receiveDeposit(this,amountToDeposit);
}

void ConcreteDepositor::depositAllMoney(Bank *bank) {

    makeDeposit(bank,currencyInPossession);
}
void ConcreteDepositor::receiveWithdrawal(Bank *bank, double amount){
    deposits[bank] -=amount;
    totalDeposits -= amount;
    currencyInPossession += amount;
}

std::string ConcreteDepositor::toString(void) const{
    std::stringstream descriptor;

    descriptor << getName() <<":" << std::endl;
    descriptor << "--------------------------------" << std::endl;
    descriptor << "Currency in possession: ";
    descriptor << currencyInPossession << std::endl;
    descriptor << "Deposits: ";
    descriptor << totalDeposits << std::endl;

    descriptor << listDeposits() << std::endl;

    return descriptor.str();
}

std::string ConcreteDepositor::listDeposits(void) const {
    std::stringstream descriptor;

    for(auto deposit: deposits){
        descriptor << deposit.first->getName() << ": ";
        descriptor << deposit.second << std::endl;
    }

    return descriptor.str();
}

RunDiagnosticVector ConcreteDepositor::getBankRuns(void) {
    return bankRunInfo;
}

void ConcreteDepositor::setRun(Bank *bank) {
    double capitalAtRun = (bank->getCapital() / bank->getTotalAssets());
    double liquidityAtRun = (bank->getCapital() / bank->getTotalAssets());
    DepositorRunDiagnostic thisRun = {bank, capitalAtRun, liquidityAtRun};
    bankRunInfo.push_back(thisRun);
}
