#include "ExperimentRepetition.hpp"

#include <iostream>
#include <sstream>
#include <algorithm>
#include <cassert>

#include "../Economy/StrategicBankingSystem.hpp"
#include "../Util/ProbDistrib.hpp"
#include "../Strategies/BankStrategy.hpp"
#include "../Agents/IntelligentBank.hpp"

using std::string;
using std::endl;
using std::stringstream;
using std::cout;
using std::vector;
using std::pair;

ExperimentRepetition::ExperimentRepetition(Cyclic& givenCyclic,
                                           int cyclesPerRep) :
        myCyclic(givenCyclic),
        cyclesPerRepetition(cyclesPerRep){
}

void ExperimentRepetition::repeat(StrategicBankingSystem &system) {
    //cout << "ExperimentRepetition::repeat" << endl;

    int numModerates = 2, numSeveres = 1;
    double capModerate = 0.04, liqModerate = 0.02;
    double capSevere = 0.02, liqSevere = 0.01;


    //do the normal repetition

    for (int i = 0; i < cyclesPerRepetition; i++) {
        myCyclic.cycle(system);
        system.operationalReset();
    }

    StrategicAgentPointerVector& agentPtrVector =
            system.getStrategicAgents();

    // do the "post-convergence" iteration to record converged data
    for(StrategicAgent* agent: agentPtrVector)
        agent->setUpForSimulation();

    system.prepareForIteration();
    myCyclic.iterate(system);
    theAnalyzer.respondEndOfRepetition(system);
    system.operationalReset();


    //then, do the whole experiment thing.

    Iterable& theIterable = myCyclic.getIterable();

    BankStrategy* moderateStress = new BankStrategy(capModerate,
                                                    liqModerate);
    BankStrategy* severeStress = new BankStrategy(capSevere,
                                                  liqSevere);

    vector<IntelligentBank*> mdBanks, sdBanks;

    // get Id of severely distressed and moderately distressed banks
    BankPointerVector allBanks = system.getBanks();

    auto distressedBanks = pair<vector<IntelligentBank*>,
            vector<IntelligentBank*> >(
            getModerateAndSeverelyStressed(allBanks,
                                           numModerates,
                                           numSeveres));
    mdBanks = distressedBanks.first;
    sdBanks = distressedBanks.second;

    for (auto * agent : system.getStrategicAgents())
        agent->suspendLearning();

     // modify those ratios
     for (auto * moderatelyDistressedBank : mdBanks)
         //cout << dynamic_cast<IntelligentBank*>(moderatelyDistressedBank)->toString() << endl;
         dynamic_cast<IntelligentBank*>(moderatelyDistressedBank)->forceStrategy(moderateStress);
     for (auto * severelyDistressedBank : sdBanks)
         //cout << dynamic_cast<IntelligentBank*>(severelyDistressedBank)->toString() << endl;
         dynamic_cast<IntelligentBank*>(severelyDistressedBank)->forceStrategy(severeStress);

     // run the "laissez-faire" iteration
     system.prepareForIteration();
     theIterable.iterate(system);

     //invoke analysis functionality (Experiment Analyzer)
     expAnalyzer.respondLaissezFaire(system);
     system.operationalReset();

     // now the severely distressed banks are "resolved" (made null)
     // severely distressed banks
    for(int i = 0; i < sdBanks.size(); i++)
        system.deactivateBank(sdBanks[i]->getBankId());

     // run the "timely resolution" iteration
     system.prepareForIteration();
     theIterable.iterate(system);
     //invoke analysis functionality (Experiment Analyzer)
     expAnalyzer.respondTimelyResolution(system);

     //set the system back to normal:

     // swap the the resolved banks back to the system.
    system.reactivateBanks();

     //free strategies
     for (auto * moderatelyDistressedBank : mdBanks)
         (dynamic_cast<IntelligentBank*>(moderatelyDistressedBank))->freeStrategies();
     for (auto * severelyDistressedBank : sdBanks)
         (dynamic_cast<IntelligentBank*>(severelyDistressedBank))->freeStrategies();

     system.operationalReset();

    // resume learning
    for (auto * agent : system.getStrategicAgents()){
        agent->resumeLearning();
        agent->resetExperience();
    }

}

vector<IntelligentBank*> ExperimentRepetition::getDistinct(
        BankPointerVector banks,
        int howMany){

    vector<IntelligentBank*> banksSample;

    ProbDistrib pd = ProbDistrib::instance();

    vector<int> drawnIndices = pd.multipleDrawDistinct(howMany,
                                                       banks.size());

    for(int i = 0; i<howMany; i++){
        banksSample.push_back(dynamic_cast<IntelligentBank*>(banks [ drawnIndices[i] ] ));
    }

    return banksSample;
}



pair<vector<IntelligentBank*>,
        vector<IntelligentBank*> >
ExperimentRepetition::getModerateAndSeverelyStressed(
        BankPointerVector banks,
        int howManyModerately,
        int howManySeverely){

    vector<IntelligentBank*> alteredBanks;

    alteredBanks = getDistinct(banks, howManyModerately+howManySeverely);

    vector<IntelligentBank*> moderatelyDistressedBanks(alteredBanks.begin(),
                                                alteredBanks.begin() +
                                                howManyModerately);
    vector<IntelligentBank*> severelyDistressedBanks(alteredBanks.begin() +
                                              howManyModerately,
                                              alteredBanks.end());

    return pair<vector<IntelligentBank*>,
            vector<IntelligentBank*> >(
            moderatelyDistressedBanks,
            severelyDistressedBanks);
}

/*
BankPointerVector ExperimentRepetition::getDistinct(
        BankPointerVector banks,
        int howMany){

    BankPointerVector banksSample;

    ProbDistrib pd = ProbDistrib::instance();

    vector<int> drawnIndices = pd.multipleDrawDistinct(howMany,
                                                            banks.size());

    for(int i = 0; i<howMany; i++){
        banksSample.push_back(banks [ drawnIndices[i] ]  );
    }

    return banksSample;
}



pair<BankPointerVector, BankPointerVector>
ExperimentRepetition::getModerateAndSeverelyStressed(
        BankPointerVector banks,
        int howManyModerately,
        int howManySeverely){

    BankPointerVector alteredBanks;

    alteredBanks = getDistinct(banks, howManyModerately+howManySeverely);

    BankPointerVector moderatelyDistressedBanks(alteredBanks.begin(),
                                                alteredBanks.begin() +
                                                    howManyModerately);
    BankPointerVector severelyDistressedBanks(alteredBanks.begin() +
                                                      howManyModerately,
                                              alteredBanks.end());

    return pair<BankPointerVector, BankPointerVector>(
            moderatelyDistressedBanks,
            severelyDistressedBanks);
}
*/

string ExperimentRepetition::getFinalResults(void){
    stringstream results;

    results << theAnalyzer.toString()
            << endl << expAnalyzer.toString();

    return results.str();
}
