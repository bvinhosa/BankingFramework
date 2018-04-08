#include "LearningCycle.hpp"
#include <iostream>

#include "../Economy/StrategicBankingSystem.hpp"


LearningCycle::LearningCycle(long totalCyclesAllReps,
                             Iterable& givenIterable) :
        numCyclesAllReps(totalCyclesAllReps),
        myIterable(givenIterable){

    if(numCyclesAllReps <= 100)
        reportControl = numCyclesAllReps;
    else if (numCyclesAllReps <= 10000)
        reportControl = 10;
    else if (numCyclesAllReps <= 100000)
        reportControl = 100;
    else
        reportControl = numCyclesAllReps / 10000;
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

    totalCyclesElapsed++;
    reportProgress();
}

void LearningCycle::iterate(StrategicBankingSystem& system){

    //std::cout << "LearningCycle::iterate" << std::endl;
    myIterable.iterate(system);
    //collect any data
    //system.operationalReset();
}

void LearningCycle::reportProgress(void){
    if((totalCyclesElapsed % reportControl) != 0)
        return;

    double cyclePercentage = ((double)totalCyclesElapsed /
                              (double)numCyclesAllReps)*100.0;
    std::cout << cyclePercentage << "% elapsed" << std::endl;
}

Iterable& LearningCycle::getIterable(void) {
    return myIterable;
}
