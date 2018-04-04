#include "ZeroIntelStrategy.hpp"

#include <sstream>

#include "../Agents/ZeroIntelDepositor.hpp"

ZeroIntelStrategy::ZeroIntelStrategy(double givenProportion) :
                            proportionToWithdraw(givenProportion){}

void ZeroIntelStrategy::configure(StrategicAgent* theAgent){
    Depositor* theDepositor = dynamic_cast<Depositor*>(theAgent);
    theDepositor->setUpWithdrawal(proportionToWithdraw);
}
double ZeroIntelStrategy::getPayoff(StrategicAgent* theAgent) const{

}

std::string ZeroIntelStrategy::toString(void) const{
    std::stringstream result;
    result << "Proportion to withdraw: " << proportionToWithdraw;
    return result.str();
}
