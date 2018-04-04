#include "LearningCycle.hpp"
#include <iostream>

#include "../Economy/StrategicBankingSystem.hpp"


LearningCycle::LearningCycle(Iterable &givenIterable) :
        myIterable(givenIterable){
}

void LearningCycle::cycle(StrategicBankingSystem& system) {
    //std::cout << "LearningCycle::cycle" << std::endl;

    StrategicAgentPointerVector& agentPtrVector =
            system.getStrategicAgents();

    // [FACTUAL]
    for(StrategicAgent* agent: agentPtrVector)
        agent->setUpForSimulation();
    system.prepareForIteration();
    myIterable.iterate(system);
    for(StrategicAgent* agent: agentPtrVector)
        agent->observePayoff();

    system.operationalReset();

    // [COUNTERFACTUAL]
    for(StrategicAgent* intelligentAgent: agentPtrVector){
        if(!intelligentAgent->reasonsCounterfactually())
            continue;

        StrategyPointerSet& agentsStrategies =
                intelligentAgent->getPossibleStrategies();

        for (auto* currentStrategy: agentsStrategies) {
            if(intelligentAgent->isFactual(currentStrategy))
                continue;

            intelligentAgent->setUpStrategy(currentStrategy);
            system.prepareForIteration();
            myIterable.iterate(system);
            intelligentAgent->observePayoff();
            system.operationalReset();
            /**/
        }
        intelligentAgent->learnFromExperience();
        intelligentAgent->revertToFactual();
    }
}

void LearningCycle::iterate(StrategicBankingSystem& system){

    //std::cout << "LearningCycle::iterate" << std::endl;
    myIterable.iterate(system);
    //collect any data
    //system.operationalReset();
}


Iterable& LearningCycle::getIterable(void) {
    return myIterable;
}
