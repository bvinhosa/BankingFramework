#ifndef DEPOSITOR_HPP
#define DEPOSITOR_HPP

#include "Agent.hpp"

#include <vector>
#include <string>

class Bank;

struct DepositorRunDiagnostic{
    Bank* bankUndergoingRun;
    double capitalAtRun;
    double liquidityAtRun;
};

typedef std::vector<DepositorRunDiagnostic> RunDiagnosticVector;

class Depositor : public Agent {
public:
    virtual int getDepositorId(void) const = 0;
    virtual void setUpWithdrawal(double proportionToWithdraw) = 0;
    virtual void setUpThreshold(double runThreshold) = 0;
    virtual double getThreshold(void) = 0;
    virtual void receiveWithdrawal(Bank* bank, double amount) = 0;
    virtual void assessWithdrawal(void) = 0;
    virtual double getReturnOnDeposit(void) = 0;
    virtual void accrueInterest(Bank* bank, double interestRate) = 0;
    virtual void receiveMoney(double amount) = 0;
    virtual void makeDeposit(Bank *bank,
                             double amount) = 0;
    virtual RunDiagnosticVector getBankRuns(void) = 0;
};

typedef std::vector<Depositor*> DepositorPointerVector;

#endif //DEPOSITOR_HPP
