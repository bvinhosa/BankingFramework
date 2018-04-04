#include "RandomAgent.hpp"

void RandomAgent::resetStrategies(void){
    bool forcingStrategy=false;
}

bool RandomAgent::reasonsCounterfactually(void) const{
    return false;
}

bool RandomAgent::isFactual(Strategy* givenStrategy) const {
    return true;
}

void RandomAgent::learnFromExperience(void){
}

void RandomAgent::setUpStrategy(Strategy* newStrategy){
    newStrategy->configure(this);
}

void RandomAgent::setUpForSimulation(void){
    currentStrategy = distribution.drawStrategy();
    setUpStrategy(currentStrategy);
}

void RandomAgent::observePayoff(void){
}

void RandomAgent::resetExperience(void){
}

void RandomAgent::revertToFactual(void){
}

void RandomAgent::suspendLearning(void){
}
void RandomAgent::resumeLearning(void){
}
void RandomAgent::forceStrategy(Strategy* forcedStrategy){
    forcingStrategy=true;
    setUpStrategy(forcedStrategy);
}

void RandomAgent::freeStrategies(){
    forcingStrategy=false;
}
StrategyPointerSet& RandomAgent::getPossibleStrategies(void){
    return distribution.getStrategies();
}