#include "LearningExperimentWorkflow.hpp"

#include <iostream>

LearningExperimentWorkflow::LearningExperimentWorkflow(int numReps,
                                                       int cyclesPerRep,
                                                       StandardBankingSystem::Parameters params,
                                                       std::vector<double> sizes) :
        theCycle(theIteration),
        theRepetition(theCycle,cyclesPerRep),
        numRepetitions(numReps),
        theSystem(params,sizes) {
}

void LearningExperimentWorkflow::execute(void) {
    //std::cout << "LearningExperimentWorkflow::execute" << std::endl;

    for(int i = 0; i < numRepetitions; i++){
        theRepetition.repeat(theSystem);
        theSystem.strategicReset();
    }
}

std::string LearningExperimentWorkflow::exportResultsToString(void) {
    return (theRepetition.getFinalResults() +
            std::string(" in LearningExperiment"));
}
