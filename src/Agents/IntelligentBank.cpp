#include "IntelligentBank.hpp"

#include <sstream>

IntelligentBank::IntelligentBank(std::set<Strategy*> strategySet,
                                 const std::string & givenName,
                                 int agentId,
                                 int bankId) : ConcreteBank(givenName,
                                                            agentId,
                                                            bankId){
    myExperience.initUniform(strategySet);
}

std::string IntelligentBank::toString(void){
    return myExperience.toString();
}

/*
bool IntelligentBank::reasonsCounterfactually(void) const{
    if(learningSuspended)
        return false;
    return true;
}

bool IntelligentBank::isFactual(Strategy* givenStrategy) const{
    if(learningSuspended)
        return true;
    return (givenStrategy == currentFactual);
}

void IntelligentBank::learnFromExperience(void){
    if(learningSuspended)
        return;
    myExperience.learn(currentFactual,this);
}

void IntelligentBank::setUpStrategy(Strategy* newStrategy){
    currentStrategy = newStrategy;
    currentStrategy->configure(this);
}

void IntelligentBank::setUpForSimulation(void){
    if(forcingStrategy)
        return;
    currentFactual = myExperience.drawStrategy();
    setUpStrategy(currentFactual);
}

void IntelligentBank::resetExperience(void){
    if(learningSuspended)
        return;
    myExperience.reset();
}

void IntelligentBank::observePayoff(void){
    if(learningSuspended)
        return;
    myExperience.observePayoff(currentStrategy,this);
}

void IntelligentBank::revertToFactual(void){
    if(learningSuspended)
        return;
    currentStrategy = currentFactual;
}

void IntelligentBank::suspendLearning(void){
    learningSuspended = true;
}

void IntelligentBank::resumeLearning(void){
    learningSuspended = false;
}

void IntelligentBank::forceStrategy(Strategy* forcedStrategy){
    forcingStrategy=true;
    currentFactual = forcedStrategy;
    setUpStrategy(forcedStrategy);
}

void IntelligentBank::freeStrategies(){
    forcingStrategy=false;
}

*/

