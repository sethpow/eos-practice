#ifndef PRACTICE
#define PRACTICE

#include <eosio/eosio.hpp>
#include <pet.hpp>

CONTRACT practice : public eosio::contract
{
public:
    using eosio::contract::contract;
    // test ACTION
    ACTION sound(eosio::name const & sound);
    
    // CRUD
    ACTION addpet(uint64_t const id, eosio::name const & owner, eosio::name const & pet_name, uint64_t const age, eosio::name const & type);
    ACTION modifypet(uint64_t const id, eosio::name const & owner, eosio::name const & pet_name, uint64_t const age, eosio::name const & type);
    ACTION removepet(uint64_t const id);

    // secondary indexing; filter pet by id
    ACTION showpet(uint64_t const id);
    // secondary indexing; list all pets owned by specific owner
    ACTION petsownedby(eosio::name const & owner);
};

#endif //PRACTICE