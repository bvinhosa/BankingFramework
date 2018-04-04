#include <iostream>
#include "CommonWorkflow.hpp"

CommonWorkflow::CommonWorkflow() :
        theCycle(theIteration),
        theRepetition(theCycle,10),
        theSystem(params,sizes) {

}

void CommonWorkflow::execute(void){
    std::cout << "CommonWorkflow::execute" << std::endl;
    theRepetition.repeat(theSystem);
}

std::string CommonWorkflow::exportResultsToString(void) {
    return std::string("CommonWorkflow results");
}
