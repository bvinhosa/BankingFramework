#include "StrategyExperience.hpp"
#include "../Util/ProbDistrib.hpp"

#include <cmath>
#include <sstream>
#include <iostream>

void StrategyExperience::initUniform(std::set<Strategy*> strategySet){
    reset();

    int numStrategies = strategySet.size();
    double uniformProbability = 1.0 / numStrategies;

    for(auto * element: strategySet) {
        probabilities[element] = uniformProbability;
        thisAgentsStrategies.insert(element);
    }
}

void StrategyExperience::observePayoff(Strategy* strategy, StrategicAgent* agent){
    payoffs[strategy] = strategy->getPayoff(agent);
}

void StrategyExperience::learn(Strategy* factual,
                               StrategicAgent* agent){
    learn(localPhony,factual,agent);
}

void StrategyExperience::learn(const EWAParameters& givenParameters,
                   Strategy* factual,
                   StrategicAgent* agent){
/*
    for(auto & payoff: payoffs){
        payoff.second = payoff.first->getPayoff(agent);
    }
*/
    //update attractions

    for(auto & attraction: attractions){
        double contributionPrevious = givenParameters.getPhi() *
                                      N_tMinus1 *
                                      attraction.second;
        double payoffWeight = ( (attraction.first == factual) ?
                                1.0 :
                                givenParameters.getDelta() );
        double weightedPayoff = payoffWeight * payoffs[attraction.first];
        attraction.second = (contributionPrevious + (weightedPayoff) / N_t);
    }

    //process probabilities

    std::map<Strategy*,double> partialExpAttractions;
    double totalExpAttraction = 0.0;

    for(auto & probability: probabilities){
        //std::cout << "att: " << attractions[probability.first] << std::endl;
        double attraction_term = exp(givenParameters.getLambda()*
                                     attractions[probability.first]);
        //std::cout << "attTerm: " << attraction_term << std::endl;
        partialExpAttractions.insert(
                std::pair<Strategy*,double>(
                        probability.first,
                        attraction_term));
        totalExpAttraction += attraction_term;
    }

    for(auto & probability: probabilities){
        //std::cout << "partialExpAttract: " << partialExpAttractions[probability.first] << std::endl;
        //probability.second = partialExpAttractions[probability.first] /
                             //totalExpAttraction;
    }

    //update N(t) and N(t-1)

    N_tMinus1 = N_t;
    N_t = (givenParameters.getRho() * N_tMinus1) + 1;

}

Strategy* StrategyExperience::drawStrategy(void){
    ProbDistrib& randomly = ProbDistrib::instance();

    double uniformDraw = randomly.drawUniformContinuous(0.0,1.0);

    double lowerBound = 0.0;

    for(auto element: probabilities){
        double upperBound = lowerBound + element.second;

        if((uniformDraw >= lowerBound) && (uniformDraw <= upperBound)){
            return element.first;
        }
        lowerBound = upperBound;
    }
    return nullptr;
}

void StrategyExperience::reset(void){
    N_t = 1;
    N_tMinus1 = 0;

    resetDistributionToUniform();

    for(auto & element: attractions )
        element.second==0.0;
    for(auto & element: payoffs )
        element.second==0.0;

}

StrategyPointerSet& StrategyExperience::getStrategies(void){
    return thisAgentsStrategies;
}

void StrategyExperience::resetDistributionToUniform(void){

    int numStrategies = probabilities.size();
    double uniformProbability = 1.0 / numStrategies;

    for(auto element: probabilities)
        element.second = uniformProbability;
}

std::string StrategyExperience::toString(void){
    std::stringstream ss;

    ss << "N(t) = " << N_t << std::endl;

    for(auto element: probabilities){
        ss << element.first->toString()
           << "; p = "
           << element.second
           << "; pi = "
           << payoffs[element.first]
           <<"; A = "
           << attractions[element.first]
           << std::endl;
    }

    return ss.str();
}