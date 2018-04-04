#ifndef COMMONITERATION_HPP
#define COMMONITERATION_HPP

#include "Iterable.hpp"

class CommonIteration : public Iterable {
public:
    virtual void iterate(BankingSystem& system);
};

#endif //COMMONITERATION_HPP
