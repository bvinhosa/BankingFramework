#ifndef ITERABLE_HPP
#define ITERABLE_HPP

class BankingSystem;

class Iterable {
public:
    virtual void iterate(BankingSystem& system) = 0;
};


#endif //ITERABLE_HPP
