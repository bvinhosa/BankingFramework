#ifndef LEARNINGWORFLOW_HPP
#define LEARNINGWORFLOW_HPP

#include "CommonWorkflow.hpp"
#include "../Economy/StandardBankingSystem.hpp"
#include "LearningCycle.hpp"
#include "CommonIteration.hpp"
#include "CommonRepetition.hpp"

class LearningWorkflow : public Workflow {
public:
    LearningWorkflow(int numReps,
                     int cyclesPerRep,
                     StandardBankingSystem::Parameters params,
                     std::vector<double> sizes);
    virtual void execute(void);
    virtual std::string exportResultsToString(void);

private:
    const int numRepetitions;
    StandardBankingSystem theSystem;

    CommonRepetition theRepetition;
    LearningCycle theCycle;
    CommonIteration theIteration;
};


#endif //LEARNINGWORFLOW_HPP
