#include <iostream>
#include "ZeroIntelFirm.hpp"

#include "../Strategies/FirmStrategy.hpp"

ZeroIntelFirm::ZeroIntelFirm(double probabilityOfDefault,
                             const std::string & givenName,
                             int agentId,
                             int firmId) : ConcreteFirm(givenName,
                                                        agentId,
                                                        firmId){
    FirmStrategy* doDefault = new FirmStrategy(true);
    FirmStrategy* doNotDefault = new FirmStrategy(false);
    distribution.initSingleEvent(doDefault, doNotDefault, probabilityOfDefault);
    //std::cout << distribution.toString() << std::endl;
}