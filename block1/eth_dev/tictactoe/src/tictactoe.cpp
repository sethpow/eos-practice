#include <eosio/eosio.hpp>

CONTRACT tictactoe : public eosio::contract
{
public:
using contract::contract;

  TABLE gameschema
  {
    eosio::name host;
    eosio::name opponent;
    auto primary_key() const { return host.value; }
  };

  typedef eosio::multi_index <"games"_n, gameschema> games_table;


  ACTION greet(eosio::name host)
  {
    require_auth( host );
    eosio::print("Hello, ", host);
  }

  ACTION create(eosio::name host, eosio::name opponent)
  {

  }

  ACTION close()
  {
  
  }

private:

};