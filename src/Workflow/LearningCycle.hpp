#ifndef LEARNINGCYCLE_HPP
#define LEARNINGCYCLE_HPP

#include "Cyclic.hpp"

class LearningCycle : public Cyclic {
public:
    LearningCycle(Iterable& givenIterable);
    virtual void cycle(StrategicBankingSystem& system);
    virtual void iterate(StrategicBankingSystem& system);
    virtual Iterable& getIterable(void);
private:
    Iterable& myIterable;
};

#endif //LEARNINGCYCLE_HPP
