#ifndef PRACTICE
#define PRACTICE

#include <eosio/eosio.hpp>
#include <pet.hpp>

CONTRACT practice : public eosio::contract
{
public:
    using eosio::contract::contract;
    ACTION greet(eosio::name const & nm);
};

#endif //PRACTICE