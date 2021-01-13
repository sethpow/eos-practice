#ifndef PRACTICE
#define PRACTICE

#include <eosio/eosio.hpp>
#include <pet.hpp>

CONTRACT practice : public eosio::contract
{
public:
    using eosio::contract::contract;
    ACTION greet(eosio::name const & nm);
    // Add an action which will allow for table entries to be added to pet table
    ACTION addpet(uint64_t const id, eosio::name const & owner, eosio::name const & pet_name, uint64_t const age, eosio::name const & type);
};

#endif //PRACTICE