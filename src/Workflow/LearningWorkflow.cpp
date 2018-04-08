#include <iostream>
#include "LearningWorkflow.hpp"

LearningWorkflow::LearningWorkflow(int numReps,
                                   int cyclesPerRep,
                                   StandardBankingSystem::Parameters params,
                                   std::vector<double> sizes) :
        theCycle(numReps*cyclesPerRep, theIteration),
        theRepetition(theCycle,cyclesPerRep),
        numRepetitions(numReps),
        theSystem(params,sizes) {
}

void LearningWorkflow::execute(void){
    //std::cout << "LearningWorflow::execute" << std::endl;

    for(int i = 0; i < numRepetitions; i++){
        theRepetition.repeat(theSystem);
        theSystem.strategicReset();
    }

}

std::string LearningWorkflow::exportResultsToString(void) {
    return (theRepetition.getFinalResults() +
            std::string(" in Learning"));
}
