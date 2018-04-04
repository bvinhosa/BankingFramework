#ifndef CONCRETEDEPOSITOR_HPP
#define CONCRETEDEPOSITOR_HPP

#include <map>
#include <string>

#include "Depositor.hpp"

class Bank;

class ConcreteDepositor : public Depositor {
public:
    ConcreteDepositor(const std::string & givenName, int agentId, int depositorId);
    /*
    ConcreteDepositor(const std::string& name);
    ConcreteDepositor(void);
    ConcreteDepositor(double initialEndowment,
                      double initialDeposits);
    ConcreteDepositor(const std::string & givenName,
                      double initialEndowment);
    */
    virtual std::string getName(void) const;
    virtual int getId(void) const;
    virtual std::string toString(void) const;
    virtual int getDepositorId(void) const;

    virtual void reset(void);
    virtual void setUpWithdrawal(double proportionToWithdraw);
    virtual void setUpThreshold(double runThreshold);
    virtual double getReturnOnDeposit(void);
    virtual void receiveMoney(double amount);
    virtual void makeDeposit(Bank *bank, double amount);
    virtual void depositAllMoney(Bank *bank);
    virtual void requestWithdrawal(Bank *bank, double amount);
    virtual void requestWithdrawal(Bank *bank);
    virtual void receiveWithdrawal(Bank *bank, double amount);
    virtual void accrueInterest(Bank* bank, double interestRate);
    virtual double getDeposits(void) const;
    virtual double getMoney(void) const;
    virtual void assessWithdrawal(void);
    virtual bool shouldWithdrawFrom(Bank* bank);
    virtual std::string listDeposits(void) const;
    virtual RunDiagnosticVector getBankRuns(void);

    //WHO'S RESPONSIBLE FOR INTEREST ACCRUAL???

protected:
    std::map<Bank*,double> deposits;
    virtual void setRun(Bank* bank);
    RunDiagnosticVector bankRunInfo;

private:
    int agentId;
    int depositorId;
    std::string name;

    double totalDeposits = 0.0;
    double currencyInPossession = 0.0;
    double overallEndowment = 0.0;

    double threshold = 0.0;
    double proportionToWithdraw = 0.0;

    bool active;
};


#endif //CONCRETEDEPOSITOR_HPP
