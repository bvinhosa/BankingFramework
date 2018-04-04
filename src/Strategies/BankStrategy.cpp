#include "BankStrategy.hpp"

#include <sstream>

#include "../Agents/IntelligentBank.hpp"

BankStrategy::BankStrategy(double givenCapital,
                           double givenLiquidity) :
                                    capital(givenCapital),
                                    liquidity(givenLiquidity){
}

void BankStrategy::configure(StrategicAgent* theAgent) {
    //Bank* theBank = (Bank*)theAgent;
    Bank* theBank = dynamic_cast<Bank*>(theAgent);
    theBank->setUpBalanceSheet(capital,liquidity);
}

double BankStrategy::getPayoff(StrategicAgent* theAgent) const {
    //Bank* theBank = (Bank*)theAgent;
    Bank* theBank = dynamic_cast<Bank*>(theAgent);
    return theBank->getReturnOnEquity();
}

std::string BankStrategy::toString(void) const {
    std::stringstream result;

    result << "Capital: " << capital
           << ", Liquidity: " << liquidity;

    return result.str();
}

