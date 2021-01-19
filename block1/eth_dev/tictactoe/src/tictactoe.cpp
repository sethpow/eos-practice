#include <eosio/eosio.hpp>

CONTRACT tictactoe : public eosio::contract
{
public:
using contract::contract;

  ACTION greet(eosio::name host)
  {
    require_auth( host );
    eosio::print("Hello, ", host);
  }

private:

};