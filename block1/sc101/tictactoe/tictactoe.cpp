#include <eosio/eosio.hpp>

CONTRACT tictactoe : public eosio::contract
{
public:
    using contract::contract;

    ACTION welcome(eosio::name host, eosio::name opponent)
    {
        eosio::check( host == eosio::name("host"), "You are not the host!" );
        eosio::print("Welcome, ", host, " and ", opponent, "!");
    }
};