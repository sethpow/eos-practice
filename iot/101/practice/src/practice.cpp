#include <practice.hpp>

void practice::greet(eosio::name const & nm)
{
    eosio::print("Hello ", nm);
}