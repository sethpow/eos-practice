#include <practice.hpp>

void practice::greet(eosio::name const & nm)
{
    eosio::print("Hello ", nm);
}


// Add an action which will allow for table entries to be added to pet table
void practice::addpet(uint64_t const id, eosio::name const & owner, eosio::name const & pet_name, uint64_t const age, eosio::name const & type)
{
    // access pet table (using typedef from pet.hpp)
    // call it pets; 2 args - name of contract that its running on, table scope (like a sub table in table)
    // scope is of type uint64_t, but we convert it (name) to numbers with .value
    pets_table pets(get_self(), get_self().value);    // get_self() - refers to whatever the name is of the current acc on which the contract is deployed

    // put new row in table with info
    // 2 args - payer of RAM for added table entry, lambda expression
        // lambda - & (reference to) entry type
        // set entry equal to a pet of these types -----------|----|------|--------|-----|
    pets.emplace(get_self(), [&](auto & entry){ entry = pet_t(id, owner, pet_name, age, type); });
}