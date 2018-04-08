#include <iostream>
#include "Workflow/LearningExperimentWorkflow.hpp"
#include "Workflow/CommonWorkflow.hpp"
#include "Workflow/LearningWorkflow.hpp"
#include "Workflow/ExperimentWorkflow.hpp"
#include "Util/ProbDistrib.hpp"

int main() {

    std::vector<double> bankSizes = {1.0,1.0,1.0,1.0,1.0};
    //1.0,1.0,1.0,1.0,1.0};
    /*1.0,1.0,1.0,1.0,1.0,
    1.0,1.0,1.0,1.0,1.0,
    1.0,1.0,1.0,1.0,1.0};*/

    StandardBankingSystem::Parameters params = {(int)bankSizes.size(),
                                                10,
                                                5};


    ProbDistrib::instance();
    Workflow *wf = new LearningExperimentWorkflow(10,100,params,bankSizes);
    wf->execute();
    std::cout << wf->exportResultsToString() << std::endl;
    delete wf;
    return 0;
}