#ifndef LEARNINGCYCLE_HPP
#define LEARNINGCYCLE_HPP

#include "Cyclic.hpp"

class LearningCycle : public Cyclic {
public:
    LearningCycle(long totalCyclesAllReps, Iterable& givenIterable);
    virtual void cycle(StrategicBankingSystem& system);
    virtual void iterate(StrategicBankingSystem& system);
    virtual Iterable& getIterable(void);
private:
    void reportProgress(void);

    long reportControl;
    long numCyclesAllReps;
    long totalCyclesElapsed=0;
    Iterable& myIterable;
};

#endif //LEARNINGCYCLE_HPP
