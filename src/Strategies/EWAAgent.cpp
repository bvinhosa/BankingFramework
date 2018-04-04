#include "EWAAgent.hpp"

//EWAAgent::EWAAgent(std::set<Strategy*> strategySet){
    //myExperience.initUniform(strategySet);
//}

void EWAAgent::resetStrategies(void){
    learningSuspended = false;
    forcingStrategy=false;
    myExperience.reset();
}

bool EWAAgent::reasonsCounterfactually(void) const{
    if(learningSuspended)
        return false;
    return true;
}

bool EWAAgent::isFactual(Strategy* givenStrategy) const{
    if(learningSuspended)
        return true;
    return (givenStrategy == currentFactual);
}

void EWAAgent::learnFromExperience(void){

    if(learningSuspended)
        return;

    myExperience.learn(currentFactual,this);
}

void EWAAgent::setUpStrategy(Strategy* newStrategy){
    currentStrategy = newStrategy;
    currentStrategy->configure(this);
}

void EWAAgent::setUpForSimulation(void){
    if(forcingStrategy)
        return;
    currentFactual = myExperience.drawStrategy();
    setUpStrategy(currentFactual);
}

void EWAAgent::observePayoff(void){
    if(learningSuspended)
        return;
    myExperience.observePayoff(currentStrategy,this);
}


void EWAAgent::resetExperience(void){
    if(learningSuspended)
        return;
    myExperience.reset();
}

void EWAAgent::revertToFactual(void){
    if(learningSuspended)
        return;
    currentStrategy = currentFactual;
}

void EWAAgent::suspendLearning(void){
    learningSuspended = true;
}

void EWAAgent::resumeLearning(void){
    learningSuspended = false;
}

void EWAAgent::forceStrategy(Strategy* forcedStrategy){
    forcingStrategy=true;
    currentFactual = forcedStrategy;
    setUpStrategy(forcedStrategy);
}

void EWAAgent::freeStrategies(){
    forcingStrategy=false;
}

StrategyPointerSet& EWAAgent::getPossibleStrategies(void){
    return myExperience.getStrategies();
}


