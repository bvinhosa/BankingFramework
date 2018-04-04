#include "CommonRepetition.hpp"
#include <iostream>
#include "../Economy/StrategicBankingSystem.hpp"

CommonRepetition::CommonRepetition(Cyclic& givenCyclic,
                                   int cyclesPerRep) :
        myCyclic(givenCyclic),
        cyclesPerRepetition(cyclesPerRep){
}


void CommonRepetition::repeat(StrategicBankingSystem &system) {
    //std::cout << "CommonRepetition::repeat" << std::endl;
    //myCyclic.cycle(system);

    for (int i = 0; i < cyclesPerRepetition; i++) {
        myCyclic.cycle(system);
        system.operationalReset();
    }

    StrategicAgentPointerVector& agentPtrVector =
            system.getStrategicAgents();

    for(StrategicAgent* agent: agentPtrVector)
        agent->setUpForSimulation();

    system.prepareForIteration();
    myCyclic.iterate(system);
    theAnalyzer.respondEndOfRepetition(system);
    system.operationalReset();
}

std::string CommonRepetition::getFinalResults(void){
    return theAnalyzer.toString();
}