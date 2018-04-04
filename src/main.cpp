#include <iostream>
#include "Workflow/LearningExperimentWorkflow.hpp"
#include "Workflow/CommonWorkflow.hpp"
#include "Workflow/LearningWorkflow.hpp"
#include "Workflow/ExperimentWorkflow.hpp"
#include "Util/ProbDistrib.hpp"

int main() {

    StandardBankingSystem::Parameters params = {10, 5, 5};
    std::vector<double> sizes = {1.0,1.0,1.0,1.0,1.0,
                                 1.0,1.0,1.0,1.0,1.0};
    /*1.0,1.0,1.0,1.0,1.0,
    1.0,1.0,1.0,1.0,1.0,
    1.0,1.0,1.0,1.0,1.0,
    1.0,1.0,1.0,1.0,1.0,
    1.0,1.0,1.0,1.0,1.0,
    1.0,1.0,1.0,1.0,1.0,
    1.0,1.0,1.0,1.0,1.0,
    1.0,1.0,1.0,1.0,1.0};*/

    ProbDistrib::instance();
    Workflow *wf = new LearningExperimentWorkflow(10,10,params,sizes);
    wf->execute();
    std::cout << wf->exportResultsToString() << std::endl;
    delete wf;
    return 0;
}