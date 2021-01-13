#include <practice.hpp>

void practice::sound(eosio::name const & sound)
{
    eosio::print("This animal makes a sound: ", sound);
}

// Add an action which will allow for table entries to be added to pet table
void practice::addpet(uint64_t const id, eosio::name const & owner, eosio::name const & pet_name, uint64_t const age, eosio::name const & type)
{
    // check if owner == actor/account are same; if not, it denies due to missing correct keys
    require_auth(owner);
    // access pet table (using typedef from pet.hpp)
    // call it pets; 2 args - name of contract that its running on, table scope (like a sub table in table)
    // scope is of type uint64_t, but we convert it (name) to numbers with .value
    pets_table pets(get_self(), get_self().value);    // get_self() - refers to whatever the name is of the current acc on which the contract is deployed

    // should not find; if we do, get err msg
    eosio::check(pets.find(id) == pets.end(), "The ID already exists. Please enter a new ID.");

    // put new row in table with info
    // 2 args - payer of RAM for added table entry, lambda expression
        // lambda - & (reference to) entry type
        // set entry equal to a pet of these types -----------|----|------|--------|-----|
    pets.emplace(get_self(), [&](auto & entry){ entry = pet_t(id, owner, pet_name, age, type); });
}

void practice::modifypet(uint64_t const id, eosio::name const & owner, eosio::name const & pet_name, uint64_t const age, eosio::name const & type)
{
    pets_table pets(get_self(), get_self().value);
    // args: iterator to appropriate id from table, RAM payer, lambda - set id of entry equal to the values (same as addpet)
    auto pet_iterator = pets.find(id);

    //check if the entry exists
    // args - bool(true-cont as if nothing happened/false-stops and print err msg), err msg
    eosio::check(pet_iterator != pets.end(), "The ID you entered does not exist.");
    
    // lets ACTUAL owner modify; not new owner (cannot reassign so someone else can modify)
    // requires that this owner is the one that auth'd TX
    require_auth(pet_iterator->get_owner());    // get_owner from pet.hpp; gets current owner by id
    
    eosio::check(age >= pet_iterator->get_age(), "The pet can not decrease in age.");

    pets.modify(pet_iterator, get_self(), [&](auto & entry){
        entry = pet_t(id, owner, pet_name, age, type);
    });
}

void practice::removepet(uint64_t const id)
{
    pets_table pets(get_self(), get_self().value);
    auto pet_iterator = pets.find(id);

    //check if the entry exists
    // args - bool(true-cont as if nothing happened/false-stops and print err msg), err msg
    eosio::check(pet_iterator != pets.end(), "The ID you entered does not exist.");

    require_auth(pet_iterator->get_owner());

    pets.erase(pet_iterator);
}