#include <eosio/eosio.hpp>

CONTRACT toy : public contract
{
public:
    using contract::contract;

    ACTION welcome(eosio::name boss)
    {
        eosio::check( has_auth( name( "toyboss" )), "You're not our owner!" );
        eosio::check( boss == name( "toyboss" ), "Don't lie about your name." );
        eosio::print( "Welcome to the toy house!" );
    }

private:

};