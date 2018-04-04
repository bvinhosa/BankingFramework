#ifndef AGENT_HPP
#define AGENT_HPP

#include <string>
#include <vector>

class Agent {
public:
    virtual int getId(void) const = 0;
    virtual std::string toString(void) const = 0;
    virtual std::string getName(void) const = 0;
    virtual void reset(void) = 0;
};

typedef std::vector<Agent*> AgentPtrVector;

#endif //AGENT_HPP
