#include "StrategyExperience.hpp"
#include "../Util/ProbDistrib.hpp"

#include <cmath>
#include <sstream>
#include <iostream>
#include <cassert>

void StrategyExperience::initUniform(std::set<Strategy*> strategySet){
    //reset();

    int numStrategies = strategySet.size();
    double uniformProbability = 1.0 / numStrategies;

    for(auto * element: strategySet) {
        probabilities[element] = uniformProbability;
        thisAgentsStrategies.insert(element);
        attractions[element] = 0.0;
        payoffs[element] = 0.0;
    }
}

void StrategyExperience::reset(void){
    N_t = 1.0;
    N_tMinus1 = 0.0;

    resetDistributionToUniform();

    for (auto * element: thisAgentsStrategies){
        attractions[element] = 0.0;
        payoffs[element] = 0.0;
    }

    /*
    for(auto & element: attractions )
        element.second=0.0;
    for(auto & element: payoffs )
        element.second=0.0;
        */

}


void StrategyExperience::resetDistributionToUniform(void){

    int numStrategies = probabilities.size();
    double uniformProbability = 1.0 / numStrategies;

    for (auto * element: thisAgentsStrategies)
        probabilities[element] = uniformProbability;

/*
    for(auto & element: probabilities)
        element.second = uniformProbability;
*/
 }

StrategyPointerSet& StrategyExperience::getStrategies(void){
    return thisAgentsStrategies;
}

void StrategyExperience::observePayoff(Strategy* strategy, StrategicAgent* agent){
    assert(payoffs.count(strategy) > 0);
    payoffs[strategy] = strategy->getPayoff(agent);
    assert(!std::isnan(payoffs[strategy]));
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
        payoff.second = (payoff.first)->getPayoff(agent);
    }
*/
    //update attractions

    for(auto & attraction: attractions){
        double contributionPrevious = givenParameters.getPhi() *
                                      N_tMinus1 *
                                      attraction.second;
        assert(!std::isnan(contributionPrevious));
        double payoffWeight = ( (attraction.first == factual) ?
                                1.0 :
                                givenParameters.getDelta() );
        assert(!std::isnan(payoffWeight));
        double weightedPayoff = payoffWeight * payoffs[attraction.first];
        assert(payoffs.count(attraction.first) > 0);
        assert(!std::isnan(payoffs[attraction.first]));
        assert(!std::isnan(weightedPayoff));
        double newAttraction = (contributionPrevious + (weightedPayoff) / N_t);
        assert(!std::isnan(newAttraction));
        attraction.second = newAttraction;
    }

    //process probabilities

    std::map<Strategy*,double> partialExpAttractions;
    double totalExpAttraction = 0.0;

    for(auto & probability: probabilities){

        double attractionForThisProbability = attractions[probability.first];

        assert(!std::isnan(attractionForThisProbability));

        //std::cout << "att: " << attractions[probability.first] << std::endl;
        double expAttractionTerm = exp(givenParameters.getLambda()*
                                             attractionForThisProbability);

        assert(!std::isnan(expAttractionTerm));
        assert(expAttractionTerm > 0.0);

        //std::cout << "attTerm: " << expAttractionTerm << std::endl;
        partialExpAttractions.insert(
                std::pair<Strategy*,double>(
                        probability.first,
                        expAttractionTerm));
        totalExpAttraction += expAttractionTerm;
    }

    assert(!std::isnan(totalExpAttraction));
    assert(totalExpAttraction > 0.0);

    for(auto & probability: probabilities){
        //std::cout << "partialExpAttract: " << partialExpAttractions[probability.first] << std::endl;
        probability.second = partialExpAttractions[probability.first] /
                             totalExpAttraction;
    }

    partialExpAttractions.clear();

    //update N(t) and N(t-1)

    N_tMinus1 = N_t;
    N_t = (givenParameters.getRho() * N_tMinus1) + 1.0;

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