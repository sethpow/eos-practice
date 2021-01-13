#ifndef PRACTICE
#define PRACTICE

#include <eosio/eosio.hpp>
#include <pet.hpp>

CONTRACT practice : public eosio::contract
{
public:
    using eosio::contract::contract;
    ACTION sound(eosio::name const & sound);
    // Add an action which will allow for table entries to be added to pet table
    ACTION addpet(uint64_t const id, eosio::name const & owner, eosio::name const & pet_name, uint64_t const age, eosio::name const & type);
    ACTION modifypet(uint64_t const id, eosio::name const & owner, eosio::name const & pet_name, uint64_t const age, eosio::name const & type);
    ACTION removepet(uint64_t const id);
};

#endif //PRACTICE