#include "ThresholdDepositor.hpp"

ThresholdDepositor::ThresholdDepositor(std::set<Strategy *> strategySet,
                                       const std::string & givenName,
                                       int agentId,
                                       int depositorId) : ConcreteDepositor(givenName,
                                                                            agentId,
                                                                            depositorId){
    myExperience.initUniform(strategySet);
}

/*
bool ThresholdDepositor::reasonsCounterfactually(void) const{
    if(learningSuspended)
        return false;
    return true;
}

bool ThresholdDepositor::isFactual(Strategy* givenStrategy) const{
    if(learningSuspended)
        return true;
    return (givenStrategy == currentFactual);
}

void ThresholdDepositor::learnFromExperience(void){
    if(learningSuspended)
        return;
    myExperience.learn(currentFactual,this);
}

void ThresholdDepositor::setUpStrategy(Strategy* newStrategy){
    currentStrategy = newStrategy;
    currentStrategy->configure(this);
}

void ThresholdDepositor::setUpForSimulation(void){
    if(forcingStrategy)
        return;
    currentFactual = myExperience.drawStrategy();
    setUpStrategy(currentFactual);
}

void ThresholdDepositor::resetExperience(void){
    if(learningSuspended)
        return;
    myExperience.reset();
}

void ThresholdDepositor::observePayoff(void){
    if(learningSuspended)
        return;
    myExperience.observePayoff(currentStrategy,this);
}

void ThresholdDepositor::revertToFactual(void){
    if(learningSuspended)
        return;
    currentStrategy = currentFactual;
}

void ThresholdDepositor::suspendLearning(void){
    learningSuspended = true;
}

void ThresholdDepositor::resumeLearning(void){
    learningSuspended = false;
}

void ThresholdDepositor::forceStrategy(Strategy* forcedStrategy){
    forcingStrategy=true;
    currentFactual = forcedStrategy;
    setUpStrategy(forcedStrategy);
}

void ThresholdDepositor::freeStrategies(){
    forcingStrategy=false;
}

std::string ThresholdDepositor::toString(void){
    return myExperience.toString();
}
*/