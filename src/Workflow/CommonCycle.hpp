#ifndef COMMONCYCLE_HPP
#define COMMONCYCLE_HPP

#include "Cyclic.hpp"

class CommonCycle : public Cyclic {
public:
    CommonCycle(Iterable &givenIterable);
    virtual void cycle(StrategicBankingSystem& system);
    virtual void iterate(StrategicBankingSystem& system);
    virtual Iterable& getIterable(void);
private:
    Iterable& myIterable;
};


#endif //COMMONCYCLE_HPP
