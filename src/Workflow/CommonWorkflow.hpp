#ifndef COMMONWORKFLOW_HPP
#define COMMONWORKFLOW_HPP

#include "Workflow.hpp"
#include "../Economy/StandardBankingSystem.hpp"
#include "CommonCycle.hpp"
#include "CommonIteration.hpp"
#include "CommonRepetition.hpp"

class CommonWorkflow : public Workflow{
public:
    CommonWorkflow();
    virtual void execute(void);
    virtual std::string exportResultsToString(void);
private:
    const int numRepetitions=10;
    const int numCyclesPerRepetition=10;

    StandardBankingSystem::Parameters params = {10, 5, 5};
    std::vector<double> sizes = {1.0,1.0,1.0,1.0,1.0,
                                 1.0,1.0,1.0,1.0,1.0};

    StandardBankingSystem theSystem;

    CommonRepetition theRepetition;
    CommonCycle theCycle;
    CommonIteration theIteration;
};


#endif  //COMMONWORKFLOW_HPP
