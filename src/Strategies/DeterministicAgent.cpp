#include "DeterministicAgent.hpp"

void DeterministicAgent::resetStrategies(void){
}

bool DeterministicAgent::reasonsCounterfactually(void) const{
    return false;
}

bool DeterministicAgent::isFactual(Strategy* givenStrategy) const{
    return true;
}

void DeterministicAgent::learnFromExperience(void){
}

void DeterministicAgent::setUpStrategy(Strategy* newStrategy){
}

void DeterministicAgent::setUpForSimulation(void) {
    setUpStrategy(constantStrategy);
}

void DeterministicAgent::observePayoff(void){
}

void DeterministicAgent::resetExperience(void){
}

void DeterministicAgent::revertToFactual(void){
}

StrategyPointerSet& DeterministicAgent::getPossibleStrategies(void){
    std::set<Strategy*> setWithOneStrategy;
    setWithOneStrategy.insert(constantStrategy);
    return setWithOneStrategy;
}

void DeterministicAgent::suspendLearning(void){
}

void DeterministicAgent::resumeLearning(void){
}

void DeterministicAgent::forceStrategy(Strategy* forcedStrategy){
}

void DeterministicAgent::freeStrategies() {
}

