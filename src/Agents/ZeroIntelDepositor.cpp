#include "ZeroIntelDepositor.hpp"
#include "../Strategies/ZeroIntelStrategy.hpp"

ZeroIntelDepositor::ZeroIntelDepositor(double withdrawalProbability,
                                       const std::string & givenName,
                                       int agentId,
                                       int depositorId) : ConcreteDepositor(givenName,
                                                                            agentId,
                                                                            depositorId){
    ZeroIntelStrategy* doWithdraw = new ZeroIntelStrategy(1.0);
    ZeroIntelStrategy* doNotWithdraw = new ZeroIntelStrategy(0.0);
    distribution.initSingleEvent(doWithdraw,
                                 doNotWithdraw,
                                 withdrawalProbability);
}
/*
bool ZeroIntelDepositor::reasonsCounterfactually(void) const{
    return false;
}

bool ZeroIntelDepositor::isFactual(Strategy* givenStrategy) const {
    return true;
}

void ZeroIntelDepositor::learnFromExperience(void){}

void ZeroIntelDepositor::resetExperience(void){}

void ZeroIntelDepositor::observePayoff(void){}

void ZeroIntelDepositor::revertToFactual(void){}

void ZeroIntelDepositor::setUpStrategy(Strategy* newStrategy){
    newStrategy->configure(this);
}

void ZeroIntelDepositor::setUpForSimulation(void){
    currentStrategy = distribution.drawStrategy();
    setUpStrategy(currentStrategy);
}
*/