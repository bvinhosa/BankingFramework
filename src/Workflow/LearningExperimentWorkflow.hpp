#ifndef LEARNINGEXPERIMENTWORKFLOW_HPP
#define LEARNINGEXPERIMENTWORKFLOW_HPP

#include "Workflow.hpp"
#include "ExperimentRepetition.hpp"
#include "CommonIteration.hpp"
#include "LearningCycle.hpp"
#include "../Economy/StandardBankingSystem.hpp"


class LearningExperimentWorkflow : public Workflow {
public:
    LearningExperimentWorkflow(int numReps,
                               int cyclesPerRep,
                               StandardBankingSystem::Parameters params,
                               std::vector<double> sizes);
    virtual void execute(void);
    virtual std::string exportResultsToString(void);
private:
    const int numRepetitions;
    //const int cyclesPerRepetition;

    StandardBankingSystem theSystem;

    ExperimentRepetition theRepetition;
    LearningCycle theCycle;
    CommonIteration theIteration;
};

#endif //LEARNINGEXPERIMENTWORKFLOW_HPP
