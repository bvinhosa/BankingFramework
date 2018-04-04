#ifndef CYCLIC_HPP
#define CYCLIC_HPP

#include "Iterable.hpp"

class StrategicBankingSystem;
class Iterable;

class Cyclic {
public:
    virtual void cycle(StrategicBankingSystem& system) = 0;
    virtual void iterate(StrategicBankingSystem& system) = 0;
    virtual Iterable& getIterable(void) = 0;
};

#endif //CYCLIC_HPP
