#include <iostream>
#include "ExperimentWorkflow.hpp"

ExperimentWorkflow::ExperimentWorkflow(int numReps,
                                       int cyclesPerRep,
                                       StandardBankingSystem::Parameters params,
                                       std::vector<double> sizes) :
        theCycle(theIteration),
        theRepetition(theCycle,cyclesPerRep),
        numRepetitions(numReps),
        theSystem(params,sizes) {
}

void ExperimentWorkflow::execute(void){
    //std::cout << "ExperimentWorkflow::execute" << std::endl;

    for(int i = 0; i < numRepetitions; i++){
        theRepetition.repeat(theSystem);
    }

}

std::string ExperimentWorkflow::exportResultsToString() {
    return theRepetition.getFinalResults();
}
