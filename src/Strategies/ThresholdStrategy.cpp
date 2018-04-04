#include "ThresholdStrategy.hpp"

#include <sstream>

#include "../Agents/ThresholdDepositor.hpp"

ThresholdStrategy::ThresholdStrategy(double givenThreshold) :
        runThreshold(givenThreshold){}

void ThresholdStrategy::configure(StrategicAgent* theAgent){
    Depositor* theDepositor = dynamic_cast<Depositor*>(theAgent);
    theDepositor->setUpThreshold(runThreshold);
}

double ThresholdStrategy::getPayoff(StrategicAgent* theAgent) const{
    Depositor* theDepositor = dynamic_cast<Depositor*>(theAgent);
    theDepositor->getReturnOnDeposit();
}

std::string ThresholdStrategy::toString(void) const{
    std::stringstream result;
    result << "Threshold for running: " << runThreshold;
    return result.str();
}
