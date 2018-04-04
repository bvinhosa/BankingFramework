#ifndef REPEATABLE_HPP
#define REPEATABLE_HPP

#include "Cyclic.hpp"

class StrategicBankingSystem;

class Repeatable {
public:
    virtual void repeat(StrategicBankingSystem& system) = 0;
};

#endif //REPEATABLE_HPP
