#include "ExperimentAnalyzer.hpp"

using std::string;

string ExperimentAnalyzer::toString() {
    return (string("Laissez-faire counter: ") +
            std::to_string(laissezFaireCounter) +
            string("; Timely resolution counter: ") +
            std::to_string(timelyResolutionCounter));
}

void ExperimentAnalyzer::respondLaissezFaire(BankingSystem &system) {
    laissezFaireCounter++;
}

void ExperimentAnalyzer::respondTimelyResolution(BankingSystem &system) {
    timelyResolutionCounter++;
}
