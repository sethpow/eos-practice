#include <eosio/eosio.hpp>

CONTRACT tictactoe : public eosio::contract
{
public:
using contract::contract;

  // table structure
  TABLE gameschema
  {
    eosio::name host;
    eosio::name opponent;
    auto primary_key() const { return host.value; }
  };

  // table setup
  typedef eosio::multi_index <"games"_n, gameschema> games_table;


  ACTION greet(eosio::name host)
  {
    require_auth( host );
    eosio::print("Hello, ", host);
  }

  ACTION create(eosio::name host, eosio::name opponent)
  {
    require_auth( host );

    // instantiating table
    // writing contract, scope
    games_table _games( get_self(), get_self().value );

    auto game_itr = _games.find( host.value );
    if(game_itr == _games.end() )
    {
      _games.emplace( host, [&](auto& newrecord){
        newrecord.host = host;
        newrecord.opponent = opponent;
      });
    } else
    {
      _games.modify( game_itr, host, [&](auto& record_to_modify){
        record_to_modify.opponent = opponent;
      });
    }

  }

  ACTION clear() {
    require_auth( get_self() );

    games_table _games(get_self(), get_self().value);

    // Delete all records in _messages table
    auto game_itr = _games.begin();
    while (game_itr != _games.end()) {
      game_itr = _games.erase(game_itr);
    }
  }

private:

};