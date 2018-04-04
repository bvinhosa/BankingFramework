#ifndef WORKFLOW_HPP
#define WORKFLOW_HPP

#include <string>

class Workflow {
public:
    virtual void execute(void) = 0;
    virtual std::string exportResultsToString(void) = 0;
};


#endif //WORKFLOW_HPP
