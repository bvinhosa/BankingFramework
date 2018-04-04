#include "FirmStrategy.hpp"

#include <sstream>
#include <iostream>
#include "../Agents/ZeroIntelFirm.hpp"

//#include "../Agents/Firm.hpp"

FirmStrategy::FirmStrategy(bool willDefault){
    hasDefaulted = willDefault;
}

void FirmStrategy::configure(StrategicAgent* theAgent){
    Firm* theFirm = dynamic_cast<Firm*>(theAgent);
    theFirm->setDefault(hasDefaulted);
}

double FirmStrategy::getPayoff(StrategicAgent* theAgent) const {
}

std::string FirmStrategy::toString(void) const{
    if(hasDefaulted)
        return std::string("Default");
    else
        return std::string("No default");
}
