#include "CommonCycle.hpp"
#include <iostream>

#include "../Economy/StrategicBankingSystem.hpp"

CommonCycle::CommonCycle(Iterable &givenIterable) :
        myIterable(givenIterable){
}

void CommonCycle::cycle(StrategicBankingSystem& system){

   //std::cout << "CommonCycle::cycle" << std::endl;
    myIterable.iterate(system);
    //collect any data
    //system.operationalReset();
}

void CommonCycle::iterate(StrategicBankingSystem& system){

    // std::cout << "CommonCycle::cycle" << std::endl;
    myIterable.iterate(system);
    //collect any data
    //system.operationalReset();
}

Iterable& CommonCycle::getIterable(void) {
    return myIterable;
}
