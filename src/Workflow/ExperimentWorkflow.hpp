#ifndef EXPERIMENTWORKFLOW_HPP
#define EXPERIMENTWORKFLOW_HPP

#include "CommonWorkflow.hpp"
#include "../Economy/StandardBankingSystem.hpp"
#include "ExperimentRepetition.hpp"
#include "CommonCycle.hpp"
#include "CommonIteration.hpp"

class ExperimentWorkflow : public Workflow {
public:
    ExperimentWorkflow(int numReps,
                       int cyclesPerRep,
                       StandardBankingSystem::Parameters params,
                       std::vector<double> sizes);
    virtual void execute(void);
    virtual std::string exportResultsToString(void);
private:
    const int numRepetitions;

    StandardBankingSystem theSystem;

    ExperimentRepetition theRepetition;
    CommonCycle theCycle;
    CommonIteration theIteration;
};

#endif //EXPERIMENTWORKFLOW_HPP
